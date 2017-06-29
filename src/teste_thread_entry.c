#include "teste_thread.h"

/* Teste_Thread entry function */
void teste_thread_entry(void)
{
    /* TODO: add your own code here */
    while (1)
    {
        toggle_led(0);
        tx_thread_sleep (100);
    }
}
