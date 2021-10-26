/*
 * timer.c
 *
 *  Created on: Oct 16, 2021
 *      Author: MSI-
 */

#include "main.h"
#include "input_reading.h"
#include "timer.h"
#include "led_display.h"

static uint32_t count = 0;
static uint32_t thescale = 0;
static int runOnce = 1;
static int blink_led_red = 0;
static int blink_led_yellow = 0;
static int blink_led_green = 0;

void calculateScale(TIM_HandleTypeDef * htim) {
	uint32_t reload = htim->Instance->ARR;
	uint32_t pre = htim->Instance->PSC;
	uint32_t final = 8000000/(reload*pre);
	thescale = final*50/100;
}

void blink_LED_RED() {
	blink_led_red = 1;
	blink_led_yellow = 0;
	blink_led_green = 0;
	HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, 1);
	HAL_GPIO_WritePin(RED_HOR_GPIO_Port, RED_HOR_Pin, 1);

	HAL_GPIO_WritePin(YELLOW_GPIO_Port, YELLOW_Pin, 0);
	HAL_GPIO_WritePin(YELLOW_HOR_GPIO_Port, YELLOW_HOR_Pin, 0);
	HAL_GPIO_WritePin(GREEN_GPIO_Port, GREEN_Pin, 0);
	HAL_GPIO_WritePin(GREEN_HOR_GPIO_Port, GREEN_HOR_Pin, 0);

}
void turn_off_blink_LED_RED() {
	HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, 0);
	HAL_GPIO_WritePin(RED_HOR_GPIO_Port, RED_HOR_Pin, 0);
	count = 0;
	blink_led_red = 0;
}

void blink_LED_YELLOW(){
	blink_led_red = 0;
	blink_led_yellow = 1;
	blink_led_green = 0;
	HAL_GPIO_WritePin(YELLOW_GPIO_Port, YELLOW_Pin, 1);
	HAL_GPIO_WritePin(YELLOW_HOR_GPIO_Port, YELLOW_HOR_Pin, 1);

	HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, 0);
	HAL_GPIO_WritePin(RED_HOR_GPIO_Port, RED_HOR_Pin, 0);
	HAL_GPIO_WritePin(GREEN_GPIO_Port, GREEN_Pin, 0);
	HAL_GPIO_WritePin(GREEN_HOR_GPIO_Port, GREEN_HOR_Pin, 0);
}

void turn_off_blink_LED_YELLOW() {
	HAL_GPIO_WritePin(YELLOW_GPIO_Port, YELLOW_Pin, 0);
	HAL_GPIO_WritePin(YELLOW_HOR_GPIO_Port, YELLOW_HOR_Pin, 0);
	count = 0;
	blink_led_yellow = 0;
}

void blink_LED_GREEN() {
	blink_led_red = 0;
	blink_led_yellow = 0;
	blink_led_green = 1;
	HAL_GPIO_WritePin(GREEN_GPIO_Port, GREEN_Pin, 1);
	HAL_GPIO_WritePin(GREEN_HOR_GPIO_Port, GREEN_HOR_Pin, 1);

	HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, 0);
	HAL_GPIO_WritePin(RED_HOR_GPIO_Port, RED_HOR_Pin, 0);
	HAL_GPIO_WritePin(YELLOW_GPIO_Port, YELLOW_Pin, 0);
	HAL_GPIO_WritePin(YELLOW_HOR_GPIO_Port, YELLOW_HOR_Pin, 0);
}

void turn_off_blink_LED_GREEN() {
	HAL_GPIO_WritePin(GREEN_GPIO_Port, GREEN_Pin, 0);
	HAL_GPIO_WritePin(GREEN_HOR_GPIO_Port, GREEN_HOR_Pin, 0);
	count = 0;
	blink_led_green = 0;
}

void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim )
{
	if( htim->Instance == TIM2 ) {

		if(runOnce == 1)
		{
			calculateScale(htim);
			runOnce = 0;
		}

		button_reading();
		button_reading_2();
		button_reading_3();

		if(blink_led_red == 1) {
			if(++count == thescale) {
				HAL_GPIO_TogglePin(RED_GPIO_Port, RED_Pin);
				HAL_GPIO_TogglePin(RED_HOR_GPIO_Port, RED_HOR_Pin);
				count = 0;
			}
		}

		if(blink_led_yellow == 1) {
			if(++count == thescale) {
				HAL_GPIO_TogglePin(YELLOW_GPIO_Port, YELLOW_Pin);
				HAL_GPIO_TogglePin(YELLOW_HOR_GPIO_Port, YELLOW_HOR_Pin);
				count = 0;
			}
		}

		if(blink_led_green == 1) {
			if(++count == thescale) {
				HAL_GPIO_TogglePin(GREEN_GPIO_Port, GREEN_Pin);
				HAL_GPIO_TogglePin(GREEN_HOR_GPIO_Port, GREEN_HOR_Pin);
				count = 0;
			}
		}

	}

}
