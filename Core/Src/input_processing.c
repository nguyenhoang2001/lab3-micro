/*
 * input_processing.c
 *
 *  Created on: Oct 16, 2021
 *      Author: MSI-
 */

#include "main.h"
#include "input_reading.h"
#include "led_display.h"
#include "timer.h"

enum ButtonState { BUTTON_RELEASED , BUTTON_PRESSED ,BUTTON_PRESSED_MORE_THAN_1_SECOND } ;
enum ButtonState buttonState = BUTTON_RELEASED;

static int time1 = 0;

static int themode = -1;

static int time_red = 5;
static int time_yellow = 2;
static int time_green = 3;

void changeState1() {

	if(HAL_GPIO_ReadPin(RED_GPIO_Port, RED_Pin) == 1) {
		HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, 0);
		HAL_GPIO_WritePin(GREEN_GPIO_Port, GREEN_Pin, 1);
	}
	else if(HAL_GPIO_ReadPin(YELLOW_GPIO_Port, YELLOW_Pin) == 1) {
		HAL_GPIO_WritePin(YELLOW_GPIO_Port, YELLOW_Pin, 0);
		HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, 1);
	}
	else if(HAL_GPIO_ReadPin(GREEN_GPIO_Port, GREEN_Pin) == 1){
		HAL_GPIO_WritePin(GREEN_GPIO_Port, GREEN_Pin, 0);
		HAL_GPIO_WritePin(YELLOW_GPIO_Port, YELLOW_Pin, 1);
	}
}

void changeState2() {

	if(HAL_GPIO_ReadPin(RED_HOR_GPIO_Port, RED_HOR_Pin) == 1) {
		HAL_GPIO_WritePin(RED_HOR_GPIO_Port, RED_HOR_Pin, 0);
		HAL_GPIO_WritePin(GREEN_HOR_GPIO_Port, GREEN_HOR_Pin, 1);
	}
	else if(HAL_GPIO_ReadPin(YELLOW_HOR_GPIO_Port, YELLOW_HOR_Pin) == 1) {
		HAL_GPIO_WritePin(YELLOW_HOR_GPIO_Port, YELLOW_HOR_Pin, 0);
		HAL_GPIO_WritePin(RED_HOR_GPIO_Port, RED_HOR_Pin, 1);
	}
	else if(HAL_GPIO_ReadPin(GREEN_HOR_GPIO_Port, GREEN_HOR_Pin) == 1){
		HAL_GPIO_WritePin(GREEN_HOR_GPIO_Port, GREEN_HOR_Pin, 0);
		HAL_GPIO_WritePin(YELLOW_HOR_GPIO_Port, YELLOW_HOR_Pin, 1);
	}
}

void trafficlight(int timered, int timeyellow, int timegreen)
{
	HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, 1);
	HAL_GPIO_WritePin(GREEN_HOR_GPIO_Port, GREEN_HOR_Pin, 1);

	int time_first = timered;
	int time_sec = timegreen;

	while(time_sec != 0) {

		int count = 0;

		while(count < 8) {

			updateLED(time_first, time_sec);

			if(is_button_pressed(0))
			{
				themode++;
				blink_LED_RED();
				return;
			}
			count++;
		}
		time_sec--;
		time_first--;
	}
	changeState2();
	time_sec = timeyellow;

	while(time_sec != 0) {
		int count = 0;
		while(count < 8) {
			updateLED(time_first, time_sec);
			if(is_button_pressed(0))
			{
				themode++;
				blink_LED_RED();
				return;
			}
			count++;
		}
		time_sec--;
		time_first--;
	}

	changeState2();
	changeState1();

	time_first = timegreen;
	time_sec = timered;

	while(time_first != 0) {
		int count = 0;
		while(count < 8) {
			updateLED(time_first, time_sec);
			if(is_button_pressed(0))
			{
				themode++;
				blink_LED_RED();
				return;
			}
			count++;
		}
		time_sec--;
		time_first--;
	}

	changeState1();
	time_first = timeyellow;

	while(time_first != 0) {
		int count = 0;
		while(count < 8) {
			updateLED(time_first, time_sec);
			if(is_button_pressed(0))
			{
				themode++;
				blink_LED_RED();
				return;
			}
			count++;
		}
		time_sec--;
		time_first--;
	}

	HAL_GPIO_WritePin(YELLOW_GPIO_Port, YELLOW_Pin, 0);
	HAL_GPIO_WritePin(RED_HOR_GPIO_Port, RED_HOR_Pin, 0);

}
void fsm_for_input_processing(void) {

	switch ( buttonState ){

	case BUTTON_RELEASED:

		if(is_button_pressed(0)) {
			buttonState = BUTTON_PRESSED;
			// INCREASE VALUE OF PORT A BY ONE UNIT
			themode++;
			if(themode == 4)
				themode = 0;

			if(themode == 1) {
				blink_LED_RED();
			}
			else if(themode == 2) {
				turn_off_blink_LED_RED();
				blink_LED_YELLOW();
			}
			else if(themode == 3) {
				turn_off_blink_LED_YELLOW();
				blink_LED_GREEN();
			}
			else {
				turn_off_blink_LED_GREEN();
			}
		}
		if(themode == 0) {
			trafficlight(time_red, time_yellow, time_green);
		}
		else
			updateLED(time1, themode);
		break;
	case BUTTON_PRESSED:
		if (!is_button_pressed(0)) {
			buttonState = BUTTON_RELEASED;
		} else {
			if( is_button_pressed_1s(0)) {
				buttonState = BUTTON_PRESSED_MORE_THAN_1_SECOND ;
			}
		}
		break ;
	case BUTTON_PRESSED_MORE_THAN_1_SECOND :
		if (!is_button_pressed(0)) {
			buttonState = BUTTON_RELEASED ;
		}
		// todo
		break ;
	}
}
