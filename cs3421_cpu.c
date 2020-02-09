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
   Program Description: (Program 1: Computer Organization): This file is the C file for the CPU device
   for the emulator. It is responsible for defining all the prototypes for any functions that the main .c
   CPU device may need.
 */

 // Assigning space for the 8 required registers
static int registers[8];

// Initializing the program counter
int programCounter = 0;

// Initializing boolean for memory work done to false by default; can be manipulated later.
bool* memDone = false;

// Memory value pointer for memory device fetch function 
int* memValue;

// String variables of registers for comparisons
char* RA = "RA";
char* RB = "RB";
char* RC = "RC";
char* RD = "RD";
char* RE = "RE";
char* RF = "RF";
char* RG = "RG";
char* RH = "RH";
char* PC = "PC";


// The “set reg” command sets the value of the specified CPU register. The “reg” parameter can be the value
// RA-RH, or PC for the program counter.
void setReg(char* reg, int hexByte)
{
    if (strcmp(reg, PC) == 0)
    {
        programCounter = hexByte;
    }

    if (strcmp(reg, RA) == 0)
    {
        registers[0] = hexByte;
    } 

    if (strcmp(reg, RB) == 0)
    {
        registers[1] = hexByte;
    }

    if (strcmp(reg, RC) == 0)
    {
        registers[2] = hexByte;
    }

    if (strcmp(reg, RD) == 0)
    {
        registers[3] = hexByte;
    }

    if (strcmp(reg, RE) == 0)
    {
        registers[4] = hexByte;
    }

    if (strcmp(reg, RF) == 0)
    {
        registers[5] = hexByte;
    }

    if (strcmp(reg, RG) == 0)
    {
        registers[6] = hexByte;
    }

    if (strcmp(reg, RH) == 0)
    {
        registers[7] = hexByte;
    }
}

// The “reset” command causes all CPU registers (including PC) to be zero.
void cpuReset()
{
    programCounter = 0;

    for (int i = 0; i < 8; i++) // resets all registers to 0
    {
        registers[i] = 0;
    }
}

// The “dump” command shows the value of all of the CPU registers.
void cpuDump()
{
    printf("PC: 0x%02X\n", programCounter);
    printf("RA: 0x%02X\n", registers[0]);
    printf("RB: 0x%02X\n", registers[1]);
    printf("RC: 0x%02X\n", registers[2]);
    printf("RD: 0x%02X\n", registers[3]);
    printf("RE: 0x%02X\n", registers[4]);
    printf("RF: 0x%02X\n", registers[5]);
    printf("RG: 0x%02X\n", registers[6]);
    printf("RH: 0x%02X\n\n", registers[7]);

    
}

/*
{
    char* stateBusy = "busy";
    char* stateIdle = "idle";
    char* currentState = stateIdle;

    if (state == 0)
    {
        currentState = stateIdle;
    }
    else {
        currentState = stateBusy;
    }

    return currentState;
}


void changeCPUState(CPU cpu, cpuState CPUstate)
{
    
}
*/

// Starts one tick for the CPU.
void cpuStartTick()
{
    programCounter = emulatorReturn(); // sets program counter to the starting hexAddress
}

// Does the cycle work for the CPU.
void cpuDoCycleWork()
{
    if (programCounter < programCounter + tickNumber() ) // if program counter is smaller than highest values, 
    {   // shifting registers
        registers[7] = registers[6];
        registers[6] = registers[5];
        registers[5] = registers[4];
        registers[4] = registers[3];
        registers[3] = registers[2];
        registers[2] = registers[1];
        registers[1] = registers[0]; 
    }

    if (programCounter < programCounter + tickNumber() ) // sets register 0 to be the next memory value fetched in the cycle
    {
        registers[0] = getMemoryValue(programCounter);
    }

    programCounter++; // increments the program counter
    
}


// Checks if CPU requires more work.
bool cpuMoreWork()
{
    if (programCounter == tickNumber() - 1)
    {
        return false;
    }
    return false;
}


