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
#include "cs3421_iodev.h"
#include "cs3421_cache.h"

/* username: sdmahade
   Name: Siddhesh Mahadeshwar
   Program Description: (Program 2: Computer Organization): This file is the C file for the clock device
   for the emulator. It is responsible for the implementation of all the prototype functions defined 
   initially in the header file.
 */

int count = 0;

int currentTick = 0;

Clock clock;

// resets the clock for all devices to 0
void clockReset()
{
    clock.count = 0;
    currentTick = 0;
}



// returns the current tick number
int getCurrentTickN()
{
    return currentTick;
}

// adds ticks to the clock counter
void tick(unsigned int amount)
{
    currentTick = 0;
    clock.count += amount;

    if (count == 0)
    {
        cpuStartTick();
        count++;
    }

    unsigned int i;

    for (i = 0; i < amount; i++) // runs cpuCycle and memoryCycle for the number of ticks given
    {
        currentTick++;
        ioRead();
        ioWrite();
        cpuDoCycleWork2(); 
        memoryDoCycleWork();
        imemoryDoCycleWork();
        TCdoCycleWork();
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

