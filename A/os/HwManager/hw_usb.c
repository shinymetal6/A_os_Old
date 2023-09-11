/*
 * hw_usb.c
 *
 *  Created on: Sep 4, 2023
 *      Author: fil
 */


#include "main.h"
#include "../scheduler.h"
#include "../hw_mngr.h"
#include <string.h>

extern	HWMngr_t	HWMngr[PERIPHERAL_NUM];
extern	Asys_t		Asys;

uint32_t	set_usb_rx_buffer(uint8_t *rx_buf)
{
	if ( HWMngr[HW_USB_IRQ].process == Asys.current_process )
	{
		HWMngr[HW_USB_IRQ].rx_buf = rx_buf;
		return 0;
	}
	return 255;
}

uint32_t UsbPktReceived(uint8_t* Buf, uint32_t Len)
{
uint8_t	*dest_ptr = HWMngr[HW_USB_IRQ].rx_buf;
	if ( dest_ptr != NULL )
	{
		HWMngr[HW_USB_IRQ].rxlen = Len;
		memcpy(dest_ptr,Buf,Len);
		dest_ptr[Len] = 0;
		activate_process(HWMngr[HW_USB_IRQ].process,WAKEUP_FROM_USB_IRQ,HW_USB_RX_COMPLETE_FLAG);
		return	Len;
	}
	return 0;
}

void UsbControlCallback(uint8_t cmd, uint8_t* pbuf, uint16_t length)
{
}

extern	uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len);

uint32_t send_usb(uint8_t* ptr, uint16_t len)
{
	if (( HWMngr[HW_USB_IRQ].process == Asys.current_process ) && ( len != 0 ))
	{
		CDC_Transmit_FS(ptr, len);
		return 0;
	}
	return 255;
}
