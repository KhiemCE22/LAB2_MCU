/*
 * Exercise.h
 *
 *  Created on: Sep 21, 2024
 *      Author: GIGABYTE
 */

#ifndef INC_EXERCISE_H_
#define INC_EXERCISE_H_

#include "main.h"
extern int index_led;

extern int hour, minute, second;

void init_exercise();
void run_exercise();

void run_DOT();
void update7SEG(int index);
void updateClockBuffer();
#endif /* INC_EXERCISE_H_ */
