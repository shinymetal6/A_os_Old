/*
 * timer.c
 *
 *  Created on: Sep 2, 2023
 *      Author: fil
 */

#include "main.h"
#include "A.h"
#include "scheduler.h"
#include "timer.h"
#include "ports.h"

extern	Asys_t		Asys;

void  SysTick_Handler(void)
{
	if ( Asys.g_os_started )
	{
#ifdef	DEBUG_TICK_ON_PG6
		HAL_GPIO_TogglePin(PG6_Debug_GPIO_Port, PG6_Debug_Pin);
#endif
		Asys.g_tick_count++;
		scan_processes();
		do_pendV();
	}
	else
		  HAL_IncTick();
}

void HAL_Delay(uint32_t tick_count)
{
uint32_t tickstart = HAL_GetTick();
uint32_t wait = tick_count;

	if ( Asys.g_os_started == 0 )
	{
		/* Add a freq to guarantee minimum wait */
		if (wait < HAL_MAX_DELAY)
		{
		wait += (uint32_t)(uwTickFreq);
		}

		while ((HAL_GetTick() - tickstart) < wait)
		{
		}
	}
	else
	{
		__disable_irq();
		process[Asys.current_process].delay_value = Asys.g_tick_count + tick_count;
		if ( Asys.current_process )	// supervisor is constantly enabled
			process[Asys.current_process].wait_event = SUSPEND_ON_DELAY;
		suspend();
		__enable_irq();
	}
}

void init_systick_timer(uint32_t tick_hz)
{
uint32_t ticks = (SYSTICK_TIM_CLK/tick_hz)-1;
    SysTick_Config(ticks);
}

uint32_t create_timer(uint8_t timer_id,uint32_t tick_count,uint8_t flags)
{
uint8_t timer_index = 0;
	if (( process[Asys.current_process].timer_flags[timer_id] & TIMERFLAGS_IN_USE ) == TIMERFLAGS_IN_USE)
		return 1;
	switch(timer_id)
	{
	case	TIMER_ID_0:	timer_index = 0; break;
	case	TIMER_ID_1:	timer_index = 1; break;
	case	TIMER_ID_2:	timer_index = 2; break;
	case	TIMER_ID_3:	timer_index = 3; break;
	case	TIMER_ID_4:	timer_index = 4; break;
	case	TIMER_ID_5:	timer_index = 5; break;
	case	TIMER_ID_6:	timer_index = 6; break;
	case	TIMER_ID_7:	timer_index = 7; break;
	default : return 1;
	}
	__disable_irq();
	process[Asys.current_process].timer_flags[timer_index] = (flags & TIMERFLAGS_USERMASK) | TIMERFLAGS_IN_USE;
	process[Asys.current_process].timer_value[timer_index] = tick_count;
	process[Asys.current_process].current_timer[timer_index] = Asys.g_tick_count + tick_count;
	__enable_irq();
	return 0;
}

uint32_t start_timer(uint8_t timer_id)
{
uint8_t timer_index = 0;
	if (( process[Asys.current_process].timer_flags[timer_id] & TIMERFLAGS_IN_USE ) == TIMERFLAGS_IN_USE)
		return 1;
	switch(timer_id)
	{
	case	TIMER_ID_0:	timer_index = 0; break;
	case	TIMER_ID_1:	timer_index = 1; break;
	case	TIMER_ID_2:	timer_index = 2; break;
	case	TIMER_ID_3:	timer_index = 3; break;
	case	TIMER_ID_4:	timer_index = 4; break;
	case	TIMER_ID_5:	timer_index = 5; break;
	case	TIMER_ID_6:	timer_index = 6; break;
	case	TIMER_ID_7:	timer_index = 7; break;
	default : return 1;
	}
	process[Asys.current_process].timer_flags[timer_index] |= TIMERFLAGS_ENABLED;
	return 0;
}

uint32_t stop_timer(uint8_t timer_id)
{
	if (( process[Asys.current_process].timer_flags[timer_id] & TIMERFLAGS_IN_USE ) == TIMERFLAGS_IN_USE)
		return 1;
	process[Asys.current_process].timer_flags[timer_id] &= ~TIMERFLAGS_ENABLED;
	return 0;
}

uint32_t destroy_timer(uint8_t timer_id)
{
	if (( process[Asys.current_process].timer_flags[timer_id] & TIMERFLAGS_IN_USE ) != TIMERFLAGS_IN_USE)
		return 1;
	__disable_irq();
	process[Asys.current_process].timer_flags[timer_id] = 0;
	__enable_irq();
	return 0;
}

uint8_t get_timer_expired(void)
{
uint8_t tim_exp = process[Asys.current_process].timer_expired;
	process[Asys.current_process].timer_expired &= ~tim_exp;
	return tim_exp;
}
