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
	uint32_t LED_Num = LED_GetCount();
	while(1){
		for(int j = 0; j < LED_Num; j++) {
			LED_On(j);
			
			delay();
			
			LED_Off(j);
		}
	}
	
	return(0);
}