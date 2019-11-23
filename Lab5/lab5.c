#include "Board_GLCD.h"
#include "Board_LED.h"
#include "stm32f2xx_hal.h"
#include "GLCD_Config.h"
#include "JOY.h"
#include "Serial.h"

extern GLCD_FONT GLCD_Font_16x24;
uint32_t fw,fh,dx,dy, hex, xc, yc, xmin, xmax, ymin, ymax;
bool ready;

void setup(void);
void SysTick_Handler(void);
void draw(void);
void highlightText(uint32_t x,uint32_t y, uint32_t c);
void toPosition(int * p);
void getPos(uint32_t ch,int *p);
void LED (uint32_t c);
void sampleJoystick(void);
void clearHighlight(uint32_t x,uint32_t y, uint32_t c);
void wait(void);


int main(void){
	SystemCoreClockUpdate();
	HAL_Init();
	SysTick_Config(SystemCoreClock/1000);
	setup();
	GLCD_ClearScreen();
	
	draw(); // Draw the ascii char on the screen
	
	// Use xc and yc as current x and y position
	// Use hex as the current hex value +/-x = +/-0x01 hex +/-y = +/-0x10 hex
	hex = 0x20;
	xc = dx;
	yc = dy;
	xmin = dx;
	xmax = GLCD_WIDTH - dx;
	ymin = dy;
	ymax = GLCD_HEIGHT - dy;
	
	// Add Additional lines of code if required //
	highlightText(xc,yc, hex);
	LED(hex);

	while(1);
	
	return 0;
}

/**Initialize the peripherals: Already Done**/

void setup(void){
	GLCD_Initialize();
	LED_Initialize();
	JOY_Init();
	SER_Init(115200);
	GLCD_SetFont(&GLCD_Font_16x24);
	GLCD_SetBackgroundColor(GLCD_COLOR_PURPLE);
	fw = GLCD_Font_16x24.width;// font width
	fh = GLCD_Font_16x24.height; //font height
	//minimum x position on the screen. Corresponds to column 0
	dx = (GLCD_WIDTH - 16*fw)>>1;
	//minimum y position on the screen. Corresponds to row 0
	dy = (GLCD_HEIGHT - 6 * fh) >> 1;
	//use to prevent Joy stick sampling when the joy stick has not be initialized
	ready = true;
}

/*SysTick ISR*/

void SysTick_Handler(void){
	//increment HAL tick variable; this is required for LCD Display Config.
	HAL_IncTick();
	//check for joy stick movement to configure Joystick Sampling
	sampleJoystick();
}

/**Draw ascii characters on the screen**/

void draw(void){ 
	int32_t character = 0x20; // Starting from space ascii value
	GLCD_SetBackgroundColor(GLCD_COLOR_PURPLE); // Set the background as purple
	GLCD_SetForegroundColor(GLCD_COLOR_WHITE); // Set the text color to white
	// Starting from the top of the screen offset by one space to the second to last row of the screen
	for(int y = dy; y < (GLCD_HEIGHT - dy); y = y+fh) {
		// Starting from the left of the screen offset by one space to the second to last column
		for(int x = dx; x < (GLCD_WIDTH - dx); x = x+fw) {
			GLCD_DrawChar(x, y, character); // Draw the char in the current position
			character++; // Increase the char value
			//x = x+fw; // Move right by one char width
		}
		//y = y+fh; // Move down by one char height
	}
}


/**Highlight the character c in the 16x6 grid **/


void highlightText(uint32_t x,uint32_t y, uint32_t c){

	GLCD_SetForegroundColor(GLCD_COLOR_BLACK); // Set the text color to white
	GLCD_DrawChar(x, y, c);
	GLCD_SetForegroundColor(GLCD_COLOR_GREEN);
	GLCD_DrawRectangle(x, y, fw, fh);
	wait();
}



/**Convert row and column to actual x y position: p[0] = column p[1] = row **/



void toPosition(int * p){

/*** PUT YOUR CODE HERE**/

}



/**Fill the array p with the row and column number of the character ch: p[0] column p[1] = row **/



void getPos(uint32_t ch,int *p){
	
/***PUT YOUR CODE HERE***/

}


/**Toggle the LED based on the bits of the character c.
1 LED will be turned on
0 LED will be turned off **/


void LED (uint32_t c){
	LED_SetOut(c);		
}


/**Checks if the direction of the joy stick and move the cursor in the joy stick's direction. If the cursor is at the bounds, cursor will not be moved**/


void sampleJoystick(void){
	if(!ready)return;//initialization has not completed, abort
	uint32_t key = JOY_GetKeys();
	if (key == JOY_RIGHT) {
		// If the right button is pushed and we aren't at the edge of the screen
		// Move to the right
		if (xc < xmax - fw) {
			clearHighlight(xc, yc, hex);
			// Increase xc to move right
			xc += fw;
			// Increase the hex value
			hex += 1;
			// Send the hex value out to the leds
			LED(hex);
			// Highlight the new text
			highlightText(xc, yc, hex);
		}
	}
	else if (key == JOY_LEFT) {
		// If the left button is pushed and we aren't at the edge of the screen
		// Move to the left
		if (xc > xmin) {
			// Clear the current highlight
			clearHighlight(xc, yc, hex);
			// Decrease xc to move left
			xc -= fw;
			// Decrease the hex value
			hex -= 1;
			// Send the he value out to the leds
			LED(hex);
			// Highlight the new text
			highlightText(xc, yc, hex);
		}
	}
	else if (key == JOY_DOWN) {
		if(yc < ymax - fh) {
			// Clear the current highlight
			clearHighlight(xc, yc, hex);
			// Increase yc to move down
			yc += fh;
			// Decrease the hex value by 0x10
			hex += 0x10;
			// Send the he value out to the leds
			LED(hex);
			// Highlight the new text
			highlightText(xc, yc, hex);
		}
	}
	else if (key == JOY_UP) {
		if(yc > ymin) {
			// Clear the current highlight
			clearHighlight(xc, yc, hex);
			// Decrease yc to move down
			yc -= fh;
			// Decrease the hex value by 0x10
			hex -= 0x10;
			// Send the he value out to the leds
			LED(hex);
			// Highlight the new text
			highlightText(xc, yc, hex);
		}
	}
	return;
}


void clearHighlight(uint32_t x,uint32_t y, uint32_t c){
	GLCD_SetForegroundColor(GLCD_COLOR_PURPLE);
	GLCD_DrawRectangle(x, y, fw, fh);
	GLCD_SetForegroundColor(GLCD_COLOR_WHITE); // Set the text color to white
	GLCD_DrawChar(x, y, c);
}


void wait(void) {
	for (int i = 0; i < 500000; i++);
}
