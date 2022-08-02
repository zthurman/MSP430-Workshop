/**
 * MSP430 Workshop: Chapter 6 Timers - Lab 6
 *
 * MSP430FR6989
 *
 * myClocks.h
 */


#ifndef MYCLOCKS_H_
#define MYCLOCKS_H_

//***** Prototypes ************************************************************
void initClocks(void);

//***** Defines ***************************************************************
#define LF_CRYSTAL_FREQUENCY_IN_HZ     32768
#define HF_CRYSTAL_FREQUENCY_IN_HZ     0                                        // FR6989 Launchpad does not ship with HF Crystal populated

#define myMCLK_FREQUENCY_IN_HZ         8000000
#define mySMCLK_FREQUENCY_IN_HZ        8000000
#define myACLK_FREQUENCY_IN_HZ         32768


#endif /* MYCLOCKS_H_ */

