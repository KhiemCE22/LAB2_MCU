/*
 * software_timer.c
 *
 *  Created on: Sep 21, 2024
 *      Author: GIGABYTE
 */


#include "software_timer.h"

int flag_timer;
int timer_counter;
void setTimer(int duration){
	timer_counter = duration;
	flag_timer = 0;
}

void runTimer(){
	if (timer_counter > 0){
		timer_counter --;
		if (timer_counter <= 0){
			flag_timer = 1;
		}
	}
}
