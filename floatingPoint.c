#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <inttypes.h>
#include <float.h>

/*
Name: Siddhesh Mahadeshwar
Class: CS 3421 - Computer Organization
Program Title: Floating point extra credit assignment

	1. 0x447A0000 in binary is equivalent to the following: 0 10001000 11110100000000000000000
	-  The leading "0" represents a positive number.
	-  The second set of 8 bits represent the exponent which is 136.
	-  136(exponent) - 127(the bias) will yield 9
	-  Adding an implicit 1 and moving over 9 decimal places, the following would be the number we will
	   deal with 1111101000.00000000000000 which equals 1,000.00 which is the same as 1.0e3

	2. The outputs for the internal representation of 1.0e3 and the sum of 1.0e3 and 1.0e-5 were
	   exactly the same on my machine. The sum of those 2 values results in 1000.00001.
	   The reason these values are the same is because single-precision cannot represent a value
	   as such as this one with these many decimal values and a total of 9 significant figures as it
	   can display 8 significant digits successfully such as this: "0000.0000". 

	3. For Sum 1, the following internal operations occur:
	   As seen in the explanation for problem 2, single precision cannot accurately display
	   1.0e3 and 1.0e-5 so it does not matter is there are 10,000 elements of 1.0e-5 added as this
	   is simply beyond the level of precicion which can be represented by this precision of floats. 
	   Thus, once 1000 is added first, no effect appears on the sum until a significant enough number
	   such as 1000 is added at the end. Therefore, the final answer then becomes 
	   1000 + (insignificant decimal numbers) + 1000 = 2000.00

	   For Sum 2, the following internal operations occur:
	   As 1000 has not been added to the sum yet, 0.00001 can succesfully be displayed with the 
	   available significant numbers. This continues for 10,000 elements which results in 0.1.
	   At the end, when 1000 + 1000 is added to the sum, these values take place in the sum 
	   figures available. In theory, 2000.1 should be the absolute and correct answer however the
	   displayed value is 2000.09998. As floats are not always 100% accurate, the output of 
	   2000.09998, which is extrememly close to 2000.1, is appropriate because floats also cannot
	   display an infinite number of decimal points. As a result, a very miniscule margin of error
	   can be expected and is understandable too. 
*/

int main()
{
	// -----------------------------------all declarations------------------------------------- //

	// array size declaration
	int arraySize = 10002;
	// create a floating point array of size 10,002
	float* floatArray;
	// floats array memory allocation
	floatArray = malloc(arraySize * sizeof(float));
	// float array lower value --> 0.00001
	float lower = 1.0e-5f;
	// float array higher value --> 1,000 in decimal 
	float higher = 1.0e3f;
	// set 0th index to higher value
	floatArray[0] = higher;
	// set last index to higher value at index 10,001
	floatArray[arraySize - 1] = higher;
	// initialization of Sum1 and Sum2
	float Sum1 = 0;
	float Sum2 = 0;

	// ----------------------------assigning values in array + Sum1---------------------------- //

	// declaration of all indices 1-10,000 to lower value (1.0e-5);
	for (int i = 1; i < arraySize - 1; i++)
	{
		floatArray[i] = lower;
	}

	// Sum 1 calculation of all elements from 0 to 10,001
	for (int i = 0; i < arraySize; i++)
	{
		Sum1 += floatArray[i];
	}

	// ------------------------------------swapping values------------------------------------- //

	// swapping of 0 and 10,000 indices
	float temp;
	// 1.0e3 saved in temp
	temp = floatArray[0]; 
	// 0th index saved as 1.0e-5
	floatArray[0] = floatArray[arraySize - 2]; 
	// 10,000th index saved as 1.0e3
	floatArray[arraySize - 2] = temp;

	// ------------------------------------------Sum2------------------------------------------ //

	// Sum 2 calculation of all elements from 0 to 10,001
	for (int i = 0; i < arraySize; i++)
	{
		Sum2 += floatArray[i];
	}

	// ---------------------------------printing values and sums------------------------------- //

	// Hex representation of a 32 bit floating number
	int low = *(int*)&lower;
	int high = *(int*)&higher;

	// calculation and hex representation of high + low value
	float total = 1.0e3f + 1.0e-5f;
	int tot = *(int*)&total;

	// print statements for the output
	printf("Internal representation of 1.0e-5 is: 0x%08X\n", low);
	printf("Internal representation of 1.0e3 is: 0x%08X\n", high);
	printf("Internal representation of 1.0e3 + 1.0e-5 is: 0x%08X\n", tot);
	printf("Sum 1 is: %.5f\n", Sum1);
	printf("Sum 2 is: %.5f\n", Sum2);

	// ---------------------------------------free array--------------------------------------- //

	// free all allocated space in the float point array
	free(floatArray);

	return 0;
}