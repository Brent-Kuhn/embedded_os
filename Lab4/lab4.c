#include <stdint.h>
#include <stdio.h>
#include "stm32f2xx.h"                  // Device header
#include "Board_LED.h"                  // ::Board Support:LED

// Crate a variable to hold the bits for counting people
uint8_t count = 0b00000000;

void wait() {
	for (int i = 0; i < 500000; i++);
}

void button_init() {
	// To initialize WAKEUP (PA0)
	// Enable clock for the gpio using RCC (bit 1)
	RCC->AHB1ENR |= 0x01;
	
	// Configure  the  System  (SYSCFG)  Register  EXTICR  Register  to  configure  the  Line  of  Interrupt. (SYSCFG-> EXTI[0] Register)
	RCC->APB2ENR = (1<<14);
	SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PA;
	
	//Set   the   mode   of   GPIOx   pin(i)   to   "INPUT".   (using   GPIO   port   mode   register   (GPIOx_MODER) (x = A..I) 
	GPIOA->MODER &= ~03;
	
	// Set  the  interrupt  Triggering  level:  Falling  edge  (using  Falling  trigger  selection  register  (EXTI_FTSR)) or Rising edge (using Rising trigger selection register (EXTI_RTSR))
	EXTI->FTSR |= 0x01;
	
	// Unmask the Interrupt over EXTI Mask Register (Interrupt mask register (EXTI_IMR) 
	EXTI->IMR |= 0x01;
	
	// Enable the interrupt using NVIC for IRQ6
	NVIC_EnableIRQ(EXTI0_IRQn);
	
	// To initialize USER (PG15)
	// Enable clock for gpio using RCC (bit 6)
	RCC->AHB1ENR |= (1<<6);
	
	// Enable the select line for the 15 multiplexer
	SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI15_PG;
	
	// Enable PG15 as in input
	GPIOG->MODER &= ~0xC0000000;
	
	//Enable 15th? bit of the Falling Trigger Selection Register as 1
	EXTI->FTSR |= (1<<15);
	
	//Enable 15th? bit of the Interrupt Mask Register as 1
	EXTI->IMR |= (1<<15);
	
	NVIC_EnableIRQ(EXTI15_10_IRQn);
}



int main() {
	// Initialize the buttons for interrupts
	button_init();
	// Initialize LEDs
	LED_Initialize();
	
	// Infinite loop
	while(1) {
	}
	
	return 0;
}

void EXTI0_IRQHandler(void) {
	// clear the pending bit for exti0
	if( (EXTI->PR & 0x01) ) {
		EXTI->PR = 0x01;//Writing 1 , clears the pending bit for exti0
	}
	uint32_t LED_Num = LED_GetCount();
	LED_SetOut(0);
	// Blink LEDS from 0 to 7 to show a new person has entered
	for(int i = 0; i<LED_Num; i++) {
		LED_On(i);
		wait();
		LED_Off(i);
	}
	count = count + 1;
	LED_SetOut(count);
}

void EXTI15_10_IRQHandler(void) {
	// clear the pending bit for exti15
	if( (EXTI->PR & 0x8000) ) {
		EXTI->PR = 0x8000;//Writing 1 , clears the pending bit for exti15
	}
	LED_SetOut(0);
	uint32_t LED_Num = LED_GetCount();
	// Blink LEDS from 7 to 0 to show a new person has left
	for(int i = LED_Num - 1; i > 0; i--) {
		LED_On(i);
		wait();
		LED_Off(i);
	}
	count = count - 1;
	LED_SetOut(count);
}
