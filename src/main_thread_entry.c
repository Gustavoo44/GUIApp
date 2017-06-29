/* Main Thread entry function */
#include "main_thread.h"
#include "bsp_api.h"
#include "gx_api.h"
#include "gui/guiapp_specifications.h"
#include "gui/guiapp_resources.h"
#include "adc_hal_api_mg.h"

#if defined(BSP_BOARD_S7G2_SK)
#include "hardware/lcd.h"
#endif

/***********************************************************************************************************************
    Private function prototypes
 ***********************************************************************************************************************/
static bool ssp_touch_to_guix(sf_touch_panel_payload_t * p_touch_payload, GX_EVENT * g_gx_event);
void main_thread_entry(void);

void time_int_callback(timer_callback_args_t * p_args);
void toggle_led (bsp_led_t led);

#if defined(BSP_BOARD_S7G2_SK)
void g_lcd_spi_callback(spi_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
    Private global variables
 ***********************************************************************************************************************/
static GX_EVENT g_gx_event;

GX_WINDOW_ROOT * p_window_root;
extern GX_CONST GX_STUDIO_WIDGET *guiapp_widget_table[];


static GX_CHAR txt_buffer[5];

//adc_data_size_t adc_result[N_BUFFER];  /*Variavel que recebe o valor da conversão A/D*/
adc_data_size_t adc_result;

ssp_err_t result_status; /*Flag com a numeração que indica qual o status da conversão A/D*/

uint32_t i =0;
static float media_R=0;

static float b0 = 8.7989344e-5f;
static float b1 = 0.00017597869f;
static float b2 = 8.7989344e-5f;
static float a1 = -1.9809761f;
static float a2 = 0.98132808f;

static float vin=0;
static float vin_ant1=0;
static float vin_ant2=0;
static float vout=0;
static float vout_ant1=0;
static float vout_ant2=0;

/*******************************************************************************************************************//**
    @brief  Primary logic for handling events generated by the various sub-systems.
 ***********************************************************************************************************************/
void main_thread_entry(void) {
	ssp_err_t        err;
	sf_message_header_t * p_message = NULL;
	UINT      status = TX_SUCCESS;

	GX_PROMPT * p_prompt;

	/*---------------------------------------------------------------------------------------------*/
	/* Função que habilita o printf() no console*/
	//initialise_monitor_handles();

    //Inicializa o timer0
	err |= g_timer0.p_api->open(g_timer0.p_ctrl, g_timer0.p_cfg);
	// Inicializa o ADC e retorna o status e verifica se ocorreu tudo certo
    err = ADC_HAL_open();
    if(err != SSP_SUCCESS) while (1);

    //Configura o canal ADC e verifica se ocorreu tudo certo
    err =  ADC_HAL_scan_config();
    if(err != SSP_SUCCESS) while (1);

    //Continuos mode ADC
    err =  ADC_HAL_scan_start();
    if(err != SSP_SUCCESS)
    {
        toggle_led(1);
    }

    /** Check for any errors. */
    if (err != SSP_SUCCESS)
    {
        while(1)
        {
            /** Check err. */
            toggle_led(1);
        }
    }
    /*-----------------------------------------------------------------------------------------*/
    /* Initializes GUIX. */
    status = gx_system_initialize();
    if(TX_SUCCESS != status)
    {
        while(1);
    }

    /* Initializes GUIX drivers. */
    err = g_sf_el_gx.p_api->open (g_sf_el_gx.p_ctrl, g_sf_el_gx.p_cfg);
    if(SSP_SUCCESS != err)
    {
        while(1);
    }

    gx_studio_display_configure ( DISPLAY_1,
                                  g_sf_el_gx.p_api->setup,
                                  LANGUAGE_ENGLISH,
                                  DISPLAY_1_THEME_1,
                                  &p_window_root );

    err = g_sf_el_gx.p_api->canvasInit(g_sf_el_gx.p_ctrl, p_window_root);
    if(SSP_SUCCESS != err)
    {
        while(1);
    }

    // Create the widgets we have defined with the GUIX data structures and resources.
    GX_CONST GX_STUDIO_WIDGET ** pp_studio_widget = &guiapp_widget_table[0];
    GX_WIDGET * p_first_screen = NULL;

    while (GX_NULL != *pp_studio_widget)
    {
        // We must first create the widgets according the data generated in GUIX Studio.

        // Once we are working on the widget we want to see first, save the pointer for later.
        if (0 == strcmp("window1", (char*)(*pp_studio_widget)->widget_name))
        {
            gx_studio_named_widget_create((*pp_studio_widget)->widget_name, (GX_WIDGET *)p_window_root, GX_NULL);
        } else {
            gx_studio_named_widget_create((*pp_studio_widget)->widget_name, GX_NULL, GX_NULL);
        }
        // Move to next top-level widget
        pp_studio_widget++;
    }
    // Attach the first screen to the root so we can see it when the root is shown
   gx_widget_attach(p_window_root, p_first_screen);


    if(TX_SUCCESS != status)
    {
            while(1);
    }

    /* Shows the root window to make it and patients screen visible. */
    status = gx_widget_show(p_window_root);
    if(TX_SUCCESS != status)
    {
        while(1);
    }

    /* Lets GUIX run. */
    status = gx_system_start();
    if(TX_SUCCESS != status)
    {
        while(1){
            toggle_led(2);
        }
    }

#if defined(BSP_BOARD_S7G2_SK)
    /** Open the SPI driver to initialize the LCD (SK-S7G2) **/
    err = g_spi_lcdc.p_api->open(g_spi_lcdc.p_ctrl, (spi_cfg_t *)g_spi_lcdc.p_cfg);
    if (err)
    {
        while(1){
            toggle_led(2);
        }
    }
    /** Setup the ILI9341V (SK-S7G2) **/
    ILI9341V_Init();
#endif

    /* Controls the GPIO pin for LCD ON (DK-S7G2, PE-HMI1) */
#if defined(BSP_BOARD_S7G2_DK)
    err = g_ioport.p_api->pinWrite(IOPORT_PORT_07_PIN_10, IOPORT_LEVEL_HIGH);
    if (err)
    {
        while(1);
    }
#elif defined(BSP_BOARD_S7G2_PE_HMI1)
    err = g_ioport.p_api->pinWrite(IOPORT_PORT_10_PIN_03, IOPORT_LEVEL_HIGH);
    if (err)
    {
        while(1);
    }
#endif

    /* Opens PWM driver and controls the TFT panel back light (DK-S7G2, PE-HMI1) */
#if defined(BSP_BOARD_S7G2_DK) || defined(BSP_BOARD_S7G2_PE_HMI1)
    err = g_pwm_backlight.p_api->open(g_pwm_backlight.p_ctrl, g_pwm_backlight.p_cfg);
    if (err)
    {
        while(1);
    }
#endif

    /* Set the prompt pointer to txt_counter widget */
    status = gx_system_widget_find(ID_PRT_S_FORCA, GX_SEARCH_DEPTH_INFINITE, (GX_WIDGET **) &p_prompt);
    if (status)
            while (1){
                toggle_led(2);
            }

    /* Attach txt_buffer to txt_counter widget */
    status = gx_prompt_text_set(p_prompt, txt_buffer);
    if (status)
        while (1){
            toggle_led(2);
        }

    tx_thread_sleep(100);

    /*-----------------------------------------Loop Principal------------------------------------------------*/
	while(1)
	{
		bool new_gui_event = false;

		err = g_sf_message0.p_api->pend(g_sf_message0.p_ctrl, &main_thread_message_queue, (sf_message_header_t **) &p_message, TX_NO_WAIT);
		if (err)
		{
			/** TODO: Handle error. */
		    toggle_led(1);
		}

		switch (p_message->event_b.class_code)
		{
		case SF_MESSAGE_EVENT_CLASS_TOUCH:
		{
			switch (p_message->event_b.code)
			{
			case SF_MESSAGE_EVENT_NEW_DATA:
			{
				/** Translate an SSP touch event into a GUIX event */
				new_gui_event = ssp_touch_to_guix((sf_touch_panel_payload_t*)p_message, &g_gx_event);
			}
			default:
				break;
			}
			break;
		}
		default:
			break;
		}

		/** Message is processed, so release buffer. */
		err = g_sf_message0.p_api->bufferRelease(g_sf_message0.p_ctrl, (sf_message_header_t *) p_message, SF_MESSAGE_RELEASE_OPTION_FORCED_RELEASE);

		if (err)
		{
			/** TODO: Handle error. */
		}

		/** Post message. */
		if (new_gui_event) {
			gx_system_event_send(&g_gx_event);
		}

		/* Convert current counter value to string */
        gx_utility_ltoa((LONG) media_R, txt_buffer, 5);


        /* Let GUIX know that txt_counter should be re-drawn */
        status = gx_system_dirty_mark((GX_WIDGET *) p_prompt);
        if (status){
            while (1){
                toggle_led(2);
            }
        }
        /* Force re-draw all "dirty" widgets */
        gx_system_canvas_refresh();
        //toggle_led(2);
        tx_thread_sleep(10);

	}

}

static bool ssp_touch_to_guix(sf_touch_panel_payload_t * p_touch_payload, GX_EVENT * gx_event)
{
	bool send_event = true;

	switch (p_touch_payload->event_type)
	{
	case SF_TOUCH_PANEL_EVENT_DOWN:
		gx_event->gx_event_type = GX_EVENT_PEN_DOWN;
		break;
	case SF_TOUCH_PANEL_EVENT_UP:
		gx_event->gx_event_type = GX_EVENT_PEN_UP;
		break;
	case SF_TOUCH_PANEL_EVENT_HOLD:
	case SF_TOUCH_PANEL_EVENT_MOVE:
		gx_event->gx_event_type = GX_EVENT_PEN_DRAG;
		break;
	case SF_TOUCH_PANEL_EVENT_INVALID:
		send_event = false;
		break;
	default:
		break;
	}

	if (send_event)
	{
		/** Send event to GUI */
		gx_event->gx_event_sender = GX_ID_NONE;
		gx_event->gx_event_target = 0;
		gx_event->gx_event_display_handle = 0;

		gx_event->gx_event_payload.gx_event_pointdata.gx_point_x = p_touch_payload->x;

#if defined(BSP_BOARD_S7G2_SK)
		gx_event->gx_event_payload.gx_event_pointdata.gx_point_y = (GX_VALUE)(320 - p_touch_payload->y);  // SK-S7G2
#else
		gx_event->gx_event_payload.gx_event_pointdata.gx_point_y = p_touch_payload->y;  // DK-S7G2, PE-HMI1
#endif
	}

	return send_event;
}

#if defined(BSP_BOARD_S7G2_SK)
void g_lcd_spi_callback(spi_callback_args_t * p_args)
{
    (void)p_args;
    tx_semaphore_ceiling_put(&g_main_semaphore_lcdc, 1);
}
#endif

void time_int_callback(timer_callback_args_t * p_args)
{
    SSP_PARAMETER_NOT_USED(p_args);
    result_status = ADC_HAL_channel_read(0, &adc_result);
    vin_ant2=vin_ant1;
    vin_ant1=vin;
    vin=adc_result;

    vout_ant2=vout_ant1;
    vout_ant1=vout;

    vout=b0*vin+b1*vin_ant1+b2*vin_ant2-a1*vout_ant1-a2*vout_ant2;
    media_R = vout;
}

void toggle_led (bsp_led_t led)
{
    bsp_leds_t leds;
    ioport_level_t level;

    R_BSP_LedsGet(&leds);

    /* Toggle LED */
    g_ioport.p_api->pinRead(leds.p_leds[led], &level);

    if (IOPORT_LEVEL_HIGH == level)
    {
        level = IOPORT_LEVEL_LOW;
    } else
    {
        level = IOPORT_LEVEL_HIGH;
    }

    g_ioport.p_api->pinWrite(leds.p_leds[led], level);
}
