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

uint8_t	swsw=0;
void process1_handler(void)
{
uint32_t	wakeup;
uint8_t		tim;
	create_timer(TIMER_ID_0,200,TIMERFLAGS_DISABLED | TIMERFLAGS_FOREVER);
	create_timer(TIMER_ID_1,1000,TIMERFLAGS_DISABLED | TIMERFLAGS_FOREVER);
	while(1)
	{
		wakeup = wait_event(SUSPEND_ON_TIMER );
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			tim = get_timer_expired();
			if ( tim == (TIMER_ID_0 | TIMER_ID_1) )
#ifdef	STM32F746xx
				swsw++;
#else
				HAL_GPIO_TogglePin(LED_1_GPIOPORT, LED_1_GPIOBIT);
#endif
		}
	}
}

void process2_handler(void)
{
uint32_t	wakeup;
uint32_t	tval = 0;

	create_timer(TIMER_ID_0,100,TIMERFLAGS_DISABLED | TIMERFLAGS_FOREVER);
	while(1)
	{
		wakeup = wait_event(SUSPEND_ON_TIMER );
		HAL_GPIO_TogglePin(LED_2_GPIOPORT, LED_2_GPIOBIT);
	}
}

uint8_t line[32];
void process3_handler(void)
{
uint32_t	wakeup;
uint32_t	tval = 0;
uint8_t		*mem_ptr1 = NULL;

	create_timer(TIMER_ID_0,500,TIMERFLAGS_DISABLED | TIMERFLAGS_FOREVER);
	while(1)
	{
		wakeup = wait_event(SUSPEND_ON_TIMER );
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			if ( mem_ptr1 != NULL )
				mem_release(mem_ptr1);
			mem_ptr1 = mem_get(256);
			sprintf((char *)mem_ptr1,"Line transmitted %d\n\r",tval);
			CDC_Transmit_FS(mem_ptr1,strlen((char *)mem_ptr1));
			tval++;
		}
		HAL_GPIO_TogglePin(LED_3_GPIOPORT, LED_3_GPIOBIT);
	}
}

void process4_handler(void)
{
uint32_t	wakeup;
uint32_t	tval = 0;

	create_timer(TIMER_ID_0,50,TIMERFLAGS_DISABLED | TIMERFLAGS_FOREVER);
	while(1);
}
