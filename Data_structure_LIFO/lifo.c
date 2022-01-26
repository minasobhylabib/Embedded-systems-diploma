/*
 * lifo.c
 *
 *  Created on: Jan 25, 2022
 *      Author: Mina
 */
# include "lifo.h"
# include "stdlib.h"
Buffer_status LIFO_Add_item (LIFO_Buf_t* lifo_buf, unsigned int item)
{
	if( !lifo_buf->head)
		return LIFO_NULL;
	if(lifo_buf->count ==lifo_buf->length)
		return LIFO_full;
	*lifo_buf->head = item;
	lifo_buf->head++;
	lifo_buf->count++;
	return LIFO_no_error;
}
Buffer_status LIFO_get_item (LIFO_Buf_t* lifo_buf, unsigned int* item)
{
	if(!lifo_buf->head)
			return LIFO_NULL;
	if(lifo_buf->count ==0)
			return LIFO_empty;
	lifo_buf->head--;
	*item = *lifo_buf->head;
	lifo_buf->count--;
	return LIFO_no_error;
}
Buffer_status LIFO_init (LIFO_Buf_t* lifo_buf,unsigned int* buf, unsigned int length)
{
	if(!buf)
		return LIFO_NULL;
	lifo_buf-> head = buf;
	lifo_buf-> length = length;
	lifo_buf-> count =0;
	return LIFO_no_error;

}

