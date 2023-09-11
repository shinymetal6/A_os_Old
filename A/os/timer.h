/*
 * timer.h
 *
 *  Created on: Sep 2, 2023
 *      Author: fil
 */

#ifndef TIMER_H_
#define TIMER_H_

#define	TIMER_ID_0		0x01
#define	TIMER_ID_1		0x02
#define	TIMER_ID_2		0x04
#define	TIMER_ID_3		0x08
#define	TIMER_ID_4		0x10
#define	TIMER_ID_5		0x20
#define	TIMER_ID_6		0x40
#define	TIMER_ID_7		0x80

extern void __attribute__ ((noinline)) suspend(void);
extern	void init_systick_timer(uint32_t tick_hz);
extern	uint32_t create_timer(uint8_t timer_id,uint32_t tick_count,uint8_t flags);
extern	uint32_t destroy_timer(uint8_t timer_id);
extern	uint32_t start_timer(uint8_t timer_id);
extern	uint8_t get_timer_expired(void);

#endif /* TIMER_H_ */
