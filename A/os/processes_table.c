/*
 * processes_table.c
 *
 *  Created on: Sep 8, 2023
 *      Author: fil
 */

#include "main.h"
#include "A.h"
#include "scheduler.h"

extern	void process1_handler(void);	//This is process1
extern	void process2_handler(void);	//This is process2
extern	void process3_handler(void);	//This is process3
extern	void process4_handler(void);	//This is process4 of the application

USRprcs_t	UserProcesses[USR_PROCESS] =
{
		{
				.user_process = process1_handler,
				.stack_size = 256,
		},
		{
				.user_process = process2_handler,
				.stack_size = 256,
		},
		{
				.user_process = process3_handler,
				.stack_size = 256,
		},
		{
				.user_process = process4_handler,
				.stack_size = 256,
		}
};
