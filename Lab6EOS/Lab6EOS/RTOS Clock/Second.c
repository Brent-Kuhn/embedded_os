#include "cmsis_os2.h"                          // CMSIS RTOS header file
#include "rtosClockObjects.h"
#include <stdint.h>
/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 
osThreadId_t second_Thread;                        // thread id
 
void secondThread (void *argument);                   // thread function
 
int Init_secondThread (void) {
 
  second_Thread = osThreadNew(secondThread, NULL, NULL);
  if (second_Thread == NULL) {
    return(-1);
  }
 
  return(0);
}
 
void secondThread (void *argument) {
 
  while (1) {
    osDelay(osKernelGetTickFreq()); // Wait one second
		osMutexAcquire(mutSecond, osWaitForever);	// Acquire the second mutex key
		second = (second + 1) % 60; // calculate seconds
		osMutexRelease(mutSecond); // release the mutex so other portions of the code have access
		
		if(second == 0) {
			// relase the key and inc min
			osSemaphoreRelease(semMinute);
		}
		// refresh the screen
		osStatus_t screenStatus = osSemaphoreAcquire(semDisplayTime, osWaitForever); // returns status = osOK
		if(screenStatus == osOK) {
			//thdDisplayTime(hour, minute, second)
		}
		
    osThreadYield();                            // suspend thread
  }
}
