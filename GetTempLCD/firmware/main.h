#ifndef _MAIN_H
#define _MAIN_H
//--------------------------------------------------------------
// WILL NEED TO EDIT THIS SECTION FOR EVERY PROJECT
//--------------------------------------------------------------
// Must include the appropriate microcontroller header file here
#include <at89x52.h>

// Oscillator / resonator frequency (in Hz) e.g. (11059200UL)
#define OSC_FREQ (11059200UL)

typedef unsigned char tByte;
typedef unsigned int tWord;
typedef unsigned long tLong;


#define OSC_PER_INST (12)

#define INTERRUPT_Timer_0_Overflow 1
#define INTERRUPT_Timer_1_Overflow 3
#define INTERRUPT_Timer_2_Overflow 5


#endif