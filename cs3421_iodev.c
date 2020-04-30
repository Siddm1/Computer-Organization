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
   Program Description: (Program 2: Computer Organization): This file is the C file for the I/O device
   for the emulator. It is responsible for the implementation of all the prototype functions defined 
   initially in the header file.
 */

typedef struct InstructionData {
    int executionTick;
    char* instr;
    int address;
    int value;
} InstructionData;

InstructionData instructions[128];

uint8_t data = 0;

// resets the I/O device
void ioReset()
{
    data = 0;
}

char* instr1 = "";


// the load method for this device which will directly load data straight to d-memory
bool ioLoad(char* filename)
{
    FILE* fp = fopen(filename, "r");

    // checks if the file pointer is possible, if not, returns false
    if (fp == NULL)
    {
        return false;
    }

    int lineNumber = 0;

    char tick[2];
    
    char address[4];
    char value[4];
    instr1 = malloc(sizeof(char*));
   
    while (fscanf(fp, "%s", tick) != EOF)
    {
        instructions[lineNumber].executionTick = atoi(tick); // scanning in the tick on which to execute
        if (fscanf(fp, "%s", instr1) == 0)
        {
            return 1;
        }
        instructions[lineNumber].instr = instr1;

        if (strcmp(instr1, "read") == 0)
        {
            if (fscanf(fp, "%s", address) == 0) // scanning in the address on which to execute
            {
                long converted = strtol(address, NULL, 16);
                instructions[lineNumber].address = converted;
                return 1;
            }
        } 
        else if (strcmp(instr1, "write") == 0) // scanning in if the instruction to execute is to write
        {
            if (fscanf(fp, "%s", address) == 0) // scans the address
            {
                return 1;
            }
            if (fscanf(fp, "%s", value) == 0) // scans the value to store at an address
            {
                return 1;
            }

            long converted2 = strtol(address, NULL, 16); // convert the address from hex to decimal 
            instructions[lineNumber].address = converted2;

            long converted3 = strtol(value, NULL, 16); // convert the value from hex to decimal
            instructions[lineNumber].value = converted3;
        }

        lineNumber++; // increments the line number being processed
    }

    fclose(fp); // close the file pointer
    return true;
}

// frees the instruction variable malloc'd
void ioFree()
{
    free(instr1);
}

// deals with the I/O reading
void ioRead()
{
    for (int i = 0; i < 32; i++)
    {
        if (getCurrentTickN() == instructions[i].executionTick) // when current tick is equal to one of the execution ticks, execute
        {
            if (strcmp(instructions[i].instr, "read") == 0) // if ticks match and instruction is read, execute the actions below
            {
                data = getMemoryValue(instructions[i].address);
            }
        }
    }
}

// deals with the I/O writing
void ioWrite()
{
    
    for (int i = 0; i < 32; i++)
    {
        if (getCurrentTickN() == instructions[i].executionTick) // when current tick is equal to one of the execution ticks, execute
        {
            if (strcmp(instructions[i].instr, "write") == 0) // if ticks match and instruction is write, execute the actions below
            {
                setMemoryValue(instructions[i].address, instructions[i].value);
            }
        }
    }
}

// dumps the I/O device
void ioDump()
{
    printf("IO Device: 0x%02X\n\n", data);
}
