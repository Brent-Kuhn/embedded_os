#include<stdint.h>
#include "Board_LED.h"
#include "Board_Buttons.h"

void delay(void){
	uint32_t i;
	// Create a loop counter to create delay
	for(i=0; i<1000000; i++);
}

int main(void) {
	// Initialize LEDs
	LED_Initialize();
	Buttons_Initialize();
	
	uint32_t button;
	uint32_t LED_Num = LED_GetCount();
	
	while(1){
		button = Buttons_GetState();
		if(button == 0) {
			
		}
		else if(button == 1){
			// If user button is pressed
			// Blink LEDs from left to right
			for(int j = 0; j < LED_Num; j++) {
				LED_On(j);
				
				delay();
				
				LED_Off(j);
			}
		}
		else if(button == 2){
			// If Tamper button is pressed
			// Blink even number LEDs from left to right
			for(int j = 0; j < LED_Num; j++) {
				LED_On(j);
				
				delay();
				
				LED_Off(j);
				j++;
			}
		}
		else if(button == 4){
			// If Wakeup button is pressed
			// Blink LEDs in pairs
			for(int j = 0; j < LED_Num; j++) {
				if(j < 7) {
					LED_On(j);
					LED_On(j+1);
				
					delay();
					
					LED_Off(j);
					LED_Off(j+1);
				}
			}
		}
	}
	
	return(0);
}