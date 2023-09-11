/*
 * mem.h
 *
 *  Created on: Sep 5, 2023
 *      Author: fil
 */

#ifndef OS_MEM_H_
#define OS_MEM_H_

typedef struct
{
	uint8_t		*nxt_link;
	uint8_t		*pre_link;
	uint8_t		*mem_ptr;
	uint8_t		chunk_count;
	uint8_t		chunk_index;
	uint8_t		process;
	uint8_t		flags;
}MEMpool_t;

/* flags */
#define		MEM_IN_USE			0x01
#define		MEM_CHANGED_OWNER	0x02
#define		MEM_IN_LIST			0x04
#define		LAST_IN_LIST		0x80

extern	void mem_init(void);

#endif /* OS_MEM_H_ */
