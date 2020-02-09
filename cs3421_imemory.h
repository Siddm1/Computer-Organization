#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


/* username: sdmahade
   Name: Siddhesh Mahadeshwar
   Program Description: (Program 1: Computer Organization): This file is the C file for the instruction memory device
   for the emulator. It is responsible for defining all the prototypes for any functions that the main .c
   memory device may need.
 */

#ifndef IMEMORY_H
#define IMEMORY_H

 // The “create” command accepts a single integer parameter which indicates the size of the memory in bytes.
void icreate(int size);

// The “reset” command causes all of the allocated memory to be set to zero.
void imemoryReset();

// The dump command shows the contents of memory starting at address <address>, and continuing for <count> bytes.
void imemoryDump(int hexAddress, int hexCount);

unsigned int getiMemoryValue(unsigned int index);

// The set commands initializes memory to a user supplied set of values. The “hex address” specifies where to 
// begin setting memory values, “hex count” is how many bytes will be assigned, and is followed by “hex count” 
// number of hex bytes, separated by a single space.
void iset(int hexAddress, char* filename);

// Starts one tick for the memory.
void imemoryStartTick();

// Does the cycle work for the memory device.
void imemoryDoCycleWork();

#endif