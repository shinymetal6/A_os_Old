/*
 * A.h
 *
 *  Created on: Sep 8, 2023
 *      Author: fil
 */

#ifndef OS_A_H_
#define OS_A_H_



#define MAX_PROCESS				5
#define USR_PROCESS				(MAX_PROCESS-1)
#define MAX_TIMERS				8
#define	MAILBOX_NUM				8
#define	PERIPHERAL_NUM			32

/* peripherals */
#define	HW_DELAY					0
#define	HW_TIMER					1
#define	HW_MBX						2
#define	HW_UART1_IRQ				3
#define	HW_UART2_IRQ				4
#define	HW_UART3_IRQ				5
#define	HW_I2C1_IRQ					6
#define	HW_I2C2_IRQ					7
#define	HW_SPI1_IRQ					8
#define	HW_SPI2_IRQ					9
#define	HW_USB_IRQ					31

/* event to wait */
#define	EVENT_DELAY					(1<<HW_DELAY)
#define	EVENT_TIMER					(1<<HW_TIMER)
#define	EVENT_MBX					(1<<HW_MBX)
#define	EVENT_UART1_IRQ				(1<<HW_UART1_IRQ)
#define	EVENT_UART2_IRQ				(1<<HW_UART2_IRQ)
#define	EVENT_UART3_IRQ				(1<<HW_UART3_IRQ)
#define	EVENT_I2C1_IRQ				(1<<HW_I2C1_IRQ)
#define	EVENT_I2C2_IRQ				(1<<HW_I2C2_IRQ)
#define	EVENT_SPI1_IRQ				(1<<HW_SPI1_IRQ)
#define	EVENT_SPI2_IRQ				(1<<HW_SPI2_IRQ)
#define	EVENT_USB_IRQ				(1<<HW_USB_IRQ)
/* suspend_mode */
#define	SUSPEND_ON_DELAY			EVENT_DELAY
#define	SUSPEND_ON_TIMER			EVENT_TIMER
#define	SUSPEND_ON_MBX				EVENT_MBX
#define	SUSPEND_ON_UART1_IRQ		EVENT_UART1_IRQ
#define	SUSPEND_ON_UART2_IRQ		EVENT_UART2_IRQ
#define	SUSPEND_ON_UART3_IRQ		EVENT_UART3_IRQ
#define	SUSPEND_ON_I2C1_IRQ			EVENT_I2C1_IRQ
#define	SUSPEND_ON_I2C2_IRQ			EVENT_I2C2_IRQ
#define	SUSPEND_ON_SPI1_IRQ			EVENT_SPI1_IRQ
#define	SUSPEND_ON_SPI2_IRQ			EVENT_SPI2_IRQ
#define	SUSPEND_ON_USB_IRQ			EVENT_USB_IRQ
/* wakeup_flags */
#define	WAKEUP_FROM_DELAY			SUSPEND_ON_DELAY
#define	WAKEUP_FROM_TIMER			SUSPEND_ON_TIMER
#define	WAKEUP_FROM_MBX				SUSPEND_ON_MBX
#define	WAKEUP_FROM_UART1_IRQ		SUSPEND_ON_UART1_IRQ
#define	WAKEUP_FROM_UART2_IRQ		SUSPEND_ON_UART2_IRQ
#define	WAKEUP_FROM_UART3_IRQ		SUSPEND_ON_UART3_IRQ
#define	WAKEUP_FROM_I2C1_IRQ		SUSPEND_ON_I2C1_IRQ
#define	WAKEUP_FROM_I2C2_IRQ		SUSPEND_ON_I2C2_IRQ
#define	WAKEUP_FROM_SPI1_IRQ		SUSPEND_ON_SPI1_IRQ
#define	WAKEUP_FROM_SPI2_IRQ		SUSPEND_ON_SPI2_IRQ
#define	WAKEUP_FROM_USB_IRQ			SUSPEND_ON_USB_IRQ

#define DUMMY_XPSR  				0x01000000U

typedef struct
{
	void 		(*user_process)(void);
	uint16_t	stack_size;
}USRprcs_t;

extern	void apply_quirks(void);

extern	void supervisor_process1(void);
extern	void supervisor_process2(void);
extern	void supervisor_process3(void);
extern	void supervisor_process4(void);

#endif /* OS_A_H_ */
