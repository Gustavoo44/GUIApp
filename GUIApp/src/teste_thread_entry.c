#include "teste_thread.h"

/* Teste_Thread entry function */
void teste_thread_entry(void)
{
    g_timer1.p_api->open(g_timer1.p_ctrl, g_timer1.p_cfg);
    g_timer1.p_api->dutyCycleSet(g_timer1.p_ctrl, 0, TIMER_PWM_UNIT_PERCENT, 50);
    while (1)
    {
        g_ioport.p_api->pinWrite( IOPORT_PORT_01_PIN_12, IOPORT_LEVEL_LOW);
        g_ioport.p_api->pinWrite( IOPORT_PORT_01_PIN_13, IOPORT_LEVEL_HIGH);
        g_timer1.p_api->dutyCycleSet(g_timer1.p_ctrl, 100, TIMER_PWM_UNIT_PERCENT, 0);
        tx_thread_sleep (1000);
        g_ioport.p_api->pinWrite( IOPORT_PORT_01_PIN_13, IOPORT_LEVEL_LOW);
        g_ioport.p_api->pinWrite( IOPORT_PORT_01_PIN_12, IOPORT_LEVEL_HIGH);
        g_timer1.p_api->dutyCycleSet(g_timer1.p_ctrl, 50, TIMER_PWM_UNIT_PERCENT, 0);
        tx_thread_sleep (1000);
    }
}
