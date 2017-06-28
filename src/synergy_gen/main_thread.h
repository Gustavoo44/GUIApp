/* generated thread header file - do not edit */
#ifndef MAIN_THREAD_H_
#define MAIN_THREAD_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus 
extern "C" void main_thread_entry(void);
#else 
extern void main_thread_entry(void);
#endif
#include "r_adc.h"
#include "r_adc_api.h"
#include "r_gpt.h"
#include "r_timer_api.h"
#include "r_icu.h"
#include "r_external_irq_api.h"
#include "sf_external_irq.h"
#include "r_dtc.h"
#include "r_transfer_api.h"
#include "r_riic.h"
#include "r_i2c_api.h"
#include "sf_touch_panel_i2c.h"
#include "sf_touch_panel_api.h"
#include "r_sci_spi.h"
#include "r_spi_api.h"
#ifdef __cplusplus
extern "C"
{
#endif
/** ADC on ADC Instance. */
extern const adc_instance_t g_adc0;
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer0;
#ifndef time_int_callback
void time_int_callback(timer_callback_args_t * p_args);
#endif
/* External IRQ on ICU Instance. */
extern const external_irq_instance_t g_touch_irq;
#ifndef NULL
void NULL(external_irq_callback_args_t * p_args);
#endif
/** SF External IRQ on SF External IRQ Instance. */
extern const sf_external_irq_instance_t g_sf_touch_irq;
/* Transfer on DTC Instance. */
extern const transfer_instance_t g_transfer3;
#ifndef NULL
void NULL(transfer_callback_args_t * p_args);
#endif
/* Transfer on DTC Instance. */
extern const transfer_instance_t g_transfer2;
#ifndef NULL
void NULL(transfer_callback_args_t * p_args);
#endif
extern const i2c_cfg_t g_i2c_cfg;
/** I2C on RIIC Instance. */
extern const i2c_master_instance_t g_i2c;
#ifndef NULL
void NULL(i2c_callback_args_t * p_args);
#endif
/** SF Touch Panel on SF Touch Panel I2C Instance. */
extern const sf_touch_panel_instance_t g_sf_touch_panel_i2c;
/** Messaging Framework Instance */
extern const sf_message_instance_t g_sf_message0;
void g_sf_touch_panel_i2c_err_callback(void * p_instance, void * p_data);
extern const spi_cfg_t g_spi_lcdc_cfg;
/** SPI on SCI Instance. */
extern const spi_instance_t g_spi_lcdc;
#ifndef g_lcd_spi_callback
void g_lcd_spi_callback(spi_callback_args_t * p_args);
#endif
extern TX_SEMAPHORE g_main_semaphore_lcdc;
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* MAIN_THREAD_H_ */
