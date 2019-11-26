#include "cmsis_os2.h"                          // CMSIS RTOS header file
#include "rtosClockObjects.h"
#include <stdint.h>

/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 
osThreadId_t minute_Thread;                        // thread id
 
void minuteThread (void *argument);                   // thread function
 
int Init_minuteThread (void) {
 
  minute_Thread = osThreadNew(minuteThread, NULL, NULL);
  if (minute_Thread == NULL) {
    return(-1);
  }
 
  return(0);
}
 
void minuteThread (void *argument) {
 
  while (1) {
//		osStatus_t status = osSemaphoreAcquire(semMinute, osWaitForever); // returns status = osOK
//		if(status == 'osOK') {
//			osMutexAcquire(mutMinute, osWaitForever);	// Acquire the minute mutex key
//			minute = (minute + 1) % 60;
//			osMutexRelease(mutMinute);
//			
//			if(minute == 0) {
//				// relase the key and inc hour
//				osStatus_t status = osSemaphoreRelease(semHour);
//			}
//		}
		osSemaphoreAcquire(semMinute, osWaitForever);	// Lock the minute semaphore for waiting until the next minute

		osMutexAcquire(mutMinute, osWaitForever);	// Acquire the minute mutex key
		minute = (minute + 1) % 60;
		osMutexRelease(mutMinute);
		
		if(minute == 0) {
			// relase the key and inc hour
			osStatus_t status = osSemaphoreRelease(semHour);
		}
		
    ; // Insert thread code here...
    osThreadYield();                            // suspend thread
  }
}
