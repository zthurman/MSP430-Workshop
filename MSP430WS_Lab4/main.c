/**
 * MSP430 Workshop: Chapter 4 Clocks - Lab 4
 *
 * MSP430FR6989
 *
 * main.c
 */

#include <driverlib.h>
#include "myClocks.h"

void initGPIO(void);

#define ONE_SECOND  800000
#define HALF_SECOND 400000

int main(void)
{
    // Stop watchdog timer
	WDT_A_hold(WDT_A_BASE);
	
	initGPIO();

	initClocks();

	while(1)
	{
	    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
	    _delay_cycles(ONE_SECOND);
	    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
	    _delay_cycles(ONE_SECOND);
	}
}

void initGPIO(void)
{
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
    // Unlock pins after setting all used gpio registers
    PMM_unlockLPM5();
}
