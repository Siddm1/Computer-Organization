#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>                                                                          
#include <math.h>
#include <inttypes.h>

/* username: sdmahade
   Name: Siddhesh Mahadeshwar
   Program Description: (Program 2: Computer Organization): This file is the header file for the clock device
   for the emulator. It is responsible for defining all the prototypes for any functions that the main .c
   clock device may need.
 */

#ifndef IODEV_H
#define IODEV_H

// resets the I/O device
void ioReset();

// the load method for this device which will directly load data straight to d-memory
bool ioLoad(char* filename);

// deals with the I/O reading
void ioRead();

// deals with the I/O writing
void ioWrite();

// dumps the I/O device
void ioDump();

// free variables
void ioFree();

#endif
