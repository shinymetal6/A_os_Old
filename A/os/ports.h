/*
 * ports.h
 *
 *  Created on: Sep 8, 2023
 *      Author: fil
 */

#ifndef OS_PORTS_H_
#define OS_PORTS_H_

#define SYSTEM_RAM				__attribute__((section(".sram_4" ))) __attribute__ ((aligned (32)))

#ifdef	STM32U575xx
/*
	Include paths:
	../../A_os/Libraries/STM32U5/STM32_USB_Device_Library/Core
	../../A_os/Drivers/STM32U5/Usb_Device/Target
	../../A_os/Libraries/STM32U5/STM32_USB_Device_Library/Class/CDC
*/
/* defines for stack , in sram, downward */
#define SRAM_START               0x28000000U
#define SRAM_END                 ((SRAM_START) + (SIZE_SRAM) )
#define SIZE_SRAM                ( (16) * (1024))
#define SIZE_TASK_STACK          1024U
#define SIZE_SCHED_STACK         1024U
#define T1_STACK_START           SRAM_END
#define T2_STACK_START           ( (SRAM_END) - (1 * SIZE_TASK_STACK) )
#define T3_STACK_START           ( (SRAM_END) - (2 * SIZE_TASK_STACK) )
#define T4_STACK_START           ( (SRAM_END) - (3 * SIZE_TASK_STACK) )
#define IDLE_STACK_START         ( (SRAM_END) - (4 * SIZE_TASK_STACK) )
#define SCHED_STACK_START        ( (SRAM_END) - (5 * SIZE_TASK_STACK) )
/* defines for memory pool, in sram4,upward */
#define POOL_START              SRAM_START
#define POOL_SIZE               ( (8) * (1024))
#define POOL_END                ((POOL_START) + (POOL_SIZE) )
#define	POOL_BUFSIZE		    256
#define	POOL_NUM			    (POOL_END-POOL_START)/POOL_BUFSIZE

#define	DEBUG_GPIOPORT			PG6_Debug_GPIO_Port
#define	DEBUG_GPIOBIT			PG6_Debug_Pin
#define	LED_1_GPIOPORT			LED_RED_GPIO_Port
#define	LED_1_GPIOBIT			LED_RED_Pin
#define	LED_2_GPIOPORT			LED_GREEN_GPIO_Port
#define	LED_2_GPIOBIT			LED_GREEN_Pin
#define	LED_3_GPIOPORT			LED_BLUE_GPIO_Port
#define	LED_3_GPIOBIT			LED_BLUE_Pin

#define TICK_HZ 				1000U
#define HSI_CLOCK         		160000000U
#define SYSTICK_TIM_CLK   		HSI_CLOCK

#define	PendSV_PRIORITY			7
#define	SysTick_PRIORITY		6
#define	ASSIGNED				1

#endif

#ifdef	STM32H563xx
/*
	Include paths:
	USB :
	../../A_os/Libraries/STM32H5/STM32_USB_Device_Library/Class/CDC/Inc
	../../A_os/Drivers/STM32H5/USB_Device/Target
	../../A_os/Libraries/STM32H5/STM32_USB_Device_Library/Core/Inc
*/
/*
 * for h5 we use only SRAM4, leaving the conventional ram for user
 */
/* defines for stack , in sram, downward */
#define SRAM_START               0x20080000U
#define SRAM_END                 ((SRAM_START) + (SIZE_SRAM) )
#define SIZE_SRAM                ( (128) * (1024))
#define SIZE_TASK_STACK          1024U
#define SIZE_SCHED_STACK         1024U
#define T1_STACK_START           SRAM_END
#define T2_STACK_START           ( (SRAM_END) - (1 * SIZE_TASK_STACK) )
#define T3_STACK_START           ( (SRAM_END) - (2 * SIZE_TASK_STACK) )
#define T4_STACK_START           ( (SRAM_END) - (3 * SIZE_TASK_STACK) )
#define IDLE_STACK_START         ( (SRAM_END) - (4 * SIZE_TASK_STACK) )
#define SCHED_STACK_START        ( (SRAM_END) - (5 * SIZE_TASK_STACK) )
/* defines for memory pool, in sram4,upward */
#define POOL_START              SRAM_START
#define POOL_SIZE               ( (8) * (1024))
#define POOL_END                ((POOL_START) + (POOL_SIZE) )
#define	POOL_BUFSIZE		    256
#define	POOL_NUM			    (POOL_END-POOL_START)/POOL_BUFSIZE

#define	DEBUG_GPIOPORT			PG6_Debug_GPIO_Port
#define	DEBUG_GPIOBIT			PG6_Debug_Pin
#define	LED_1_GPIOPORT			LED3_RED_GPIO_Port
#define	LED_1_GPIOBIT			LED3_RED_Pin
#define	LED_2_GPIOPORT			LED1_GREEN_GPIO_Port
#define	LED_2_GPIOBIT			LED1_GREEN_Pin
#define	LED_3_GPIOPORT			LED2_YELLOW_GPIO_Port
#define	LED_3_GPIOBIT			LED2_YELLOW_Pin

#define TICK_HZ 				1000U
#define HSI_CLOCK         		160000000U
#define SYSTICK_TIM_CLK   		HSI_CLOCK

#define	PendSV_PRIORITY			15
#define	SysTick_PRIORITY		14
#define	ASSIGNED				1
#endif

#ifdef	STM32F746xx
/* defines for memory pool, in sram4 */
#define SRAM_START               0x20040000U
#define SRAM_END                 ((SRAM_START) + (SIZE_SRAM) )
#define SIZE_SRAM                ( (64) * (1024))
#define SIZE_TASK_STACK          1024U
#define SIZE_SCHED_STACK         1024U
#define T1_STACK_START           SRAM_END
#define T2_STACK_START           ( (SRAM_END) - (1 * SIZE_TASK_STACK) )
#define T3_STACK_START           ( (SRAM_END) - (2 * SIZE_TASK_STACK) )
#define T4_STACK_START           ( (SRAM_END) - (3 * SIZE_TASK_STACK) )
#define IDLE_STACK_START         ( (SRAM_END) - (4 * SIZE_TASK_STACK) )
#define SCHED_STACK_START        ( (SRAM_END) - (5 * SIZE_TASK_STACK) )
/* defines for memory pool, in sram4,upward */
#define POOL_START              SRAM_START
#define POOL_SIZE               ( (32) * (1024))
#define POOL_END                ((POOL_START) + (POOL_SIZE) )
#define	POOL_BUFSIZE		    256
#define	POOL_NUM			    (POOL_END-POOL_START)/POOL_BUFSIZE

#define TICK_HZ 				1000U
#define HSI_CLOCK         		160000000U
#define SYSTICK_TIM_CLK   		HSI_CLOCK

#define	PendSV_PRIORITY			15
#define	SysTick_PRIORITY		14

#define	STM32F746xx_QUIRKS		1
#define	ASSIGNED				1

#ifdef aaa
#define RAM_START               0x20040000U
#define SIZE_RAM                ( (64) * (1024))
#define RAM_END                 ((RAM_START) + (SIZE_RAM) )
#define	POOL_START			    RAM_START
#define	POOL_END			    RAM_END
#define	POOL_SIZE			    256
#define	POOL_NUM			    (RAM_END-RAM_START)/POOL_SIZE
/* defines for stack , in sram */
#define SIZE_TASK_STACK          1024U
#define SIZE_SCHED_STACK         1024U
#define SIZE_SRAM                ( (16) * (1024))
#define SRAM_START               0x2003C000
#define SRAM_END                 ((SRAM_START) + (SIZE_SRAM) )
#define T1_STACK_START           SRAM_END
#define T2_STACK_START           ( (SRAM_END) - (1 * SIZE_TASK_STACK) )
#define T3_STACK_START           ( (SRAM_END) - (2 * SIZE_TASK_STACK) )
#define T4_STACK_START           ( (SRAM_END) - (3 * SIZE_TASK_STACK) )
#define IDLE_STACK_START         ( (SRAM_END) - (4 * SIZE_TASK_STACK) )
#define SCHED_STACK_START        ( (SRAM_END) - (5 * SIZE_TASK_STACK) )
#define SYSTEM_RAM				__attribute__((section(".sram_4" ))) __attribute__ ((aligned (32)))

#define	DEBUG_GPIOPORT			PG6_Debug_GPIO_Port
#define	DEBUG_GPIOBIT			PG6_Debug_Pin
#endif
#endif

#ifdef	STM32F722xx
/* defines for memory pool, in sram4 */
#define SRAM_START               0x20020000U
#define SRAM_END                 ((SRAM_START) + (SIZE_SRAM) )
#define SIZE_SRAM                ( (64) * (1024))
#define SIZE_TASK_STACK          1024U
#define SIZE_SCHED_STACK         1024U
#define T1_STACK_START           SRAM_END
#define T2_STACK_START           ( (SRAM_END) - (1 * SIZE_TASK_STACK) )
#define T3_STACK_START           ( (SRAM_END) - (2 * SIZE_TASK_STACK) )
#define T4_STACK_START           ( (SRAM_END) - (3 * SIZE_TASK_STACK) )
#define IDLE_STACK_START         ( (SRAM_END) - (4 * SIZE_TASK_STACK) )
#define SCHED_STACK_START        ( (SRAM_END) - (5 * SIZE_TASK_STACK) )
/* defines for memory pool, in sram4,upward */
#define POOL_START              SRAM_START
#define POOL_SIZE               ( (32) * (1024))
#define POOL_END                ((POOL_START) + (POOL_SIZE) )
#define	POOL_BUFSIZE		    256
#define	POOL_NUM			    (POOL_END-POOL_START)/POOL_BUFSIZE

#define	LED_1_GPIOPORT			LD1_GPIO_Port
#define	LED_1_GPIOBIT			LD1_Pin
#define	LED_2_GPIOPORT			LD2_GPIO_Port
#define	LED_2_GPIOBIT			LD2_Pin
#define	LED_3_GPIOPORT			LD3_GPIO_Port
#define	LED_3_GPIOBIT			LD3_Pin

#define TICK_HZ 				1000U
#define HSI_CLOCK         		216000000U
#define SYSTICK_TIM_CLK   		HSI_CLOCK

#define	PendSV_PRIORITY			15
#define	SysTick_PRIORITY		14
#define	ASSIGNED				1
#endif

#ifdef	STM32F446xx
/* defines for memory pool, in sram4 */
#define SRAM_START               0x20018000U
#define SRAM_END                 ((SRAM_START) + (SIZE_SRAM) )
#define SIZE_SRAM                ( (32) * (1024))
#define SIZE_TASK_STACK          1024U
#define SIZE_SCHED_STACK         1024U
#define T1_STACK_START           SRAM_END
#define T2_STACK_START           ( (SRAM_END) - (1 * SIZE_TASK_STACK) )
#define T3_STACK_START           ( (SRAM_END) - (2 * SIZE_TASK_STACK) )
#define T4_STACK_START           ( (SRAM_END) - (3 * SIZE_TASK_STACK) )
#define IDLE_STACK_START         ( (SRAM_END) - (4 * SIZE_TASK_STACK) )
#define SCHED_STACK_START        ( (SRAM_END) - (5 * SIZE_TASK_STACK) )
/* defines for memory pool, in sram4,upward */
#define POOL_START              SRAM_START
#define POOL_SIZE               ( (8) * (1024))
#define POOL_END                ((POOL_START) + (POOL_SIZE) )
#define	POOL_BUFSIZE		    256
#define	POOL_NUM			    (POOL_END-POOL_START)/POOL_BUFSIZE

#define	LED_1_GPIOPORT			LD2_GPIO_Port
#define	LED_1_GPIOBIT			LD2_Pin

#define TICK_HZ 				1000U
#define HSI_CLOCK         		180000000U
#define SYSTICK_TIM_CLK   		HSI_CLOCK

#define	PendSV_PRIORITY			15
#define	SysTick_PRIORITY		14
#define	ASSIGNED				1
#endif
#ifdef	STM32F429xx
/* defines for memory pool, in sram4 */
#define SRAM_START               0x10000000U
#define SRAM_END                 ((SRAM_START) + (SIZE_SRAM) )
#define SIZE_SRAM                ( (64) * (1024))
#define SIZE_TASK_STACK          1024U
#define SIZE_SCHED_STACK         1024U
#define T1_STACK_START           SRAM_END
#define T2_STACK_START           ( (SRAM_END) - (1 * SIZE_TASK_STACK) )
#define T3_STACK_START           ( (SRAM_END) - (2 * SIZE_TASK_STACK) )
#define T4_STACK_START           ( (SRAM_END) - (3 * SIZE_TASK_STACK) )
#define IDLE_STACK_START         ( (SRAM_END) - (4 * SIZE_TASK_STACK) )
#define SCHED_STACK_START        ( (SRAM_END) - (5 * SIZE_TASK_STACK) )
/* defines for memory pool, in sram4,upward */
#define POOL_START              SRAM_START
#define POOL_SIZE               ( (8) * (1024))
#define POOL_END                ((POOL_START) + (POOL_SIZE) )
#define	POOL_BUFSIZE		    256
#define	POOL_NUM			    (POOL_END-POOL_START)/POOL_BUFSIZE

#define	LED_1_GPIOPORT			LD3_GPIO_Port
#define	LED_1_GPIOBIT			LD3_Pin
#define	LED_2_GPIOPORT			LD4_GPIO_Port
#define	LED_3_GPIOBIT			LD4_Pin

#define TICK_HZ 				1000U
#define HSI_CLOCK         		144000000U
#define SYSTICK_TIM_CLK   		HSI_CLOCK

#define	PendSV_PRIORITY			15
#define	SysTick_PRIORITY		14
#define	ASSIGNED				1
#endif

#ifndef	ASSIGNED
#error "No processor defined"
#endif


#endif /* OS_PORTS_H_ */
