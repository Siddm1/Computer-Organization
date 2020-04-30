#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/* username: sdmahade
   Name: Siddhesh Mahadeshwar
   Program Description: (Program 2: Computer Organization): This file is the header file for the memory device
   for the emulator. It is responsible for defining all the prototypes for any functions that the main .c
   memory device may need.
 */

#ifndef MEMORY_H
#define MEMORY_H


// The “create” command accepts a single integer parameter which indicates the size of the memory in bytes.
void create(int size);

// The “reset” command causes all of the allocated memory to be set to zero.
void memoryReset();

// The dump command shows the contents of memory starting at address <address>, and continuing for <count> bytes.
void memoryDump(int hexAddress, int hexCount);

// The set commands initializes memory to a user supplied set of values. The “hex address” specifies where to 
// begin setting memory values, “hex count” is how many bytes will be assigned, and is followed by “hex count” 
// number of hex bytes, separated by a single space.
void set(int hexAddress, int hexCount, int memA[]);

// Starts one tick for the memory.
void memoryStartTick();

// Does the cycle work for the memory device.
void memoryDoCycleWork();

// Check if memory needs more work to be done.
bool memoryMoreWork();

// set memory value function which will set paramter 
void setMemoryValue(unsigned int ttt, unsigned int regsss);

// Returns the value stored at the given index in the parameter
unsigned int getMemoryValue(unsigned int index);

// Free variables function
void freeVariables();

#endif