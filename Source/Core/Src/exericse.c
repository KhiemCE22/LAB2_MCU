/*
 * Exericse.c
 *
 *  Created on: Sep 21, 2024
 *      Author: GIGABYTE
 */

#include "exercise.h"

//# define LED0 0
//# define LED1 1
//# define LED2 2
//# define LED3 3


/////
const int MAX_LED = 4;
int index_led = 0;
int led_buffer[4] = {1,5,0,8};

int hour, minute, second;


/////
const int MAX_LED_MATRIX = 8;
int index_led_matrix = 0;
uint8_t matrix_buffer [8] = {0x18 , 0x3c , 0x66 , 0x7e , 0x7e , 0x66 , 0x66 , 0x66}; // dipslay character A

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

void init_clock(){
	hour = 15;
	minute = 8;
	second = 50;
}

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

void decodeLed(uint8_t _8bit_led_){
	/* Control 8x8 matrix led by ULN2803
	 * ULN 2803: array 8 not gate
	 * so active-low for ENM to control COLLUMN
	 * */
	uint16_t ENMX[8] = {ENM0_Pin, ENM1_Pin, ENM2_Pin, ENM3_Pin,
						ENM4_Pin, ENM5_Pin, ENM6_Pin, ENM7_Pin };
	for (int col = 0; col < 8; ++col){
		if ( (_8bit_led_) & (1 << (7 - col) ) ){
			// column th led is turn on
			HAL_GPIO_WritePin(GPIOA, ENMX[col], RESET);
		}
		else {
			HAL_GPIO_WritePin(GPIOA, ENMX[col], SET);
		}
	}
}


void updateLEDMatrix(int index){

	/* Turn specified led on a row
	 * col is controlled by ENM GPIO
	 */
	HAL_GPIO_WritePin(GPIOB, ROW0_Pin | ROW1_Pin | ROW2_Pin | ROW3_Pin
							|ROW4_Pin | ROW5_Pin | ROW6_Pin | ROW7_Pin	, SET);
    // Decode and set columns
    decodeLed(matrix_buffer[index]);
    // Circular shift left the previous row
    matrix_buffer[index - 1] = (matrix_buffer[index - 1] >> 7) | (matrix_buffer[index - 1] << 1);
    // Turn on the specific row
    switch (index) {
        case 0:
            HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, RESET);
            break;
        case 1:
            HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, RESET);
            break;
        case 2:
            HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, RESET);
            break;
        case 3:
            HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, RESET);
            break;
        case 4:
            HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, RESET);
            break;
        case 5:
            HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, RESET);
            break;
        case 6:
            HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, RESET);
            break;
        case 7:
            HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, RESET);
            break;
        default:
            break;
    }
}
void run_clock(){
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
