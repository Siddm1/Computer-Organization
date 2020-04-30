#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>                                                                          
#include <math.h>

/* username: sdmahade
   Name: Siddhesh Mahadeshwar
   Program Description: (Program 2: Computer Organization): This file is the header file for the clock device
   for the emulator. It is responsible for defining all the prototypes for any functions that the main .c
   clock device may need.
 */

#ifndef CACHE_H
#define CACHE_H

// fills the cache with data based on the CLO
void cacheFill();

// sets all the cache flags to valid
void cacheSetFlagsInvalid();

// sets all the cache flags to valid
void cacheSetFlagsValid();

 // handles the load word request in the cache
int cacheRequestLW(int address);

// handles the Store word request in the cache
void cacheRequestSW(int address, int shiftingsss);

 // checks if any of the cache data has been written
bool cacheWritten();

// return true of cache is on, false if off
bool isCacheEnabled();

 // determines if the cache is valid
int isCacheValid();

// flushes data from the cache to the data memory
void cacheFlush();

// turns on the cache for the cache device
void cacheOn();

// turns off the cache for the cache device
void cacheOff();

// resets the cache for the cache device
void cacheReset();

// dumps the values stored in the cache device
void cacheDump();

// returns the current CLO from cache device
int getCLO();

#endif
