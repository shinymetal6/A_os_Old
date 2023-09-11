/*
 * hw_uart.c
 *
 *  Created on: Sep 4, 2023
 *      Author: fil
 */


#include "main.h"
#include "../scheduler.h"
#include "../hw_mngr.h"

extern	HWMngr_t	HWMngr[PERIPHERAL_NUM];
extern	Asys_t		Asys;

uint32_t	set_uart1_rx_buffer(uint8_t *rx_buf)
{
	if ( HWMngr[HW_UART1_IRQ].process == Asys.current_process )
	{
		HWMngr[HW_UART1_IRQ].rx_buf = rx_buf;
		return 0;
	}
	return 255;
}

uint32_t send_uart1(uint8_t *ptr,uint16_t len)
{
	if ( HWMngr[HW_UART1_IRQ].process == Asys.current_process )
		return  HAL_UART_Transmit_IT(&huart1, ptr, len);
	else
		return 255;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
uint8_t	owner_process;
	if ( HWMngr[HW_UART1_IRQ].status == STAUS_ALLOCATED)
	{
		if (( owner_process = HWMngr[HW_UART1_IRQ].process ) != 0 )
		{
			if((process[owner_process].wait_event & SUSPEND_ON_UART1_IRQ) == SUSPEND_ON_UART1_IRQ)
			{
				activate_process(owner_process,WAKEUP_FROM_UART1_IRQ,HW_UART_TX_COMPLETE_FLAG);
			}
		}
	}
}
