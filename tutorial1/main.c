#include<stdint.h>
#include "Board_LED.h"                  // ::Board Support:LED

void delay(void){
	uint32_t i;
	// Create a loop counter to create delay
	for(i=0; i<1000000; i++);
}

int main(void) {
	// Initialize LEDs
	LED_Initialize();
	
	while(1){
		// Turn on LED 0 and 5
		LED_On(0);
		LED_On(5);
		
		// Wait a period of time
		delay();
		
		// Turn LEDs off
		LED_Off(0);
		LED_Off(5);
		
		// Wait a period of time
		delay();
	}
	
	return(0);
}