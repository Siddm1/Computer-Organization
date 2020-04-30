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
#include "cs3421_cache.h"
#include "cs3421_iodev.h"

/* username: sdmahade
   Name: Siddhesh Mahadeshwar
   Program Description: (Program 2: Computer Organization): This file is the C file for the iMemory device
   for the emulator. It is responsible for the implementation of all the prototype functions defined 
   initially in the header file.
 */

unsigned int* iMemArray;
int size;
unsigned int instructionValue = 0;
unsigned int indexing = 0;


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
    printf("Addr     0     1     2     3     4     5     6     7");

    int j = 8; // tracks progress on the line
    bool space = false;
    int buffer = hexAddress % 8; //amount to skip

    if (buffer != 0)
    {
        space = true;
    }

    for (int i = hexAddress; i < hexAddress + hexCount; i++)
    {
        if (j == 8)
        {
            printf("\n");
            int mod = i % 8;
            int current = i - mod;

            printf("0x%02X ", current);
            j = 0;
        }

        if (space == true)
        {
            for (int k = 0; k < buffer; k++)
            {
                printf("      ");
            }
            space = false;
            j += buffer;
        }

        printf("%05X ", iMemArray[i]);
        j++;

    }
    printf("\n\n");
}

// The set commands initializes memory to a user supplied set of values. The “hex address” specifies where to 
// begin setting memory values, “hex count” is how many bytes will be assigned, and is followed by “hex count” 
// number of hex bytes, separated by a single space.
bool iset(int hexAddress, char* filename)
{
    // creating a file pointer to access a file entered as taken in as parameter for this function
    FILE* fp = fopen(filename, "r");

    // checks if the file pointer is possible, if not, returns false
    if (fp == NULL)
    {
        return false;
    }

    int index = hexAddress;
    int count = 0;
    char* input = "";
    input = malloc(sizeof(char*));
    char hex[5]; // char array variable to store the chars read in from instruction set

    while (fscanf(fp, "%s", input) != EOF)
    {
        count++;
        for (int i = 0; i < 5; i++)
        {
            hex[i] = input[i];
        }
        long converted = strtol(hex, NULL, 16);
        iMemArray[index] = converted; // sets the converted version from hex to int into the iMemory Array
        index++;
    }

    fclose(fp); // close the file pointer
    free(input); // free variables
    return true;
}


// Starts one tick for the memory.
void imemoryStartTick()
{

}

// Does the cycle work for the memory device.
void imemoryDoCycleWork()
{

}

// frees allocated memory array
void ifreeVariables()
{
    free(iMemArray);
}

