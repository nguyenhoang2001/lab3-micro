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
static int themode = 0;

void fsm_for_input_processing(void) {

	switch ( buttonState ){
	case BUTTON_RELEASED:

		if( is_button_pressed(0)) {
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
		updateLED(time1, themode);
		break ;
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
