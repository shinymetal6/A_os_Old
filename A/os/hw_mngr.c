/*
 * hw_mngr.c
 *
 *  Created on: Sep 2, 2023
 *      Author: fil
 */

#include "main.h"

#include "scheduler.h"

extern	HWMngr_t	HWMngr[PERIPHERAL_NUM];
extern	Asys_t		Asys;

uint32_t allocate_hw(uint32_t peripheral)
{
	if ( HWMngr[peripheral].process )
		return 0;
	HWMngr[peripheral].process = Asys.current_process;
	HWMngr[peripheral].status = STAUS_ALLOCATED;
	return peripheral;
}

uint32_t deallocate_hw(uint32_t peripheral)
{
	if ( HWMngr[peripheral].process != Asys.current_process )
		return 0;
	HWMngr[peripheral].process = 0;
	HWMngr[peripheral].status = STAUS_FREE;
	return peripheral;
}

uint16_t get_rx_len(uint32_t peripheral)
{
	if ( HWMngr[peripheral].process != Asys.current_process )
		return 0;
	return HWMngr[HW_USB_IRQ].rxlen;
}

uint32_t get_peripheral_flags(uint32_t peripheral)
{
	if ( HWMngr[peripheral].process != Asys.current_process )
		return 0;
	return HWMngr[HW_USB_IRQ].flags;
}

