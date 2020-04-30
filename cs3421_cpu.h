#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/* username: sdmahade
   Name: Siddhesh Mahadeshwar
   Program Description: (Program 2: Computer Organization): This file is the header file for the CPU device
   for the emulator. It is responsible for defining all the prototypes for any functions that the main .c
   CPU device may need.
 */

#ifndef CPU_H
#define CPU_H

//increments the TC register
void TCdoCycleWork();

// The “set reg” command sets the value of the specified CPU register. The “reg” parameter can be the value
// RA-RH, or PC for the program counter.
void setReg(char* reg, int hexByte);

// finds out the instruction command to be run;
void cpuDoCycleWork2();

// The “reset” command causes all CPU registers (including PC) to be zero.
void cpuReset();

// The “dump” command shows the value of all of the CPU registers.
void cpuDump();

// Starts one tick for the CPU.
void cpuStartTick();

// Does the cycle work for the CPU.
void cpuDoCycleWork1();

// The load word function for this emulator program which will load a word into a register from data memory.
void loadWord(unsigned int instruction);

// The store word function which will store a word into data memory from a target CPU register.
void storeWord(unsigned int instruction);

// The add function adds the source and target register words, storing the result in the destination register. All
// values should be treated as 8 bit 2's complement numbers.
void add(unsigned int instruction);

// The addi function adds the source register and immediate value words, storing the result in the destination register. All
// values should be treated as 8 bit 2's complement numbers.
void addi(unsigned int instruction);

// Takes the upper 4 bits and lower bits of the source register, multiplies those values together, and stores the result in
// the destination register
void mul(unsigned int instruction);

// Inverts all the bits in the source register word, storing the result in the destination register.
void inv(unsigned int instruction);

// The branch if equal function: if the words in the source and target registers are equal, assign the PC to the immediate
// specified imemory address, otherwise, increment the PC. 
void beq(unsigned int instruction);

// The brance if not equal function: If the words in the source and target register are not equal, assign the PC to the
// immediate-specified imemory address, otherwise increment the PC. 
void bneq(unsigned int instruction);

// The branch if less than function: if the word in the source register is less than the word in the target registers, assign
// the PC to the immeidate-specified imemory address, otherwise increment the PC.
void blt(unsigned int instruction);

// Halt execution of the processor after incrementing PC. After halting, the CPU will ignore all future clock ticks, but will
// cooperate in supporting all parser commands such as "cpu dump";
void halt();

#endif