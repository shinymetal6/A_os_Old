/*
 * test.c
 *
 *  Created on: Sep 11, 2023
 *      Author: fil
 */


#include "main.h"
#include "../os/A_user_callable_functions.h"
#include <stdio.h>
#include <string.h>

void process1_handler(void)
{
uint32_t	wakeup;
uint32_t	tval = 0;

	create_timer(TIMER_ID_0,500,TIMERFLAGS_DISABLED | TIMERFLAGS_FOREVER);
	while(1)
	{
		wakeup = wait_event(SUSPEND_ON_TIMER );
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			HAL_GPIO_TogglePin(LED_2_GPIOPORT, LED_2_GPIOBIT);
		}
	}
}

void process2_handler(void)
{
uint32_t	wakeup;
uint32_t	tval = 0;

	create_timer(TIMER_ID_0,500,TIMERFLAGS_DISABLED | TIMERFLAGS_FOREVER);
	while(1)
	{
		wakeup = wait_event(SUSPEND_ON_TIMER );
		HAL_GPIO_TogglePin(LED_3_GPIOPORT, LED_3_GPIOBIT);
	}
}

void process3_handler(void)
{
uint32_t	wakeup;
uint32_t	tval = 0;

	create_timer(TIMER_ID_0,500,TIMERFLAGS_DISABLED | TIMERFLAGS_FOREVER);
	while(1)
	{
		wakeup = wait_event(SUSPEND_ON_TIMER );
	}
}

void process4_handler(void)
{
uint32_t	wakeup;
uint32_t	tval = 0;

	create_timer(TIMER_ID_0,50,TIMERFLAGS_DISABLED | TIMERFLAGS_FOREVER);

}
