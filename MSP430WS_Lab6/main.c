/**
 * MSP430 Workshop: Chapter 6 Timers - Lab 6
 *
 * MSP430FR6989
 *
 * main.c
 */


#include <driverlib.h>
#include "myGpio.h"
#include "myClocks.h"
#include "myTimers.h"


int main(void)
{
    WDT_A_hold( WDT_A_BASE );

    initGPIO();

    initClocks();

    initTimers();

    __bis_SR_register(GIE);

    while(1)
    {
        __no_operation();
    }
}
