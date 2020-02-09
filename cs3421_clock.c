#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "cs3421_clock.h"
#include "cs3421_cpu.h"
#include "cs3421_memory.h"
#include "cs3421_emul.h"
#include "cs3421_imemory.h"

/* username: sdmahade
   Name: Siddhesh Mahadeshwar
   Program Description: (Program 1: Computer Organization): This file is the C file for the clock device
   for the emulator. It is responsible for defining all the prototypes for any functions that the main .c
   clock device may need.
 */

Clock clock;

// resets the clock for all devices to 0
void clockReset()
{
    clock.count = 0;
}

// adds ticks to the clock counter
void tick(unsigned int amount)
{
    clock.count += amount;
    cpuStartTick();
    for (unsigned int i = 1; i < clock.count + 1; i++) // runs cpuCycle and memoryCycle for the number of ticks given
    {
        cpuDoCycleWork(); 
        memoryDoCycleWork();
    }

}

int tickNumber()
{
    return clock.count; // returns the tick number a given moment when called
}

// print the ticks left in clock
void clockDump()
{ 
    printf("Clock: %u\n", clock.count); // prints the clock when called
}

