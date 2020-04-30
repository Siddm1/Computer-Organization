#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <inttypes.h>

#include "cs3421_clock.h"
#include "cs3421_cpu.h"
#include "cs3421_memory.h"
#include "cs3421_emul.h"
#include "cs3421_imemory.h"
#include "cs3421_cache.h"
#include "cs3421_iodev.h"

/* username: sdmahade
   Name: Siddhesh Mahadeshwar
   Program Description: (Program 2: Computer Organization): This file is the C file for the CPU device
   for the emulator. It is responsible for the implementation of all the prototype functions defined 
   initially in the header file.
 */

 // Assigning space for the 8 required registers
uint8_t registers[8];

// Initializing the program counter
int programCounter = 0;

// Initializing boolean for memory work done to false by default; can be manipulated later.
bool isIdle = true;

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

int TCreg = 0;
bool haltCalled = false;

int instruction = 0;
int addressInstruction = 0;
int branchType = 0;

int remainingTicks = 0;

int computedCLO = 0;

void TCdoCycleWork()
{
    if (!haltCalled)
    {
        TCreg++;
    }
}

// finds out what type of instruction is needed to be run, sw or lw
void cpuDoCycleWork2()
{
    if (isIdle)
    {
        isIdle = false;
        instruction = getiMemoryValue(programCounter);
        addressInstruction = instruction >> 17; // bit shifting to isolate just the 3 most significant bits 17th - 19th
        branchType = instruction >> 14 & 7; // shifting to obtain the branch time 14th - 16th 
        //printf("intruction type: %d branch type %d \n", addressInstruction, branchType);

        // setting remainingTicks needed for different functions
        switch (addressInstruction)
        {
        case 0: remainingTicks = 1; // for add function
            break;
        case 1: remainingTicks = 1; // for addi function
            break;
        case 2: remainingTicks = 2; // for mul function
            break;
        case 3: remainingTicks = 1; // for inv function
            break;
        case 7: remainingTicks = 1; // for halt function
            break;
        }

        if (addressInstruction == 5) // load word sets the ticks needed for specific situations when cache is on
        {
            unsigned int shiftingttt = ((instruction >> 8) & 7);

            computedCLO = (registers[shiftingttt]) / 8;
            if (isCacheEnabled())
            {
                if (getCLO() == computedCLO && isCacheValid() == 1) // cache hit situation
                {
                    remainingTicks = 1;
                }
                else if (shiftingttt == 255)
                {
                    remainingTicks = 1;
                }
                else {
                    remainingTicks = 5;
                }
            }
            else
            {
                remainingTicks = 5;
            }
        }

        if (addressInstruction == 6) // store word sets the ticks needed for specific situations when case is on
        {
            unsigned int shiftingttt = ((instruction >> 8) & 7);

            computedCLO = (registers[shiftingttt]) / 8; // calculates the offset for the cache

            if (isCacheEnabled())
            {
                if (registers[shiftingttt] == 255 && !cacheWritten())
                {
                    remainingTicks = 1;
                }
                if (registers[shiftingttt] == 255 && cacheWritten())
                {
                    remainingTicks = 5;
                }
                else if (getCLO() == computedCLO || isCacheValid() == 0) // cache hit situation
                {
                    remainingTicks = 1;
                }
                else
                {
                    remainingTicks = 5;
                }
            }
            else
            {
                remainingTicks = 5;
            }
        }

        // conditions if instruction is a branch
        if (addressInstruction == 4)
        {
            if (branchType == 0) // branch for beq
            {
                unsigned int sss = ((instruction >> 11) & 7);
                unsigned int ttt = ((instruction >> 8) & 7);

                if (registers[sss] == registers[ttt])
                {
                    remainingTicks = 2;
                }
                else {
                    remainingTicks = 1;
                }
            }

            else if (branchType == 1) // branch for bneq
            {
                unsigned int sss = ((instruction >> 11) & 7);
                unsigned int ttt = ((instruction >> 8) & 7);

                if (registers[sss] != registers[ttt])
                {
                    remainingTicks = 2;
                }
                else {
                    remainingTicks = 1;
                }
            }

            else if (branchType == 2) // branch for blt
            {
                unsigned int sss = ((instruction >> 11) & 7);
                unsigned int ttt = ((instruction >> 8) & 7);

                if (registers[sss] < registers[ttt])
                {
                    remainingTicks = 2;
                }
                else if (registers[sss] >= registers[ttt])
                {
                    remainingTicks = 1;
                }
            }
        }
    }

    // when CPU is no longer idle, the following commands will be executed
    if (!isIdle)
    {
        remainingTicks--;
        if (remainingTicks == 0) // when ticks = 0, the commands will be executed based on which is decoded in the instruction
        {
            if (addressInstruction == 0)
            {
                add(instruction);
            }
            else if (addressInstruction == 1)
            {
                addi(instruction);
            }
            else if (addressInstruction == 2)
            {
                mul(instruction);
            }
            else if (addressInstruction == 3)
            {
                inv(instruction);
            }
            else if (addressInstruction == 5)
            {
                loadWord(instruction);
            }
            else if (addressInstruction == 6)
            {
                storeWord(instruction);
            }
            else if (addressInstruction == 7)
            {
                halt(instruction);
            }
            else if (addressInstruction == 4 && branchType == 0)
            {
                beq(instruction);
            }
            else if (addressInstruction == 4 && branchType == 1)
            {
                bneq(instruction);
            }
            else if (addressInstruction == 4 && branchType == 2)
            {
                blt(instruction);
            }
            isIdle = true;
        }
    }
}


// The add function adds the source and target register words, storing the result in the destination register. All
// values should be treated as 8 bit 2's complement numbers.
void add(unsigned int instruction)
{
    unsigned int ddd = ((instruction >> 14) & 7);
    unsigned int sss = ((instruction >> 11) & 7);
    unsigned int ttt = ((instruction >> 8) & 7);

    registers[ddd] = registers[sss] + registers[ttt];

    programCounter++;
}

// The addi function adds the source register and immediate value words, storing the result in the destination register. All
// values should be treated as 8 bit 2's complement numbers.
void addi(unsigned int instruction)
{
    unsigned int ddd = ((instruction >> 14) & 7);
    unsigned int sss = ((instruction >> 11) & 7);
    unsigned int i = instruction & 255;

    registers[ddd] = registers[sss] + i;

    programCounter++;
}

// Takes the upper 4 bits and lower bits of the source register, multiplies those values together, and stores the result in
// the destination register
void mul(unsigned int instruction)
{
    unsigned int ddd = ((instruction >> 14) & 7);
    unsigned int sss = ((instruction >> 11) & 7);

    unsigned int upper = (registers[sss] >> 4) & 15;
    unsigned int lower = (registers[sss] & 15);

    registers[ddd] = upper * lower;

    programCounter++;
}

// Inverts all the bits in the source register word, storing the result in the destination register.
void inv(unsigned int instruction)
{
    unsigned int ddd = ((instruction >> 14) & 7);
    unsigned int sss = ((instruction >> 11) & 7);

    registers[ddd] = ~(registers[sss]);

    programCounter++;
}

// The branch if equal function: if the words in the source and target registers are equal, assign the PC to the immediate
// specified imemory address, otherwise, increment the PC. 
void beq(unsigned int instruction)
{
    unsigned int sss = ((instruction >> 11) & 7);
    unsigned int ttt = ((instruction >> 8) & 7);
    unsigned int i = instruction & 255;

    if (registers[sss] == registers[ttt])
    {
        programCounter = i;
    }
    else {
        programCounter++;
    }
}

// The brance if not equal function: If the words in the source and target register are not equal, assign the PC to the
// immediate-specified imemory address, otherwise increment the PC. 
void bneq(unsigned int instruction)
{
    unsigned int sss = ((instruction >> 11) & 7);
    unsigned int ttt = ((instruction >> 8) & 7);
    unsigned int i = instruction & 255;

    if (registers[sss] != registers[ttt])
    {
        programCounter = i;
    }
    else {
        programCounter++;
    }
}

// The branch if less than function: if the word in the source register is less than the word in the target registers, assign
// the PC to the immeidate-specified imemory address, otherwise increment the PC.
void blt(unsigned int instruction)
{
    unsigned int sss = ((instruction >> 11) & 7);
    unsigned int ttt = ((instruction >> 8) & 7);
    unsigned int i = instruction & 255;

    if (registers[sss] < registers[ttt])
    {
        programCounter = i;
    }
    else {
        programCounter++;
    }
}

// Halt execution of the processor after incrementing PC. After halting, the CPU will ignore all future clock ticks, but will
// cooperate in supporting all parser commands such as "cpu dump";
void halt()
{
    programCounter++;
    clockReset();
    haltCalled = true;
    TCreg++;
}

// load word function which will bit shift and mask to obtain correct values and then shift register ddd to the memory value
// stored at the value of register at index ttt.
void loadWord(unsigned int instruction)
{
    unsigned int shiftingddd = ((instruction >> 14) & 7);

    unsigned int shiftingttt = ((instruction >> 8) & 7);

    registers[shiftingddd] = cacheRequestLW(registers[shiftingttt]);

    programCounter++;
}

// store word function for the emulator program
void storeWord(unsigned int instruction)
{
    unsigned int shiftingsss = ((instruction >> 11) & 7);

    unsigned int shiftingttt = ((instruction >> 8) & 7);
    
    //printf("storeword add: %d, data: %d", registers[shiftingttt], registers[shiftingsss]);
    cacheRequestSW(registers[shiftingttt], registers[shiftingsss]);

    programCounter++;
}


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
    TCreg = 0;
    haltCalled = false;

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
    printf("RH: 0x%02X\n", registers[7]);
    printf("TC: %d\n\n", TCreg);
}


// Starts one tick for the CPU.
void cpuStartTick()
{
    if (programCounter == 0)
    {
        programCounter = emulatorReturn(); // sets program counter to the starting hexAddress
    }
}

// Does the cycle work for the CPU.
void cpuDoCycleWork1()
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



