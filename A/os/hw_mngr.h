/*
 * hw_mngr.h
 *
 *  Created on: Sep 2, 2023
 *      Author: fil
 */

#ifndef HW_MNGR_H_
#define HW_MNGR_H_

#define	HW_UART_TX_COMPLETE_FLAG	0x00000001
#define	HW_UART_RX_COMPLETE_FLAG	0x00000002
#define	HW_USB_TX_COMPLETE_FLAG		0x00000001
#define	HW_USB_RX_COMPLETE_FLAG		0x00000002
extern	UART_HandleTypeDef huart1;
#define	HW_MAX_RX_SIZE				256

typedef struct
{
	uint8_t 	process;
	uint8_t		status;
	uint16_t	rxlen;
	uint32_t	flags;
	uint8_t		*rx_buf;
}HWMngr_t;
#define	STAUS_FREE		0
#define	STAUS_ALLOCATED	1
#endif /* HW_MNGR_H_ */
