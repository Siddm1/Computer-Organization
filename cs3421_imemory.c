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
   Program Description: (Program 1: Computer Organization): This file is the C file for the instruction memory device
   for the emulator. It is responsible for the implementation of any functions that may be needed for
   this device.
 */

unsigned int* iMemArray;
int size;

 // The “create” command accepts a single integer parameter which indicates the size of the memory in bytes.
void icreate(int size1)
{
    iMemArray = (unsigned int*)malloc(sizeof(unsigned int) * size1);
    size = size1;
}

// The “reset” command causes all of the allocated memory to be set to zero.
void imemoryReset()
{
    for (int i = 0; i < size; i++)
    {
        iMemArray[i] = 0;
    }
}

// Returns the memory value at the given index in the memory array
unsigned int getiMemoryValue(unsigned int index)
{
    unsigned int memoryValue = iMemArray[index];
    return memoryValue;
}

// The dump command shows the contents of memory starting at address <address>, and continuing for <count> bytes.
void imemoryDump(int hexAddress, int hexCount)
{

}

// The set commands initializes memory to a user supplied set of values. The “hex address” specifies where to 
// begin setting memory values, “hex count” is how many bytes will be assigned, and is followed by “hex count” 
// number of hex bytes, separated by a single space.
void iset(int hexAddress, char* filename)
{
    // creating a file pointer to access a file entered as taken in as parameter for this function
    FILE* fp = fopen(filename, "r");

    // checks if the file pointer is possible, if not, returns false
    if (fp == NULL)
    {
        return false;
    }

    int count = 0;

    char* input = "";
    input = malloc(sizeof(char*));

    char* input1 = "";
    input1 = malloc(sizeof(char*));


    // continues to scan until scanner reaches the End of File
    while (fscanf(fp, "%s", input) != EOF)
    {
        count++;
    }

    int temp[hexAddress + count];

    while (fscanf(fp, "%s", input1) != EOF)
    {
        temp[hexAddress] = input1;
    }

    for (int i = hexAddress; i < hexAddress + count; i++)
    {
        iMemArray[i] = temp[i];
    }
}


// Starts one tick for the memory.
void imemoryStartTick()
{

}

// Does the cycle work for the memory device.
void imemoryDoCycleWork()
{

}