/*
 * main.c
 *
 *  Created on: Jan 25, 2022
 *      Author: Mina
 */

# include "lifo.h"
# include "stdio.h"
# include "stdlib.h"


unsigned int buffer1 [5];

int main ()
{
	unsigned int i,temp,size;
	LIFO_Buf_t uart_lifo, I2C_lifo;
	LIFO_init (&uart_lifo, buffer1, 5);

	printf("Please enter I2C LIFO buffer size");
	fflush(stdout);fflush(stdin);
	scanf("%d",&size);
	unsigned int* buffer2 = (unsigned int*) malloc (size * sizeof(unsigned int) );
	LIFO_init(&I2C_lifo, buffer2, size);

	for ( i=0 ; i<7;i++)
	{
		if(LIFO_Add_item(&uart_lifo, i)== LIFO_no_error)
		{
			printf("UART_LIFO add : %d \n",i);
				fflush(stdout);
		}
		else
		{
			printf("UART_LIFO is full\n");
			fflush(stdout);
			break;
		}
	}


for ( i=0 ; i<7;i++)
{
	if(LIFO_get_item (&uart_lifo, &temp)== LIFO_no_error)
	{
		printf("UART_LIFO get : %d \n",temp);
		fflush(stdout);
	}
	else
	{
		printf("UART_LIFO is empty\n");
		break;
	}

}
for ( i=0 ; i<7;i++)
{
	if(LIFO_Add_item(&I2C_lifo, i)== LIFO_no_error)
	{
		printf("I2C_LIFO add : %d \n",i);
		fflush(stdout);
	}
	else
	{
		printf("I2C_LIFO is full\n");
		break;
	}
}
for ( i=0 ; i<7;i++)
{
	if(LIFO_get_item (&I2C_lifo, &temp)== LIFO_no_error)
		printf("I2C_LIFO get : %d \n",temp);
	else
	{
		printf("I2C_LIFO is empty\n");
		break;
	}
}
return 0;
}
