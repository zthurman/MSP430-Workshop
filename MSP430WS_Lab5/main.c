/**
 * MSP430 Workshop: Chapter 5 Interrupts - Lab 5
 *
 * MSP430FR6989
 *
 * main.c
 */

#include <driverlib.h>

void initGPIO(void);


void main (void)
{
    // Stop watchdog timer
//    WDT_A_hold( WDT_A_BASE );

    // Initialize GPIO
    initGPIO();

    WDT_A_initIntervalTimer( WDT_A_BASE,
                             WDT_A_CLOCKSOURCE_ACLK,
                             WDT_A_CLOCKDIVIDER_8192);
//                             WDT_A_CLOCKDIVIDER_32K);

    WDT_A_start( WDT_A_BASE );

    //Enable Watchdog Interupt
    SFR_clearInterrupt( SFR_WATCHDOG_INTERVAL_TIMER_INTERRUPT );
    SFR_enableInterrupt( SFR_WATCHDOG_INTERVAL_TIMER_INTERRUPT );

    // Initialize clocks
//    initClocks();

//    __bis_SR_register( GIE );                                                   // Enable interrupts globally
    __bis_SR_register( LPM3_bits + GIE );

    while(1) {
        __no_operation();                                                       // Placeholder for while loop (not required)
    }
}


void initGPIO(void) {

    // Set pin P1.0 to output direction and turn LED off
    GPIO_setAsOutputPin( GPIO_PORT_P1, GPIO_PIN0 );                             // Red LED (LED1)
//    GPIO_setOutputLowOnPin( GPIO_PORT_P1, GPIO_PIN0 );

    // Set pin P9.7 to output direction and turn LED off
    GPIO_setAsOutputPin( GPIO_PORT_P9, GPIO_PIN7 );                             // Green LED (LED2)
    GPIO_setOutputLowOnPin( GPIO_PORT_P9, GPIO_PIN7 );

    // Unlock pins (required for most FRAM devices)
    // Unless waking from LPMx.5, this should be done before clearing and enabling GPIO port interrupts
    PMM_unlockLPM5();

    // Set P1.1 as input with pull-up resistor (for push button 1)
    //  configure interrupt on low-to-high transition
    //  and then clear flag and enable the interrupt
    GPIO_setAsInputPinWithPullUpResistor( GPIO_PORT_P1, GPIO_PIN1 );
    GPIO_selectInterruptEdge ( GPIO_PORT_P1, GPIO_PIN1, GPIO_LOW_TO_HIGH_TRANSITION );
    GPIO_clearInterrupt ( GPIO_PORT_P1, GPIO_PIN1 );
    GPIO_enableInterrupt ( GPIO_PORT_P1, GPIO_PIN1 );

    // Set P1.2 as input with pull-up resistor (for push button 2)
    //  configure interrupt on low-to-high transition
    //  and then clear flag and enable the interrupt
    GPIO_setAsInputPinWithPullUpResistor( GPIO_PORT_P1, GPIO_PIN2 );
    GPIO_selectInterruptEdge ( GPIO_PORT_P1, GPIO_PIN2, GPIO_LOW_TO_HIGH_TRANSITION );
    GPIO_clearInterrupt ( GPIO_PORT_P1, GPIO_PIN2 );
    GPIO_enableInterrupt ( GPIO_PORT_P1, GPIO_PIN2 );

//    // Set LFXT (low freq crystal pins) to crystal input (rather than GPIO)
//    // Since HFXT is not used, we don't need to set these pins. But for the
//    // record, they are:
//    //              GPIO_PIN6                            // HFXTIN on PJ.6
//    //              GPIO_PIN7                            // HFXOUT on PJ.7
//    GPIO_setAsPeripheralModuleFunctionInputPin(
//            GPIO_PORT_PJ,
//            GPIO_PIN4 +                                  // LFXIN  on PJ.4
//            GPIO_PIN5 ,                                  // LFXOUT on PJ.5
//            GPIO_PRIMARY_MODULE_FUNCTION
//    );

//    // Output the MCLK, ACLK signals to their respective pins - which allows you to
//    // watch them with a logic analyzer (MCLK on P4.0, ACLK on P4.1).
//    // Note, all three clocks (MCLK, SMCLK, ACLK) are each available on 4 different I/O pins; though,
//    // we're only showing these two because they are the only ones routed to BoosterPack pins
//    GPIO_setAsPeripheralModuleFunctionOutputPin(
//                    GPIO_PORT_P4,
//                    GPIO_PIN0 +                          // MCLK on P4.0
//                    GPIO_PIN1 ,                          // ACLK on P4.1
//                    GPIO_TERNARY_MODULE_FUNCTION
//    );
}


#pragma vector=PORT1_VECTOR
__interrupt void pushbutton_ISR (void)
{
        // Toggle the LED on/off (initial code; moved into switch statement below)
        //GPIO_toggleOutputOnPin( GPIO_PORT_P1, GPIO_PIN0 );

    switch( __even_in_range( P1IV, P1IV_P1IFG7 )) {
        case P1IV_NONE:   break;                               // None
        case P1IV_P1IFG0:                                      // Pin 0
             __no_operation();
             break;
       case P1IV_P1IFG1:                                       // Pin 1 (button 1)
//            GPIO_toggleOutputOnPin( GPIO_PORT_P1, GPIO_PIN0 ); // Toggle LED 1
           __no_operation();
           break;
       case P1IV_P1IFG2:                                       // Pin 2 (button 2)
           GPIO_toggleOutputOnPin( GPIO_PORT_P9, GPIO_PIN7 );  // Toggle on LED 2
            break;
       case P1IV_P1IFG3:                                       // Pin 3
            __no_operation();
            break;
       case P1IV_P1IFG4:                                       // Pin 4
            __no_operation();
            break;
       case P1IV_P1IFG5:                                       // Pin 5
            __no_operation();
            break;
       case P1IV_P1IFG6:                                       // Pin 6
            __no_operation();
            break;
       case P1IV_P1IFG7:                                       // Pin 7
            __no_operation();
            break;
       default:   _never_executed();
    }
}

//Watchdog Timer interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = WDT_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(WDT_VECTOR)))
#endif
void WDT_A_ISR(void)
{
    //Toggle P1.0
    GPIO_toggleOutputOnPin(
        GPIO_PORT_P1,
        GPIO_PIN0
    );
}
