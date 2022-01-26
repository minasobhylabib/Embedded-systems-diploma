/*
 * lifo.h
 *
 *  Created on: Jan 25, 2022
 *      Author: Mina
 */

#ifndef FIFO_H_
#define FIFO_H_

#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
//select the type (uint8_t, uint16_t, uint32_t)
#define type uint32_t


//select buffer size
typedef struct{
	unsigned int length ;
	type* base;
	type* head;
	type* tail ;
	unsigned int count ;
}FIFO_Buf_t;

typedef enum {
	FIFO_no_error,
	FIFO_full,
	FIFO_empty,
	FIFO_NULL
}Buffer_status;

Buffer_status FIFO_init (FIFO_Buf_t* fifo_buf,type* buf, unsigned int number_elements);
Buffer_status FIFO_enqueue (FIFO_Buf_t* fifo_buf,type* buf, type* item);
Buffer_status FIFO_dequeue (FIFO_Buf_t* fifo_buf,type* buf,type* item);
Buffer_status FIFO_IS_FULL (FIFO_Buf_t* fifo_buf,type* buf);
void FIFO_PRINT(FIFO_Buf_t* fifo_buf);



#endif /* LIFO_H_ */
