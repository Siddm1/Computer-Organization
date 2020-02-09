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
   Program Description: (Program 1: Computer Organization): This is the emulator device for this program which
                        contains the main method with executing all the required parsing.
 */

Emulator emulator;

int emulatorReturn()
{
    return emulator.address;
}


int main(int argc, char** argv)
{
    if (argc < 2 || argc > 2)
    {
        printf("You are missing a file to input\n");
        printf("Format: cs3421_emul <.txt file> \n");
        return 0;
    }
    
    // creating a file pointer to access a file entered as the 2 argument
    FILE* fp = fopen(argv[1], "r");

    // temporary variables for parsing
    char* input = "";
    input = malloc(sizeof(char*));
    char* input2 = "";
    input2 = malloc(sizeof(char*));
    char* ignore = "";
    ignore = malloc(sizeof(char*));
    char* reg = "";
    reg = malloc(sizeof(char*));
    char* filename = "";
    filename = malloc(sizeof(char*));
    unsigned int input3;
    unsigned int memD1;
    unsigned int memD2;
    unsigned int memD3;
    unsigned int temp = 0;

    // checks if the file pointer is possible, if not, returns false
    if (fp == NULL)
    {
        return false;
    }

    // continues to scan until scanner reaches the End of File
    while (fscanf(fp, "%s", input) != EOF)
    {
        if (strcmp(input, "clock") == 0) // scans the first word in and check if it a clock device
        {
            if (fscanf(fp, "%s", input2) == 0)
            {
                return 1;
            }
            if (strcmp(input2, "reset") == 0) // checks if the clock command is reset
            {
                clockReset(); // resets the clock
            }
            else if (strcmp(input2, "tick") == 0) // checks if the clock command is tick
            {
                if (fscanf(fp, "%u", &input3) == 0)
                {
                    return 1;
                }
                tick(input3); // calls the tick method and adds ticks
            }else if (strcmp(input2, "dump") == 0) // checks if the clock command is dump
            {
                clockDump(); // calls the clock dump method
            }
            
        }
        else if (strcmp(input, "cpu") == 0) // compares the first word to check if the device is CPU
        {
            if (fscanf(fp, "%s", input2) == 0) // scans the second word
            {
                return 1;
            } 
            if (strcmp(input2, "reset") == 0) // checks if command is reset
            {
                cpuReset(); // calls the reset command on the CPU
            }
            else if (strcmp(input2, "set") == 0) // checks if the command is set
            {
                if (fscanf(fp, "%s", ignore) == 0) // scans and ignores the 3rd read as it is "reg" when set is read in
                {
                    return 1;
                }
                
                if (fscanf(fp, "%s", reg) == 0) // scans the register where value must be set
                {
                    return 1;
                }
                
                if (fscanf(fp, "%X", &input3) == 0) // scans the hex number
                {
                    return 1;
                }
                

                setReg(reg, input3); // set the value at the given register
            }
            else if (strcmp(input2, "dump") == 0) // checks if command is dump
            {
                cpuDump(); // calls the cpuDump() method
            }
        }

        // --------------------------------------------------------------------------------------------------------------
        else if (strcmp(input, "imemory") == 0) // compares if device is memory
        {
            if (fscanf(fp, "%s", input2) == 0)
            {
                return 1;
            }

            if (strcmp(input2, "reset") == 0) // checks if second scan is reset
            {
                imemoryReset();
            }
            else if (strcmp(input2, "create") == 0) // checks if second scan is create
            {
                if (fscanf(fp, "%X", &memD1) == 0)
                {
                    return 1;
                }
                icreate(memD1);
            }
            else if (strcmp(input2, "set") == 0) // checks if second scan is set
            {
                if (fscanf(fp, "%X", &memD1) == 0)
                {
                    return 1;
                }

                if (fscanf(fp, "%s", ignore) == 0)
                {
                    return 1;
                }

                if (fscanf(fp, "%s", filename) == 0)
                {
                    return 1;
                }

                iset(memD1, filename);

            }
            else if (strcmp(input2, "dump") == 0)
            {
                emulator.address = temp; // sets the hexAddress to be whatever it is that is scanned in

                if (fscanf(fp, "%X", &memD1) == 0)
                {
                    return 1;
                }

                if (fscanf(fp, "%X", &memD2) == 0)
                {
                    return 1;
                }
                imemoryDump(memD1, memD2);
            }
        }

        // -----------------------------------------------------------------------------------------------------------

        else if (strcmp(input, "memory") == 0) // compares if device is memory
        {
            if (fscanf(fp, "%s", input2) == 0)
            {
                return 1;
            }
                
            if (strcmp(input2, "reset") == 0) // checks if second scan is reset
            {
                memoryReset();
            }
            else if (strcmp(input2, "create") == 0) // checks if second scan is create
            {
                if (fscanf(fp, "%X", &memD1) == 0)
                {
                    return 1;
                }
                create(memD1);
            }
            else if (strcmp(input2, "set") == 0) // checks if second scan is set
            {
                if (fscanf(fp, "%X", &memD1) == 0)// scans the starting hexAddress
                {
                    return 1;
                }

                if (fscanf(fp, "%X", &memD2) == 0)// scans the number of values to set
                {
                    return 1;
                }
                 
                emulator.address = memD1; // sends starting address to structure so it can be accessed globally
                temp = memD1; // saved the hexAddress in a temp variable to be access in another loop
                int memArray2[memD2]; // initializes array to have (hexaddress + count) number of variables
                for (unsigned int i = 0; i < memD2; i++)
                {
                    if (fscanf(fp, "%X", &memD3) == 0)
                    {
                        return 1;
                    }
                    memArray2[i] = memD3; // stores following scanned values into a temporary array which will be passed into send
                                          // values to the set function
                }
                set(memD1, memD2, memArray2); // calling the set command with given parameters
            }
            else if (strcmp(input2, "dump") == 0)
            {
                emulator.address = temp; // sets the hexAddress to be whatever it is that is scanned in
                
                if (fscanf(fp, "%X", &memD1) == 0)
                {
                    return 1;
                }

                if (fscanf(fp, "%X", &memD2) == 0)
                {
                    return 1;
                }
                memoryDump(memD1, memD2);
            }
        }
    }
    fclose(fp); // closes the file pointer

    // frees all variables
    freeVariables();
    free(input);
    free(input2);
    free(ignore);
    free(reg);

    return 0;
}
