/*
 * scheduler.h
 *
 *  Created on: Sep 2, 2023
 *      Author: fil
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "A.h"
#include "mem.h"
#include "ports.h"
#include "hw_mngr.h"

#define PROCESS_WAITING_STATE  		0x00
#define PROCESS_READY_STATE 	 	0x01
#define PROCESS_MEMORY_EXHAUSTED	0x20
#define PROCESS_HARDFAULT_STATE		0x40
#define PROCESS_INACTIVE_STATE 		0x80

typedef struct
{
	uint32_t	psp_value;
	uint32_t	stack_start;
	uint32_t	delay_value;
	uint32_t	current_timer[MAX_TIMERS];
	uint32_t	timer_value[MAX_TIMERS];
	uint8_t		timer_flags[MAX_TIMERS];
	uint8_t		timer_expired;
	uint8_t		*mbx[MAILBOX_NUM];
	uint32_t	mbx_size[MAILBOX_NUM];
	uint8_t		mbx_number;
	uint32_t	wait_event;
	uint8_t		current_state;
	uint32_t	wakeup_rsn;
	uint32_t	wakeup_flags;
	void (*process_handler)(void);
}PCB_t;
/* timer_flags */
#define	TIMERFLAGS_ONESHOT			0x00
#define	TIMERFLAGS_FOREVER			0x01
#define	TIMERFLAGS_ENABLED			0x02
#define	TIMERFLAGS_IN_USE			0x80
#define	TIMERFLAGS_DISABLED			0x00
#define	TIMERFLAGS_USERMASK			0x0f

typedef struct
{
	uint8_t		current_process;
	uint32_t	g_tick_count;
	uint32_t	g_os_started;
	uint8_t		*first_mem;
	uint32_t	num_buf_in_use;
	uint32_t	max_num_buf_in_use;
	uint32_t	first_data_address;
	MEMpool_t 	*first_of_list;
	MEMpool_t 	*last_of_list;
	uint32_t	system_flags;
	uint8_t		failed_process;
	uint8_t		fail_rsn;
	uint8_t		last_failed_process;
	uint8_t		last_fail_rsn;
}Asys_t;

/* system_flags */
#define	SYS_MEM_DEFRAG_REQUEST	0x00000001

extern	void supervisor_process(void);
extern	void process1_handler(void); //This is process1
extern	void process2_handler(void); //this is process2
extern	void process3_handler(void); //this is process3
extern	void process4_handler(void); // this is process4 of the application
extern	uint32_t activate_process(uint8_t dest_process,uint32_t rsn , uint32_t flags);
extern	void scan_processes(void);
extern	void __attribute__ ((noinline)) do_pendV(void);
extern void find_orphaned_chunks(uint8_t process);


extern SYSTEM_RAM	PCB_t 		process[MAX_PROCESS];
extern SYSTEM_RAM	HWMngr_t	HWMngr[PERIPHERAL_NUM];
extern SYSTEM_RAM	Asys_t		Asys;

/* internal debug */
//#define	DEBUG_TICK_ON_GPIO			1
//#define	DEBUG_SCHED_IDLE_ON_GPIO	1
//#define	DEBUG_MEM_ON_GPIO			1
//#define	DEBUG_MEM_INIT_ON_GPIO		1
//#define	DEBUG_MEM_DEFRAG_ON_GPIO	1
//#define	DEBUG_MEM_GET_ON_GPIO		1
//#define	DEBUG_MEM_RELEASE_ON_GPIO	1
//#define	DEBUG_SUPERVISOR_ON_GPIO	1

#endif /* SCHEDULER_H_ */
