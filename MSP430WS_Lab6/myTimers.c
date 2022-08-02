/**
 * MSP430 Workshop: Chapter 6 Timers - Lab 6
 *
 * MSP430FR6989
 *
 * myTimers.c
 */

#include <driverlib.h>
#include "myTimers.h"


void initTimers(void)
{
    //*************************************************************************
    // 1. Setup Timer (TAR, TACTL)
    //    TimerA1 in Continuous mode using ACLK
    //    Toggle LED2 (Green) on/off every 2 seconds using timer interrupt (TA1IFG)
    //*************************************************************************
    Timer_A_initContinuousModeParam initContParam = { 0 };
        initContParam.clockSource =                 TIMER_A_CLOCKSOURCE_ACLK;  // Use ACLK (slower clock)
        initContParam.clockSourceDivider =          TIMER_A_CLOCKSOURCE_DIVIDER_1;  // Input clock = ACLK / 1 = 32KHz
        initContParam.timerInterruptEnable_TAIE =   TIMER_A_TAIE_INTERRUPT_ENABLE;  // Enable TAR -> 0 interrupt
        initContParam.timerClear =                  TIMER_A_DO_CLEAR;               // Clear TAR & clock divider
        initContParam.startTimer =                  false;                          // Don't start the timer, yet
    Timer_A_initContinuousMode( TIMER_A1_BASE, &initContParam );

    //*************************************************************************
    // 2. Setup Capture & Compare features
    //*************************************************************************
    // This example does not use these features

    //*************************************************************************
    // 3. Clear/enable interrupt flags and start timer
    //*************************************************************************
    // Clear and enable interrupt flags inside TimerA peripheral
    Timer_A_clearTimerInterrupt( TIMER_A1_BASE );                               // Clear TA1IFG

    //This enable was already done by the configureContinuousMode function
    //Timer_A_enableInterrupt( TIMER_A1_BASE );                                     // Enable interrupt on counter (TAR) rollover

    // Start the timer; make sure you specify the correct counting mode
    Timer_A_startCounter(
        TIMER_A1_BASE,
        TIMER_A_CONTINUOUS_MODE
    );
}

//*****************************************************************************
// Interrupt Service Routine
//*****************************************************************************
#pragma vector=TIMER1_A1_VECTOR
__interrupt void timer1_ISR (void)
{
    //**************************************************************************
    // 4. Timer ISR and vector
    //**************************************************************************
    switch( __even_in_range( TA1IV, TA1IV_TAIFG )) {
     case TA1IV_NONE: break;                 // (0x00) None
     case TA1IV_TACCR1:                      // (0x02) CCR1 IFG
          _no_operation();
           break;
     case TA1IV_TACCR2:                      // (0x04) CCR2 IFG
          _no_operation();
           break;
     case TA1IV_3: break;                    // (0x06) Reserved
     case TA1IV_4: break;                    // (0x08) Reserved
     case TA1IV_5: break;                    // (0x0A) Reserved
     case TA1IV_6: break;                    // (0x0C) Reserved
     case TA1IV_TAIFG:                       // (0x0E) TA1IFG - TAR overflow
          // Toggle LED2 (Green) LED on/off
          GPIO_toggleOutputOnPin( GPIO_PORT_P9, GPIO_PIN7 );
          break;
     default: _never_executed();
    }
}

