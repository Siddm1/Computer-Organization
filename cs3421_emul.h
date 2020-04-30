#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


/* username: sdmahade
   Name: Siddhesh Mahadeshwar
   Program Description: (Program 2: Computer Organization): This file is the header file for the emulator.
   It is responsible for defining all the prototypes for any functions that the main .c
   emulator may need.
 */

#ifndef EMUL_H
#define EMUL_H

typedef struct
{
    unsigned int address;
} Emulator;

int emulatorReturn();

#endif