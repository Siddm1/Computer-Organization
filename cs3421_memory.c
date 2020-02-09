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
   Program Description: (Program 1: Computer Organization): This file is the C file for the memory device
   for the emulator. It is responsible for defining all the prototypes for any functions that the main .c
   memory device may need.
 */


unsigned int* memArray;
int size;

 // The “create” command accepts a single integer parameter which indicates the size of the memory in bytes.
void create(int size1)
{     
    memArray = (unsigned int*)malloc(sizeof(unsigned int) * size1);
    size = size1;
}



// The “reset” command causes all of the allocated memory to be set to zero.
void memoryReset()
{
    for (int i = 0; i < size; i++)
    {
        memArray[i] = 0;
    }
}

// The dump command shows the contents of memory starting at address <address>, and continuing for <count> bytes.
void memoryDump(int hexAddress, int hexCount)
{
    printf("Addr 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");

    int j = 16; // tracks progress on the line
    bool space = false;
    int buffer = hexAddress % 16; //amount to skip

    if (buffer != 0)
    {
        space = true;
    }

    for (int i = hexAddress; i < hexAddress + hexCount; i++)
    {
        if (j == 16)
        {
            printf("\n");
            int mod = i % 16;
            int current = i - mod;

            printf("0x%02X ", current);
            j = 0;
        }

        if (space == true)
        {
            for (int k = 0; k < buffer; k++)
            {
                printf("   ");
            }
            space = false;
            j += buffer;
        }

        printf("%X ", memArray[i]);
        j++;
       
    }
    printf("\n\n");
    
}

// The set commands initializes memory to a user supplied set of values. The “hex address” specifies where to 
// begin setting memory values, “hex count” is how many bytes will be assigned, and is followed by “hex count” 
// number of hex bytes, separated by a single space.
void set(int hexAddress, int hexCount, int memA[])
{
    int a = 0;

    for (int i = hexAddress; i < hexAddress + hexCount; i++)
    {
        memArray[i] = memA[a]; // memory array assigned to values at location starting at hexAddress from input array
        a++;
    }
}

// Returns the memory value at the given index in the memory array
unsigned int getMemoryValue(unsigned int index)
{
    unsigned int memoryValue = memArray[index]; 

    return memoryValue;
}

// Starts one tick for the memory.
void memoryStartTick()
{
    
}

// Does the cycle work for the memory device.
void memoryDoCycleWork()
{

}

// Check if memory needs more work to be done.
bool memoryMoreWork()
{
    return false;
}


// frees allocated memory array
void freeVariables()
{
    free(memArray);
}

