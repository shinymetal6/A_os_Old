/*
 * memory_processes.c
 *
 *  Created on: Sep 6, 2023
 *      Author: fil
 */

/*
 * uart_processes.c
 *
 *  Created on: Sep 2, 2023
 *      Author: fil
 */

#include "main.h"
#include "../os/A_user_callable_functions.h"
#include <stdio.h>
#include <string.h>
extern	Asys_t		Asys;

uint8_t	mbx_data[128];
uint8_t	tx_buf[256];

uint8_t		*mem_ptr1;
uint8_t		*mem_ptr2;
uint8_t		*mem_ptr3;
uint8_t		*mem_ptr4;

void process1_handler(void)
{
uint32_t	wakeup;
uint32_t	tval = 0;

	create_timer(TIMER_ID_0,50,TIMERFLAGS_DISABLED | TIMERFLAGS_FOREVER);

	while(1)
	{
		wakeup = wait_event(SUSPEND_ON_TIMER );
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			if ( tval == 0)
			{
				mem_ptr1 = mem_get(256);
				mem_ptr2 = mem_get(512);
				tval=1;
			}
			else
			{
				mem_release(mem_ptr2);
				mem_release(mem_ptr1);
				tval = 0;
			}
			HAL_GPIO_TogglePin(LED_1_GPIOPORT, LED_1_GPIOBIT);
		}
	}
}

void process2_handler(void)
{
uint32_t	wakeup;
uint32_t	tval = 0;
uint8_t		*mem2_ptr2;

	create_timer(TIMER_ID_1,100,TIMERFLAGS_ENABLED | TIMERFLAGS_FOREVER);
	while(1)
	{
		wakeup = wait_event(EVENT_TIMER);
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			if ( tval == 0)
			{
				mem2_ptr2 = mem_get(513);
				tval=1;
			}
			else
			{
				mem_release(mem2_ptr2);
				tval = 0;
			}
			HAL_GPIO_TogglePin(LED_2_GPIOPORT, LED_2_GPIOBIT);
		}
	}
}

void process3_handler(void)
{
uint32_t	wakeup;
uint32_t	tval = 0;
uint8_t		*mem_ptr0;
uint8_t		*mem_ptr1;
uint8_t		*mem_ptr2;
uint8_t		*mem_ptr3;

	create_timer(TIMER_ID_2,200,TIMERFLAGS_ENABLED | TIMERFLAGS_FOREVER);
	while(1)
	{
		wakeup = wait_event(EVENT_TIMER);
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			if ( tval == 0)
			{
				mem_ptr0 = mem_get(512);
				mem_ptr1 = mem_get(512);
				mem_ptr2 = mem_get(512);
				mem_ptr3 = mem_get(512);
				tval=1;
			}
			else
			{
				/*
				void (*func)(void) = 0;
			    func();
			    */
				mem_release(mem_ptr0);
				mem_release(mem_ptr1);
				mem_release(mem_ptr2);
				mem_release(mem_ptr3);
				tval = 0;
			}
			//HAL_GPIO_TogglePin(LED_3_GPIOPORT, LED_3_GPIOBIT);
		}
	}
}

void process4_handler(void)
{
	uint32_t	wakeup;
	create_timer(TIMER_ID_3,400,TIMERFLAGS_ENABLED | TIMERFLAGS_FOREVER);
	while(1)
	{
		wakeup = wait_event(SUSPEND_ON_TIMER);
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
			HAL_GPIO_TogglePin(LED_3_GPIOPORT, LED_3_GPIOBIT);
	}

	/*
	void (*func)(void) = 0;
    func();

	*/
}


