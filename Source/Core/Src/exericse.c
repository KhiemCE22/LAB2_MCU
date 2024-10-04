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

int index_buffer = 0;

int shift = 0;

/////
const int MAX_LED_MATRIX = 8;

int index_led_matrix = 0;
uint8_t matrix_buffer [8] = {0x00, 0xFC, 0xFE, 0x33,0x33, 0xFE, 0xFC, 0x00}; // dipslay character A

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
	uint16_t ROW[8] = {ROW0_Pin, ROW1_Pin, ROW2_Pin, ROW3_Pin,
						ROW4_Pin, ROW5_Pin, ROW6_Pin, ROW7_Pin };
	for (int i = 0; i < 8; ++i){
		if ( (_8bit_led_) & (1 << (i)) ){
			// row th led is turn on
			HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW[i], RESET);
		}
		else {
			HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW[i], SET);
		}
	}
}


void updateLEDMatrix(int index){

	/* Turn specified led on a row
	 * col is controlled by ENM GPIO
	 */
	HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin | ENM1_Pin | ENM2_Pin | ENM3_Pin
							|ENM4_Pin | ENM5_Pin | ENM6_Pin | ENM7_Pin	, SET);


    // Decode and set columns
	int index_led = (index - shift + 8) % 8;
    decodeLed(matrix_buffer[index_led]);

    // Turn on the specific row
    switch (index) {
        case 0:
            HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin, RESET);
            break;
        case 1:
        	HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, RESET);
            break;
        case 2:
        	HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, RESET);
            break;
        case 3:
        	HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, RESET);
            break;
        case 4:
        	HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, RESET);
            break;
        case 5:
        	HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, RESET);
            break;
        case 6:
        	HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, RESET);
            break;
        case 7:
        	HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, RESET);
            break;
        default:
            break;
    }
}
void shiftMatrix(){
	shift++;
	if (shift >= 8) shift = 0;

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
