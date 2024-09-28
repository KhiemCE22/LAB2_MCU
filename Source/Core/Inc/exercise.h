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
extern int index_led_matrix;

void init_clock();
void run_clock();

void run_DOT();
void update7SEG(int index);
void updateClockBuffer();
void updateLEDMatrix(int index);
#endif /* INC_EXERCISE_H_ */
