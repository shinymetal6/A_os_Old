/*
 * supervisor_process.c
 *
 *  Created on: Sep 2, 2023
 *      Author: fil
 */

#include "main.h"
#include "A.h"
#include "scheduler.h"

extern	void defrag_mem(void);
extern	void __attribute__ ((noinline)) suspend(void);

SYSTEM_RAM	USRprcs_t	USRprcs[USR_PROCESS] =
{
	{
			.user_process = process1_handler,
			.stack_size = SIZE_TASK_STACK,
	},
	{
			.user_process = process2_handler,
			.stack_size = SIZE_TASK_STACK,
	},
	{
			.user_process = process3_handler,
			.stack_size = SIZE_TASK_STACK,
	},
	{
			.user_process = process4_handler,
			.stack_size = SIZE_TASK_STACK,
	}
};

void supervisor_process(void)
{
	while(1)
	{
		if ( Asys.failed_process != 0 )
		{
			find_orphaned_chunks(Asys.failed_process);
			Asys.last_failed_process = Asys.failed_process;
			Asys.last_fail_rsn = Asys.fail_rsn ;
			Asys.failed_process = Asys.fail_rsn = 0;
		}
		defrag_mem();
		HAL_Delay(100);
	}
}

void supervisor_process1(void)
{
	USRprcs[0].user_process();
	process[Asys.current_process].current_state |= PROCESS_INACTIVE_STATE;
	while(1);
}

void supervisor_process2(void)
{
	USRprcs[1].user_process();
	process[Asys.current_process].current_state |= PROCESS_INACTIVE_STATE;
	while(1);
}

void supervisor_process3(void)
{
	USRprcs[2].user_process();
	process[Asys.current_process].current_state |= PROCESS_INACTIVE_STATE;
	while(1);
}

void supervisor_process4(void)
{
	USRprcs[3].user_process();
	process[Asys.current_process].current_state |= PROCESS_INACTIVE_STATE;
	while(1);
}

