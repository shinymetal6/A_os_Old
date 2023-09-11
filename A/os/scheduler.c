/*
 * scheduler.c
 *
 *  Created on: Sep 2, 2023
 *      Author: fil
 *      https://github.com/niekiran/CortexMxProgramming/blob/master/Source_code/016_cmsis_task_scheduler/
 */


#include "main.h"
#include "scheduler.h"
#include "A.h"
#include "hw_mngr.h"

uint32_t get_psp_value(void)
{

	return process[Asys.current_process].psp_value;
}

void save_psp_value(uint32_t current_psp_value)
{
	process[Asys.current_process].psp_value = current_psp_value;
}

void next_process(void)
{
register uint8_t	i;
register uint8_t	state = PROCESS_WAITING_STATE;

	for( i= 0 ; i < (MAX_PROCESS) ; i++)
	{
		Asys.current_process++;
		Asys.current_process %= MAX_PROCESS;
	    if ( Asys.current_process == 0)	// run supervisor periodically, each MAX_PROCESS schedules
	    {
			return;
	    }
		state = process[Asys.current_process].current_state;
		if( ((state & PROCESS_READY_STATE)== PROCESS_READY_STATE) && (Asys.current_process != 0) )
		{
			return;
		}
	}
	if((state & PROCESS_READY_STATE) != PROCESS_READY_STATE)
	{
		Asys.current_process = 0;
	}
}


void __attribute__ ((noinline)) do_pendV(void)
{
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

void __attribute__ ((noinline)) suspend(void)
{
	__disable_irq();
	process[Asys.current_process].current_state = PROCESS_WAITING_STATE;
	do_pendV();
	__enable_irq();
}

uint32_t __attribute__ ((noinline)) wait_event(uint32_t events)
{
uint32_t wake;
	__disable_irq();
	process[Asys.current_process].wait_event = events;
	suspend();
	wake = process[Asys.current_process].wakeup_rsn;
	process[Asys.current_process].wakeup_rsn = 0;
	__enable_irq();
	return wake;
}

__attribute__((naked)) void PendSV_Handler(void)
{
	/*Save the context of current process */
	//1. Get current running process's PSP value
	__asm volatile("MRS R0,PSP");
	//2. Using that PSP value store SF2( R4 to R11)
	__asm volatile("STMDB R0!,{R4-R11}");
	__asm volatile("PUSH {LR}");
	//3. Save the current value of PSP
    __asm volatile("BL save_psp_value");
	/*Retrieve the context of next process */
	//1. Decide next process to run
    __asm volatile("BL next_process");
	//2. get its past PSP value
	__asm volatile ("BL get_psp_value");
	//3. Using that PSP value retrieve SF2(R4 to R11)
	__asm volatile ("LDMIA R0!,{R4-R11}");
	//4. update PSP and exit
	__asm volatile("MSR PSP,R0");
	__asm volatile("POP {LR}");
	__asm volatile("BX LR");
}

void scan_processes(void)
{
register uint8_t	i,j;

	for( i = 1 ; i < MAX_PROCESS ; i++)
	{
		if((process[i].current_state & PROCESS_INACTIVE_STATE) != PROCESS_INACTIVE_STATE)
		{
			if((process[i].current_state & PROCESS_READY_STATE) != PROCESS_READY_STATE)
			{
				if((process[i].wait_event & SUSPEND_ON_DELAY) == SUSPEND_ON_DELAY)
				{
					if(process[i].delay_value == Asys.g_tick_count)
					{
						process[i].current_state |= PROCESS_READY_STATE;
						process[i].wakeup_rsn |= WAKEUP_FROM_DELAY;
						process[i].wakeup_flags = 0;
					}
				}

				if((process[i].wait_event & SUSPEND_ON_TIMER) == SUSPEND_ON_TIMER)
				{
					for( j = 0 ; j < MAX_TIMERS ; j++)
					{
						if(process[i].current_timer[j] == Asys.g_tick_count)
						{
							process[i].current_state |= PROCESS_READY_STATE;
							if ((process[i].timer_flags[j] & TIMERFLAGS_FOREVER ) == TIMERFLAGS_FOREVER)
							{
								process[i].current_timer[j] = Asys.g_tick_count + process[i].timer_value[j];
							}
							process[i].timer_expired |= (1<<j);
							process[i].wakeup_rsn |= WAKEUP_FROM_TIMER;
							process[i].wakeup_flags = j;
						}
					}
				}
			}
		}
	}
}

uint32_t inline activate_process(uint8_t dest_process,uint32_t rsn , uint32_t flags)
{
	__disable_irq();
	process[dest_process].wakeup_rsn |= rsn;
	process[dest_process].wakeup_flags |= flags;
	process[dest_process].current_state = PROCESS_WAITING_STATE;
	process[dest_process].current_state |= PROCESS_READY_STATE;
	__enable_irq();
	return 0;
}

