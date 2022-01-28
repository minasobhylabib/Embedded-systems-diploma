/*
 * states.h
 *
 *  Created on: Jan 27, 2022
 *      Author: Mina
 */

#ifndef STATES_H_
#define STATES_H_
#include "stdio.h"
#include "stdlib.h"
#define STATE_define(_stateFunc_) void ST_##_stateFunc_()
#define STATE(_stateFunc_) ST_##_stateFunc_

STATE_define(waiting);
STATE_define(driving);
void setup();
void US_distance_set(int d);
void DC_motor(int s);


#endif /* STATES_H_ */
