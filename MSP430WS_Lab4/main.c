/**
 * MSP430 Workshop: Chapter 3 GPIO - Lab 3
 *
 * MSP430FR6989
 *
 * main.c
 */

#include <driverlib.h>

void myClkInit(void)
{
    UCS_clockSignalInit(
            UCS_BASE,
            UCS_ACLK,
            UCS_REFOCLK_SELECT,
            UCS_CLOCK_DIVIDER_1
            );
}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	return 0;
}
