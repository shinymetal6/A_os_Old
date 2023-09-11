/*
 * exceptions.c
 *
 *  Created on: Sep 9, 2023
 *      Author: fil
 */

#include "main.h"
#include "scheduler.h"
#include "A.h"

void HardFault_Handler(void)
{
	process[Asys.current_process].current_state = PROCESS_WAITING_STATE;
	process[Asys.current_process].current_state |= (PROCESS_INACTIVE_STATE | PROCESS_HARDFAULT_STATE);
	Asys.failed_process = Asys.current_process;
	Asys.fail_rsn = PROCESS_HARDFAULT_STATE;
}
