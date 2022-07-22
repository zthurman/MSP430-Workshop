/**
 * MSP430 Workshop: Chapter 3 GPIO - Lab 3
 *
 * MSP430FR6989
 *
 * main.c
 */

#include <driverlib.h>

#define ONE_SECOND      800000
#define STARTUP_MODE    0

volatile unsigned short usiButton1 = 0;

int main(void)
{
	WDT_A_hold(WDT_A_BASE);	// stop watchdog timer
	
	// Lights
	GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
	GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P9, GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P9, GPIO_PIN7);

	// Button
	GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);

	PMM_unlockLPM5();       // unlock pins after setting all gpio registers

	while(1)
	{
	    usiButton1 = GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1);
	    if(usiButton1==GPIO_INPUT_PIN_LOW)
	    {
	        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
	    }
	    else
	    {
	        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
	    }
	    GPIO_setOutputHighOnPin(GPIO_PORT_P9, GPIO_PIN7);
	    _delay_cycles(ONE_SECOND);
	    GPIO_setOutputLowOnPin(GPIO_PORT_P9, GPIO_PIN7);
	    _delay_cycles(ONE_SECOND);
	}
}
