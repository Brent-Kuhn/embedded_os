#include "cmsis_os2.h"                          // CMSIS RTOS header file
#include "rtosClockObjects.h"
#include <stdint.h>
/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 
osThreadId_t hour_Thread;                        // thread id
 
void hourThread (void *argument);                   // thread function
 
int Init_hourThread (void) {
 
  hour_Thread = osThreadNew(hourThread, NULL, NULL);
  if (hour_Thread == NULL) {
    return(-1);
  }
 
  return(0);
}
 
void hourThread (void *argument) {
 
  while (1) {
		osSemaphoreAcquire(semHour, osWaitForever);	// Lock the Hour semaphore for waiting until the next hour

		osMutexAcquire(mutHour, osWaitForever);	// Acquire the hour mutex key
		hour = (hour + 1) % 24;
		osMutexRelease(mutHour);
		
    osThreadYield();                            // suspend thread
  }
}
