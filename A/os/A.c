/*
 * A.c
 *
 *  Created on: Sep 8, 2023
 *      Author: fil
 */

#include "main.h"
#include "A.h"
#include "scheduler.h"
#include "mem.h"
#include "timer.h"
#include <strings.h>

SYSTEM_RAM	PCB_t 		process[MAX_PROCESS];
SYSTEM_RAM	HWMngr_t	HWMngr[PERIPHERAL_NUM];
SYSTEM_RAM	Asys_t		Asys;
SYSTEM_RAM	MEMpool_t	MEMpool[POOL_NUM];

extern	USRprcs_t	USRprcs[USR_PROCESS];
extern	USRprcs_t	UserProcesses[USR_PROCESS];

uint32_t A_setup_user_functions(USRprcs_t *UserProcessTable , uint8_t numprc)
{
uint8_t	i;
	if ( numprc > USR_PROCESS)
		return 1;
	for(i=0;i<numprc;i++)
		USRprcs[i].user_process = UserProcessTable[i].user_process;
	return 0;
}

static void A_init_processes_stack(void)
{
uint8_t		i,j;
uint32_t	lstack = SRAM_END;
uint32_t	*pPSP;

	process[0].process_handler = supervisor_process;
	process[1].process_handler = supervisor_process1;
	process[2].process_handler = supervisor_process2;
	process[3].process_handler = supervisor_process3;
	process[4].process_handler = supervisor_process4;

	for( i = 0 ; i < MAX_PROCESS ;i++)
	{
		process[i].stack_start = process[i].psp_value = lstack;
		if ( i == 0 )
		{
			lstack -= SIZE_TASK_STACK;
			bzero((uint8_t *)(process[i].stack_start-SIZE_TASK_STACK),SIZE_TASK_STACK);
		}
		else
		{
			lstack -= UserProcesses[i-1].stack_size;
			bzero((uint8_t *)(process[i].stack_start-UserProcesses[i-1].stack_size),UserProcesses[i-1].stack_size);
		}
		pPSP = (uint32_t*) process[i].psp_value;
		pPSP--;
		*pPSP = DUMMY_XPSR;//0x00100000
		pPSP--; //PC
		*pPSP = (uint32_t) process[i].process_handler;
		pPSP--; //LR
		*pPSP = 0xFFFFFFFD;
		for( j = 0 ; j < 13 ; j++)
		{
			pPSP--;
		    *pPSP = 0;
		}
		process[i].psp_value = (uint32_t)pPSP;
		process[i].current_state = PROCESS_WAITING_STATE;
		process[i].current_state |= PROCESS_READY_STATE;
	}
}


static void A_init_memory(void)
{
	bzero(&Asys,sizeof(Asys));
	bzero(HWMngr,sizeof(HWMngr));
	bzero(process,sizeof(process));
	bzero((uint8_t *)(SCHED_STACK_START-SIZE_TASK_STACK),SIZE_TASK_STACK*MAX_PROCESS);
}
/*
void inline A_Debug_Set_One(void)
{
	  HAL_GPIO_WritePin(PG6_Debug_GPIO_Port, PG6_Debug_Pin, GPIO_PIN_SET);
}

void inline A_Debug_Set_Zero(void)
{
	  HAL_GPIO_WritePin(PG6_Debug_GPIO_Port, PG6_Debug_Pin, GPIO_PIN_RESET);
}
*/
static __attribute__((naked)) void A_init_wait_event_stack(uint32_t sched_top_of_stack)
{
     __set_MSP(sched_top_of_stack);
     __asm volatile("BX LR");
}


__attribute__((naked)) void A_switch_sp_to_psp(void)
{
    //1. initialize the PSP with process1 stack start address
	//get the value of psp of current_process
	__asm volatile ("PUSH {LR}"); //preserve LR which connects back to main()
	__asm volatile ("BL get_psp_value");
	__asm volatile ("MSR PSP,R0"); //initialize psp
	__asm volatile ("POP {LR}");  //pops back LR value
	//2. change SP to PSP using CONTROL register
	__asm volatile ("MOV R0,#0X02");
	__asm volatile ("MSR CONTROL,R0");
	__asm volatile ("BX LR");
}

void A_start(void)
{
	__disable_irq();

	HAL_NVIC_SetPriority(PendSV_IRQn,  PendSV_PRIORITY, 0);		/* Make PendSV_IRQn lower priority */
	HAL_NVIC_SetPriority(SysTick_IRQn, SysTick_PRIORITY, 0);	/* Make PendSV_IRQn lower priority */

	A_init_memory();
	mem_init();
	A_init_wait_event_stack(SCHED_STACK_START);
	A_init_processes_stack();
	A_setup_user_functions((USRprcs_t *)&UserProcesses[0],USR_PROCESS);
	A_switch_sp_to_psp();
	init_systick_timer(TICK_HZ);
	Asys.g_os_started = 1;
	__enable_irq();
	supervisor_process();
	while(1);
}


