#include "Board_GLCD.h"
#include "Board_LED.h"
#include "stm32f2xx_hal.h"
#include "GLCD_Config.h"
#include "JOY.h"
#include "Serial.h"

void setup(void);
void SysTick_Handler(void);
void draw(void);
void highlightText(void);
void toPosition(int * p);
void getPos(uint32_t ch,int *p);
void LED (uint32_t c);
void sampleJoystick(void);
void ClearHighlight(uint32_t c);
void wait(void);

extern GLCD_FONT GLCD_Font_16x24;
uint32_t fw,fh,dx,dy,hex, xc, yc, xmin, xmax, ymin, ymax;
bool ready;

int main(void){
	SystemCoreClockUpdate();
	HAL_Init();
	SysTick_Config(SystemCoreClock/1000);
	setup ();
	GLCD_ClearScreen();

// Add Additional lines of code if required //
	hex = 0x20;
	xc = dx;
	yc = dy;
	xmin = dx;
	ymin = dy;
	xmax = GLCD_WIDTH - dx;
	ymax = GLCD_HEIGHT - dy;
	LED(hex);
	draw();
	highlightText();
	while(1){}
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
	int32_t character = hex; // Starting from space ascii value
	GLCD_SetBackgroundColor(GLCD_COLOR_PURPLE); // Set the background as purple
	GLCD_SetForegroundColor(GLCD_COLOR_WHITE); // Set the text color to white
	// Starting from the top of the screen offset by one space to the second to last row of the screen
	for(int y = ymin; y < ymax; y = y+fh) {
		// Starting from the left of the screen offset by one space to the second to last column
		for(int x = xmin; x < xmax; x = x+fw) {
			GLCD_DrawChar(x, y, character); // Draw the char in the current position
			character++; // Increase the char value
			//x = x+fw; // Move right by one char width
		}
		//y = y+fh; // Move down by one char height
	}
}


/**Highlight the character c in the 16x6 grid **/


void highlightText(void){
	GLCD_SetForegroundColor(GLCD_COLOR_BLACK); // Set the text color to black
	GLCD_DrawChar(xc, yc, hex);
	GLCD_SetForegroundColor(GLCD_COLOR_GREEN);
	GLCD_DrawRectangle(xc, yc, fw, fh);
}



/**Convert row and column to actual x y position: p[0] = column p[1] = row **/



void toPosition(int * p){

//*** PUT YOUR CODE HERE**

}



/**Fill the array p with the row and column number of the character ch: p[0] column p[1] = row **/



void getPos(uint32_t ch,int *p){
	
//***PUT YOUR CODE HERE***

}


/**Toggle the LED based on the bits of the character c.
1 LED will be turned on
0 LED will be turned off **/


void LED (uint32_t c){
	LED_SetOut(c);		
}


/**Checks if the direction of the joy stick and move the cursor in the joy stick's direction. If the cursor is at the bounds, cursor will not be moved**/


void sampleJoystick(void){
	if(!ready){
		return;
	}//initialization has not completed, abort
	uint32_t key = JOY_GetKeys();
	if (key == JOY_RIGHT) {

	}
}


/** Clear any previous highlight and highlight c **/



void ClearHighlight(uint32_t c){

//***PUT YOUR CODE HERE***
}


void wait(void) {
	for (int i = 0; i < 500000; i++);
}
