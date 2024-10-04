/*
 * software_timer.c
 *
 *  Created on: Sep 21, 2024
 *      Author: GIGABYTE
 */


#include "software_timer.h"

#define SIZE 4

int flag_timer[SIZE];
int timer_counter[SIZE];
int TIMER_CYCLE = 10;
void setTimer(int index, int duration){
	// T of tim2 : 10ms
	timer_counter[index] = duration / TIMER_CYCLE;
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
