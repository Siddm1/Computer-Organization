#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>                                                                          
#include <math.h>

/* username: sdmahade
   Name: Siddhesh Mahadeshwar
   Program Description: (Program 1: Computer Organization): This file is the header file for the clock device
   for the emulator. It is responsible for defining all the prototypes for any functions that the main .c
   clock device may need.
 */

#ifndef CLOCK_H
#define CLOCK_H

typedef struct
{
    unsigned int count;
} Clock;

// The tick command accepts a positive decimal integer indicating how many clock ticks should be issued to 
// attached devices. The internal counter is incremented by the specified number of ticks.
void tick(unsigned int amount);

// The reset command sets the internal counter to zero
void clockReset();

// The dump command shows “Clock: “ followed by the value of the internal clock in decimal.
void clockDump();

// returns the current tick number;
int tickNumber();

#endif
