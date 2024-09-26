/*
 * Exericse.c
 *
 *  Created on: Sep 21, 2024
 *      Author: GIGABYTE
 */

#include "exercise.h"

# define LED0 0
# define LED1 1
# define LED2 2
# define LED3 3



const int MAX_LED = 4;
int index_led = 0;
int led_buffer[4] = {1,5,0,8};

int hour, minute, second;

void display7SEG(int num){
	//use  BCD decoder
	int A,B,C,D;
	A = (num >> 3) & 1; //MSB
	B = (num >> 2) & 1;
	C = (num >> 1) & 1;
	D = (num >> 0) & 1; // LSB

	int a,b,c,d,e,f,g;

	a =  C || A || (!B && !D) || (B && D);
	b = !B || (C && D) || (!C && !D);
	c = !C || B || D;
	d =  A || (!B && !D) || (!B && C) || (C && !D) || (B && !C && D);
	e = (!B && !D) || (C && !D);
	f =  A || (B && !D) || (!C && !D) || (B && !C);
	g =  A || (!B && C) || (B && !D) || (B && !C);

	HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, !a);
	HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, !b);
	HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, !c);
	HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, !d);
	HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, !e);
	HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, !f);
	HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, !g);

}

void init_exercise(){
	hour = 15;
	minute = 8;
	second = 50;
}
//
//void run_LED_SEG(){
//	HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
//	switch (status_led) {
//		case LED0 :
//			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
//			status_led = LED1;
//			display7SEG(1);
//			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, RESET);
//			break;
//		case LED1 :
//			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
//			status_led = LED2;
//			display7SEG(2);
//			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, RESET);
//			break;
//		case LED2 :
//			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
//			status_led = LED3;
//			display7SEG(3);
//			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, RESET);
//			break;
//		case LED3 :
//			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
//			status_led = LED0;
//			display7SEG(0);
//			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, RESET);
//			break;
//		default:
//			break;
//	}
//}
void run_DOT(){
	HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
}


//////////
void clear7SEG(){
	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin << 0, SET);
	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin << 1, SET);
	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin << 2, SET);
	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin << 3, SET);
}
void update7SEG(int index){
	switch (index) {
		case 0:
			clear7SEG();
			display7SEG(led_buffer[index]);
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, RESET);
			// Display the first 7 SEG with led_buffer [0]
			break;
		case 1:
			// Display the first 7 SEG with led_buffer [1]
			clear7SEG();
			display7SEG(led_buffer[index]);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, RESET);
			break;
		case 2:
			clear7SEG();
			display7SEG(led_buffer[index]);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, RESET);
			// Display the first 7 SEG with led_buffer [2]
			break;
		case 3:
			clear7SEG();
			display7SEG(led_buffer[index]);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, RESET);
			// Display the first 7 SEG with led_buffer [3]
			break;
		default:
			break;
	}
}

void updateClockBuffer(){
	if ( (0 <= hour) && (hour <= 9) ){
		led_buffer[0] = 0;
		led_buffer[1] = hour;
	}
	else {
		led_buffer[0] = hour / 10;
		led_buffer[1] = hour % 10;
	}
	if ((0 <= minute) && (minute <= 9)){
		led_buffer[2] = 0;
		led_buffer[3] = minute;
	}
	else {
		led_buffer[2] = minute / 10;
		led_buffer[3] = minute % 10;
	}

}

void run_exercise(){
	second ++;
	if (second >= 60){
		second = 0;
		minute ++;
	}
	if (minute >= 60){
		minute = 0;
		hour ++;
	}
	if (hour >= 24){
		hour = 0;
	}
	updateClockBuffer();
}
