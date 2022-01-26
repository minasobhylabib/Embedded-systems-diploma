/*
 * main.c
 *
 *  Created on: Jan 25, 2022
 *      Author: Mina
 */

# include "fifo.h"
# include "stdio.h"
# include "stdlib.h"
# define number_elements 5

type buf [number_elements];




int main ()
{

	FIFO_Buf_t FIFO_UART;
	type i,temp;
	if(FIFO_init(&FIFO_UART, buf, number_elements)==FIFO_no_error)
	{
		printf("\t fifo init .....Done\n");
		fflush(stdout);
	}

	for(i=0; i<7;i++)
	{
		printf("FIFO ENQUEUE (%X)\n",i);
		fflush(stdout);
		if(FIFO_enqueue (&FIFO_UART, buf,&i)==FIFO_no_error)
		{
			printf("\t FIFO ENQUEUE .....Done\n");
			fflush(stdout);
		}
		else
		{
			printf("\t FIFO ENQUEUE .....failed\n");
			fflush(stdout);
		}
	}
	FIFO_PRINT(&FIFO_UART);
	if(FIFO_dequeue(&FIFO_UART, buf, &temp)==FIFO_no_error)
	{
		printf("\t FIFO DEQUEUE (%x) .....Done\n",temp);
		fflush(stdout);
	}
	if(FIFO_dequeue(&FIFO_UART, buf, &temp)==FIFO_no_error)
	{
		printf("\t FIFO DEQUEUE (%x) .....Done\n",temp);
		fflush(stdout);
	}
	FIFO_PRINT(&FIFO_UART);
	return 0;
}
