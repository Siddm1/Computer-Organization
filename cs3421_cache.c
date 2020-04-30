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
   Program Description: (Program 2: Computer Organization): This file is the C file for the clock device
   for the emulator. It is responsible for the implementation of all the prototype functions defined 
   initially in the header file.
 */

uint8_t cacheArray[8];
int flagsArray[8]; // 0 = invalid, 1 = valid, 2 = written
int CLO = 0;
bool cacheEnabled = false;


// fills the cache with data based on the CLO
void cacheFill()
{
    int cIndex = 0;
    for (uint8_t i = CLO * 8; i < (CLO * 8) + 8; i++) // brings in the 8 corresponding values into cache based on the CLO at the point
    {
        cacheArray[cIndex] = getMemoryValue(i);
        cIndex++;
    }
}

// sets all the cache flags to valid
void cacheSetFlagsValid()
{
    for (int i = 0; i < 8; i++)
    {
        flagsArray[i] = 1;
    }
}

// sets all the cache flags to valid
void cacheSetFlagsInvalid()
{
    for (int i = 0; i < 8; i++)
    {
        flagsArray[i] = 1;
    }
}

// handles the load word request in the cache
int cacheRequestLW(int address)
{
    int computedCLO = address / 8;

    //cacheEnabled = true;
    if (cacheEnabled == true)
    {
        if (address == 255) //  edge case when address is 255
        {
            cacheSetFlagsInvalid(); // set flags to be invalid
            
        }
        else if (CLO == computedCLO && isCacheValid() == 1) // cache hit situation
        {
            return getMemoryValue(address);
        }
        else if (CLO != computedCLO || isCacheValid() == 0) // cache miss situation
        {
            CLO = computedCLO;

            cacheFill(); // fills the cache with the respective CLO

            cacheSetFlagsValid(); // sets all flags to valid

            return getMemoryValue(address);
        }
    }
    return getMemoryValue(address);
}


// handles the Store word request in the cache
void cacheRequestSW(int address, int shiftingsss)
{
    int computedCLO = address / 8;
    int index = address % 8;

    if (cacheEnabled == true)
    {
        //printf("sw");
        if (address == 255 && cacheWritten())
        {
            cacheFlush(); // flushes the cache data back to memory
            for (int i = 0; i < 8; i++)
            {
                if (flagsArray[i] == 2)
                {
                    flagsArray[i] = 1;
                }
            }
            setMemoryValue(address, shiftingsss); // sets the data to the address in memory
            return;
        }
        else if (address == 255 && !cacheWritten())
        {
            //setMemoryValue(address, shiftingsss); // sets the data to the address in memory
            return;
        }

        if (CLO == computedCLO || isCacheValid() == 0) // cache hit situation
        {
            cacheArray[index] = shiftingsss;

            flagsArray[index] = 2;
            //cacheFlush();
        }
        else if (CLO != computedCLO && cacheWritten()) // cache miss situation
        {
            cacheFlush();

            cacheSetFlagsValid();

            CLO = computedCLO;

            cacheFill(); // fill cache with appropriate data based on CLO

            cacheArray[index] = shiftingsss; //  calculates the offset to store values in for the cacheArray

            flagsArray[index] = 2; //  sets the flag at the index to be true for the cache
        }
        else if (CLO != computedCLO && !cacheWritten())
        {
            cacheFlush();

            CLO = computedCLO;

            cacheFill();

            cacheArray[index] = shiftingsss;

            flagsArray[index] = 2; // setting flag to be written
        }

    }
    else // if cache not enabled situation
    {
        setMemoryValue(address, shiftingsss);
    }
}

// checks if any of the cache data has been written
bool cacheWritten()
{
    bool written = false;
    for (int i = 0; i < 8; i++)
    {
        if (flagsArray[i] == 2)
        {
            written = true;
        }
    }
    return written;
}

// return true of cache is on, false if off
bool isCacheEnabled()
{
    return cacheEnabled;
}

// determines if the cache is valid
int isCacheValid()
{
    int invalid = 0;
    int valid = 1;
    int count = 0;
    for (int i = 0; i < 8; i++)
    {
        if (flagsArray[i] == 0)
        {
            count++;
        }
    }

    if (count == 8)
    {
        return invalid;
    }
    else {
        return valid;
    }
}

// returns the current CLO from cache device
int getCLO()
{
    return CLO;
}

// flushes data from the cache to the data memory
void cacheFlush()
{
    int cIndex = 0;
    for (int i = CLO * 8; i < (CLO * 8) + 8; i++)
    {
        setMemoryValue(i, cacheArray[cIndex]);
        cIndex++;
    }
}

// turns on the cache for the cache device
void cacheOn() 
{
    cacheEnabled = true;
}

// turns off the cache for the cache device
void cacheOff()
{
    cacheEnabled = false;
    cacheFlush();
}

// resets the cache for the cache device
void cacheReset()
{
    cacheEnabled = false;
    CLO = 0;

    for (int i = 0; i < 8; i++)
    {
        flagsArray[i] = 0;
    }
}

// dumps the values stored in the cache device
void cacheDump()
{
    printf("CLO        : 0x%02X\n", CLO);
    printf("cache data : ");
    for (int i = 0; i < 8; i++)
    {
        printf("0x%02X ", cacheArray[i]);
    }
    printf("\n");
    printf("Flags      :   ");


    for (int i = 0; i < 8; i++)
    {
        if (flagsArray[i] == 0)
        {
            printf("I    ");
        }
        else if (flagsArray[i] == 1)
        {
            printf("V    ");
        }
        else if (flagsArray[i] == 2)
        {
            printf("W    ");
        }
    }

    printf("\n\n");
}

