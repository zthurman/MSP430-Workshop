/**
 * MSP430 Workshop: Chapter 3 GPIO - Lab 4
 *
 * MSP430FR6989
 *
 * myClocks.c
 */

#include <driverlib.h>
#include "myClocks.h"

#define LF_CRYSTAL_FREQUENCY_IN_HZ      32768
#define HF_CRYSTAL_FREQUENCY_IN_HZ      0

uint32_t myACLK     = 0;
uint32_t mySMCLK    = 0;
uint32_t myMCLK     = 0;

void initClocks(void)
{
    CS_setExternalClockSource(
            LF_CRYSTAL_FREQUENCY_IN_HZ,
            HF_CRYSTAL_FREQUENCY_IN_HZ
    );

    myACLK  = CS_getACLK();
    mySMCLK = CS_getSMCLK();
    myMCLK  = CS_getMCLK();

    CS_initClockSignal(
            CS_ACLK,
            CS_VLOCLK_SELECT,
            CS_CLOCK_DIVIDER_1
    );

    CS_setDCOFreq(
            CS_DCORSEL_1,
            CS_DCOFSEL_3
    );

    CS_initClockSignal(
            CS_SMCLK,
            CS_DCOCLK_SELECT,
            CS_CLOCK_DIVIDER_1
    );

    // DCOCLK
//    CS_initClockSignal(
//            CS_MCLK,
//            CS_DCOCLK_SELECT,
//            CS_CLOCK_DIVIDER_1
//    );

    // VLOCLK
    CS_initClockSignal(
            CS_MCLK,
            CS_VLOCLK_SELECT,
            CS_CLOCK_DIVIDER_1
    );

    myACLK  = CS_getACLK();
    mySMCLK = CS_getSMCLK();
    myMCLK  = CS_getMCLK();
}
