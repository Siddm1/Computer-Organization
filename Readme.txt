


The following libraries have been used:
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
My program perfectly matches the second output required based on the second input. The first input also matches the output to 
a great extent but has some minor discrepancies where the cache writing functions are needed as after vigorous debugging and
many number of hours spent trying to debug just the cache program and the cache + IO device, these minor bugs could not be 
identified and fixed. However, the IO device by itself functions as required as all of output 2 functions as required and 
that second output depends more on the IO device functionality than output 1 which depends more on the cache as well. 

Other than this, all other #include files are the 7 header files, one for each of the .c files. 

The following are all the necessary files for this program:

cs3421_emul.h
cs3421_cpu.h
cs3421_memory.h
cs3421_clock.h
cs3421_imemory.h
cs3421_cache.h
cs3421_iodev.h
cs3421_emul.c
cs3421_cpu.c
cs3421_memory.c
cs3421_clock.c
cs3421_imemory.c
cs3421_cache.c
cs3421_iodev.c

A makefile has been included with the submission.


