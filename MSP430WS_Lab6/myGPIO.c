/**
 * MSP430 Workshop: Chapter 6 Timers - Lab 6
 *
 * MSP430FR6989
 *
 * myGPIO.c
 */


#include <driverlib.h>
#include "myGpio.h"

void initGPIO(void) {

    //**************************************************************************
    // Configure LaunchPad LEDs
    //**************************************************************************
    // Set pin P1.0 to output direction and turn LED off
    GPIO_setAsOutputPin( GPIO_PORT_P1, GPIO_PIN0 );                             // Red LED (LED1)
    GPIO_setOutputLowOnPin( GPIO_PORT_P1, GPIO_PIN0 );

    // Set pin P9.7 to output direction and turn LED off
    GPIO_setAsOutputPin( GPIO_PORT_P9, GPIO_PIN7 );                             // Green LED (LED2)
    GPIO_setOutputLowOnPin( GPIO_PORT_P9, GPIO_PIN7 );

    //**************************************************************************
    // Unlock pins (required for most FRAM devices)
    // Unless waking from LPMx.5, this should be done before clearing and enabling GPIO port interrupts
    //**************************************************************************
    PMM_unlockLPM5();


    //**************************************************************************
    // Configure external crystal pins
    //**************************************************************************
    // Set LFXT (low freq crystal pins) to crystal input (rather than GPIO)
    // Since HFXT is not used, we don't need to set these pins. But for the
    // record, they are:
    //              GPIO_PIN6                            // HFXTIN on PJ.6
    //              GPIO_PIN7                            // HFXOUT on PJ.7
    GPIO_setAsPeripheralModuleFunctionInputPin(
            GPIO_PORT_PJ,
            GPIO_PIN4 +                                  // LFXIN  on PJ.4
            GPIO_PIN5 ,                                  // LFXOUT on PJ.5
            GPIO_PRIMARY_MODULE_FUNCTION
    );
}
