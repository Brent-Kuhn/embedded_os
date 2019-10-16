//  Author: David Foster
//  Modified by: Brent Kuhn

#include <stm32f2xx.h> 
// Notice answers are in base 10!
// Assuming that the system is little-endianu

int32_t array0[] = {0x00000001,0x00000020,0x00000400,0x00008000,0x00440000,0x02200000,0x12000000,0x80000000}; // answer = 0d0/ 0x0  

uint32_t array1[] = {0x00000000,0x00000020,0x00000400,0x00008000,0x00440000,0x02200000,0x12000000,0x80000000}; // answer = 37/ 0x25 (in hex 0x25 =0d37)

uint32_t array2[] = {0x00000000,0x00000000,0x00000400,0x00008000,0x00440000,0x02200000,0x12000000,0x80000000}; // answer = 74 / 0x4A

uint32_t array3[] = {0x00000000,0x00000000,0x00000000,0x00008000,0x00440000,0x02200000,0x12000000,0x80000000}; // answer = 111 / 0x6F

uint32_t array4[] = {0x00000000,0x00000000,0x00000000,0x00000000,0x00440000,0x02200000,0x12000000,0x80000000}; // answer = 146 / 0x92

uint32_t array5[] = {0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x02200000,0x12000000,0x80000000}; // answer = 181 / 0xB5

uint32_t array6[] = {0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x12000000,0x80000000}; // answer = 217 / 0xD9

uint32_t array7[] = {0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x80000000}; // answer = 255 / 0xFF

uint32_t* arrays[] = {array0, array1, array2, array3, array4, array5, array6, array7}; 

uint32_t narrays = sizeof(arrays)/sizeof(uint32_t*);

uint32_t findLowBitASM(uint32_t*);

uint32_t findLowBitC(uint32_t*);

int main(void){
	int i;
	volatile int position;
	for (i = 0; i<narrays; i++){
		//position = findLowBitASM(arrays[i]);
		position = findLowBitC(arrays[i]);
	}
	while(1){
		position++;
	} 
	// endless loop to keep micro from crashing 
	// position++ keeps position in scope for easier debugging
}

// stub for your implementation of the function
uint32_t findLowBitC(uint32_t* array){
	// and with 0001 and when 1, return, else right shift once, increase counter and repeat
	int8_t check = 0x00000001; // Mask of 1 for checking the last value in the word
	// Create a place to save the lowBit location when we find it
	uint32_t lowBit;
	// Run through each item in the array
	for (int32_t count = 0; count <= 7; count++) {
		int32_t word = array[count]; // Each value in the array is now called word
		// For each bit in the word check
		for (int32_t pos = 0; pos <= 31; pos++) {
			// A bitwise and with 0x00000001 will return 1 if the word ends in 1
			if (check & word) {
				// Calculate the position of the current bit
				lowBit = pos + count * 32;
				return lowBit;
			} 
			else {
				// Shift word by 1 to the right if a 1 was not found
				word = word >> 1;
			}
		}
	}
}
