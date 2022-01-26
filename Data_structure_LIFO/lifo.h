/*
 * lifo.h
 *
 *  Created on: Jan 25, 2022
 *      Author: Mina
 */

#ifndef LIFO_H_
#define LIFO_H_

typedef struct{
	unsigned int length ;
	unsigned int* head ;
	unsigned int count ;
}LIFO_Buf_t;

typedef enum {
	LIFO_no_error,
	LIFO_full,
	LIFO_empty,
	LIFO_NULL
}Buffer_status;

Buffer_status LIFO_Add_item (LIFO_Buf_t* lifo_buf,unsigned int item);
Buffer_status LIFO_get_item (LIFO_Buf_t* lifo_buf,unsigned int* item);
Buffer_status LIFO_init (LIFO_Buf_t* lifo_buf,unsigned int* buf, unsigned int length);




#endif /* LIFO_H_ */
