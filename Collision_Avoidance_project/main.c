/*
 * main.c
 *
 *  Created on: Jan 27, 2022
 *      Author: Mina
 */

#include "states.h"
extern void (*state)();
int main()
{
	volatile int d;
	setup();
	while(1)
	{
		state();
		//delay
		for(d=0;d<100000;d++);
	}
	return 0;
}
