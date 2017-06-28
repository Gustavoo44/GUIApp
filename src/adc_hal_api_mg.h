/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
* this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2017 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/**********************************************************************************************************************
 * File Name    : adc_hal_api_mg.h
 * Description  : The file contains api calls form ADC HAL
 * Quick tips to customize this example according to user's requirement:
 *       1) Update the module name with that added in the SSP Configurator (eg. g_adc0)
 *********************************************************************************************************************/


#ifndef ADC_HAL_API_MG_H_
#define ADC_HAL_API_MG_H_

ssp_err_t ADC_HAL_open(void);
ssp_err_t ADC_HAL_scan_config(void);
ssp_err_t ADC_HAL_scan_start(void);
ssp_err_t ADC_HAL_channel_read(adc_register_t adc_channel_register, adc_data_size_t *result);
ssp_err_t ADC_HAL_scan_stop(void);
ssp_err_t ADC_HAL_close(void);
ssp_err_t ADC_HAL_getScan_status(void);

/**
 *  @brief This function initializes ADC HAL driver.
 *  @param none.
 *  @return ssp_err_t error type.
 * */
ssp_err_t ADC_HAL_open(void)
{
    return (g_adc0.p_api->open(g_adc0.p_ctrl, g_adc0.p_cfg));
}

/**
 *  @brief This function configures the ADC channels
 *  @param none.
 *  @return ssp_err_t error type.
 * */
ssp_err_t ADC_HAL_scan_config(void)
{
    return (g_adc0.p_api->scanCfg(g_adc0.p_ctrl, g_adc0.p_channel_cfg));
}

/**
 *  @brief This function starts the ADC scan
 *  @param none.
 *  @return ssp_err_t error type.
 * */
ssp_err_t ADC_HAL_scan_start(void)
{
    return (g_adc0.p_api->scanStart(g_adc0.p_ctrl));
}
/**
 *  @brief This function reads the ADC conversion result
 *  @param adc_channel_register Register type .
 *  @return ssp_err_t error type.
 * */
ssp_err_t ADC_HAL_channel_read(adc_register_t adc_channel_register, adc_data_size_t *result)
{
    return (g_adc0.p_api->read(g_adc0.p_ctrl, adc_channel_register, result));
}

/**
 *  @brief This function gets the status of ADC scan
 *  @param none.
 *  @return ssp_err_t error type.
 * */
ssp_err_t ADC_HAL_getScan_status()
{
    return (g_adc0.p_api->scanStatusGet(g_adc0.p_ctrl));
}

/**
 *  @brief This function stop the ADC scan
 *  @param none.
 *  @return ssp_err_t error type.
 * */
ssp_err_t ADC_HAL_scan_stop(void)
{
    return (g_adc0.p_api->scanStop(g_adc0.p_ctrl));
}

/**
 *  @brief This function closes the ADC unit
 *  @param none.
 *  @return ssp_err_t error type.
 * */
ssp_err_t ADC_HAL_close(void)
{
   return( g_adc0.p_api->close(g_adc0.p_ctrl));
}


#endif /* ADC_HAL_API_MG_H_ */
