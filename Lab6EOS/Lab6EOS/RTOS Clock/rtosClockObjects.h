#include <stdint.h>
#include "cmsis_os2.h"
#ifndef __rtosClockObjects
	#define __rtosClockObjects
	
	// shared variables and mutexes
	extern uint32_t hour; 
	extern uint32_t minute; 
	extern uint32_t second;
	extern osMutexId_t mutHour; 
	extern osMutexId_t mutMinute; 
	extern osMutexId_t mutSecond;
	
	
	// flag semaphores
	extern osSemaphoreId_t semDisplayTime;
	extern osSemaphoreId_t semSecond;
	extern osSemaphoreId_t semMinute;
	extern osSemaphoreId_t semHour;
	
	
	//threads
	extern osThreadId_t tid_thdDisplayTime;
	extern osThreadId_t second_Thread;
	extern osThreadId_t minute_Thread;
	extern osThreadId_t hour_Thread;
	int Init_thdDisplayTime (void);
#endif
