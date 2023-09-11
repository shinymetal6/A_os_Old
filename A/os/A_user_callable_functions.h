/*
 * A_user_callable_functions.h
 *
 *  Created on: Sep 2, 2023
 *      Author: fil
 */

#ifndef A_USER_CALLABLE_FUNCTIONS_H_
#define A_USER_CALLABLE_FUNCTIONS_H_

#include "scheduler.h"
#include "timer.h"


extern	uint32_t wait_event(uint32_t events);

extern	void mbx_send(uint8_t process_number,uint8_t mailbox_number,uint8_t *mbx_ptr,uint32_t mbx_size);
extern	uint32_t mbx_receive(uint8_t mailbox_number,uint8_t *buf_ptr);

extern	uint32_t allocate_hw(uint32_t hwpriv);
extern	uint32_t deallocate_hw(uint32_t hwpriv);
extern	uint16_t get_rx_len(uint32_t peripheral);
extern	uint32_t get_peripheral_flags(uint32_t peripheral);

extern	uint8_t *mem_get(uint32_t size );
extern	uint32_t mem_release(uint8_t *data_ptr);


extern	uint32_t send_uart1(uint8_t *ptr,uint16_t len);
extern	uint32_t set_uart1_rx_buffer(uint8_t *rx_buf);
extern	uint32_t send_usb(uint8_t* ptr, uint16_t len);
extern	uint32_t set_usb_rx_buffer(uint8_t *rx_buf);


extern	void A_Delay(uint32_t tick_count);

#endif /* A_USER_CALLABLE_FUNCTIONS_H_ */
