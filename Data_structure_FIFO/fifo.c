/*
 * lifo.c
 *
 *  Created on: Jan 25, 2022
 *      Author: Mina
 */
# include "fifo.h"

Buffer_status FIFO_init (FIFO_Buf_t* fifo_buf,type* buf, unsigned int number_elements)
{

	fifo_buf->base = buf;
	fifo_buf->head = buf;
	fifo_buf->tail = buf;
	fifo_buf->length= number_elements;
	fifo_buf->count = 0;
	return FIFO_no_error;

}
Buffer_status FIFO_enqueue (FIFO_Buf_t* fifo_buf,type* buf, type* item)
{
	if(!buf||!fifo_buf->base||!fifo_buf->head||!fifo_buf->tail)
		return FIFO_NULL;
	if(FIFO_IS_FULL(fifo_buf, buf)==FIFO_full)
		return FIFO_full;
	*fifo_buf->head = *item;
	fifo_buf->count++;
	if(fifo_buf->head == fifo_buf->base + fifo_buf->length *sizeof(type))
		fifo_buf->head = fifo_buf->base;
	else
		fifo_buf->head++;
	return FIFO_no_error;

}

Buffer_status FIFO_IS_FULL (FIFO_Buf_t* fifo_buf,type* buf)
{
	if(!buf||!fifo_buf->base||!fifo_buf->head||!fifo_buf->tail)
		return FIFO_NULL;
	if(fifo_buf->count==fifo_buf->length)
		return FIFO_full;
	return FIFO_no_error;

}
Buffer_status FIFO_dequeue (FIFO_Buf_t* fifo_buf,type* buf,type* item)
{
	if(!buf||!fifo_buf->base||!fifo_buf->head||!fifo_buf->tail)
		return FIFO_NULL;
	if(fifo_buf->count==0)
		return FIFO_empty;
	*item = *fifo_buf->tail;
	fifo_buf->count--;
	if(fifo_buf->tail == fifo_buf->base + fifo_buf->length *sizeof(type))
		fifo_buf->tail = fifo_buf->base;
	else
		fifo_buf->tail++;
	return FIFO_no_error;

}
void FIFO_PRINT(FIFO_Buf_t* fifo_buf)
{
	int i;
	type* temp;
	if(fifo_buf->count==0)
	{
		printf ("Fifo is empty\n");
	}
	else
	{
		temp = fifo_buf->tail;
		printf ("=====Fifo======\n");
		for(i=0;i<fifo_buf->count;i++)
			printf("\t %x \n",*temp++);
		printf ("===============\n");
	}
}
