#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/* username: sdmahade
   Name: Siddhesh Mahadeshwar
   Program Description: (Program 1: Computer Organization): This file is the header file for the CPU device
   for the emulator. It is responsible for defining all the prototypes for any functions that the main .c
   CPU device may need.
 */

#ifndef CPU_H
#define CPU_H

/*
enum cpuState { IDLE, BUSY };

typedef struct
{
    cpuState state;
} CPU;
*/


// Changes the state of the CPU as required
// void changeCPUState(CPU cpu, cpuState CPUstate);

// The “set reg” command sets the value of the specified CPU register. The “reg” parameter can be the value
// RA-RH, or PC for the program counter.
void setReg(char* reg, int hexByte);

// The “reset” command causes all CPU registers (including PC) to be zero.
void cpuReset();

// The “dump” command shows the value of all of the CPU registers.
void cpuDump();

// Starts one tick for the CPU.
void cpuStartTick();

// Does the cycle work for the CPU.
void cpuDoCycleWork();

// Checks if CPU requires more work.
bool cpuMoreWork();

// Sets the state of the CPU to either idle or working based on requirement.
char* cpuState(int state);

// Returns the hexAdress read in from the emulator
int hexAddress(int addr);

#endif