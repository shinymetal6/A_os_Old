/*
 * port_quirks.c
 *
 *  Created on: Sep 11, 2023
 *      Author: fil
 */

#include "main.h"
#include "ports.h"

void apply_quirks(void)
{
#ifdef STM32F746xx_QUIRKS
	DBGMCU->APB1FZ = 0xffffffff;
	DBGMCU->APB2FZ = 0xffffffff;
#endif
}

