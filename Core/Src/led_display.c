/*
 * led_display.c
 *
 *  Created on: Oct 16, 2021
 *      Author: MSI-
 */


#include "main.h"
#include "led_display.h"

#define NUMBER_OF_DECIMAL_DIGITS	10

static uint8_t sevenSegmentLEDConversion[NUMBER_OF_DECIMAL_DIGITS] = {0x01, 0x4f, 0x12, 0x06, 0x4C, 0x24, 0x20, 0x0f, 0x00, 0x04};
const int MAX_LED = 4;

void displayled(int num) {
	uint8_t the_number = sevenSegmentLEDConversion[num];
	HAL_GPIO_WritePin(LED1_G_GPIO_Port, LED1_G_Pin, the_number & 0x01);
	HAL_GPIO_WritePin(LED1_F_GPIO_Port, LED1_F_Pin, the_number & 0x02);
	HAL_GPIO_WritePin(LED1_E_GPIO_Port, LED1_E_Pin, the_number & 0x04);
	HAL_GPIO_WritePin(LED1_D_GPIO_Port, LED1_D_Pin, the_number & 0x08);
	HAL_GPIO_WritePin(LED1_C_GPIO_Port, LED1_C_Pin, the_number & 0x10);
	HAL_GPIO_WritePin(LED1_B_GPIO_Port, LED1_B_Pin, the_number & 0x20);
	HAL_GPIO_WritePin(LED1_A_GPIO_Port, LED1_A_Pin, the_number & 0x40);
}

void setupled(int index) {
	if(index == 0) {
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
	}
	else if(index == 1) {
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
	}
	else if(index == 2) {
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 0);
	}
	else {
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 0);
	}
}

void update7SEG ( int index, int num ) {
	 switch (index) {
	 case 0:
		 // Display the first 7 SEG with led_buffer [0]
		 setupled(0);
		 displayled(num);
		 break;
	 case 1:
		 // Display the second 7 SEG with led_buffer [1]
		 setupled(1);
		 displayled(num);
		 break;
	 case 2:
		 // Display the third 7 SEG with led_buffer [2]
		 setupled(2);
		 displayled(num);
		 break;
	 case 3:
		 // Display the forth 7 SEG with led_buffer [3]
		 setupled(3);
		 displayled(num);
		 break;
	 default :
		 break;
	 }
}

void updateLED(int time1, int time2) {
	update7SEG(0, time1/10);
	HAL_Delay(70);
	update7SEG(1, time1 % 10);
	HAL_Delay(70);
	update7SEG(2, time2 / 10);
	HAL_Delay(70);
	update7SEG(3, time2 % 10);
	HAL_Delay(70);
}

void trafficlight(int time1_red, int time1_yellow, int time1_green, int time2_red, int tim2_yellow, int time2_green) {













}
