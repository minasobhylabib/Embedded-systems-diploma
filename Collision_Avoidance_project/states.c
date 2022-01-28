/*
 * states.c
 *
 *  Created on: Jan 27, 2022
 *      Author: Mina
 */
#include"states.h"
 int distance =0, speed, threshold = 50;
enum{
	waiting,
	driving
}state_id;

int generate_random(int min,int max)
{

		int rand_num = ((rand)()%(max-min+1))+min;
		return rand_num;


}


void(*state)();

STATE_define(waiting)
{
	state_id = waiting;
	speed = 0;
	printf("waiting state : distance=%d speed=%d \n", distance,speed);
	distance  = generate_random(45,55);
	(distance <= threshold) ? (state=STATE(waiting)) : (state=STATE(driving));

}

STATE_define(driving)
{
	state_id = driving;
	speed = 30;
	printf("driving state : distance=%d speed=%d \n", distance,speed);
	distance  = generate_random(45,55);
	(distance <= threshold) ? (state=STATE(waiting)) : (state=STATE(driving));

}
void setup()
{
	state = STATE(waiting);
}
