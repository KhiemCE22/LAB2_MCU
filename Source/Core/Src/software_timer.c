/*
 * software_timer.c
 *
 *  Created on: Sep 21, 2024
 *      Author: GIGABYTE
 */


#include "software_timer.h"


int flag_timer[SIZE];
int timer_counter[SIZE];
void setTimer(int index, int duration){
	// T of tim2 : 10ms
	timer_counter[index] = duration;
	flag_timer[index] = 0;
}

void runTimer(int index	){
	if (timer_counter[index] > 0){
		timer_counter[index] --;
		if (timer_counter[index] <= 0){
			flag_timer[index] = 1;
		}
	}
}
