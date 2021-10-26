/*
 * input_reading.c
 *
 *  Created on: Oct 16, 2021
 *      Author: MSI-
 */
# include "main.h"

// we aim to work with more than one buttons
# define N0_OF_BUTTONS 						1

// timer interrupt duration is 10ms , so to pass 1 second ,
// we need to jump to the interrupt service routine 100 time
# define DURATION_FOR_AUTO_INCREASING 		10
# define BUTTON_IS_PRESSED 					GPIO_PIN_RESET
# define BUTTON_IS_RELEASED 				GPIO_PIN_SET

// the buffer that the final result is stored after
// debouncing
static GPIO_PinState buttonBuffer[ N0_OF_BUTTONS ];
static GPIO_PinState buttonBuffer_2[ N0_OF_BUTTONS ];
static GPIO_PinState buttonBuffer_3[ N0_OF_BUTTONS ];

// we define two buffers for debouncing
static GPIO_PinState debounceButtonBuffer1[ N0_OF_BUTTONS ];
static GPIO_PinState debounceButtonBuffer2[ N0_OF_BUTTONS ];

static GPIO_PinState debounceButtonBuffer1_2[ N0_OF_BUTTONS ];
static GPIO_PinState debounceButtonBuffer2_2[ N0_OF_BUTTONS ];

static GPIO_PinState debounceButtonBuffer1_3[ N0_OF_BUTTONS ];
static GPIO_PinState debounceButtonBuffer2_3[ N0_OF_BUTTONS ];

// we define a flag for a button pressed more than 1 second .
static uint8_t flagForButtonPress1s[ N0_OF_BUTTONS ];
static uint8_t flagForButtonPress1s_2[ N0_OF_BUTTONS ];
static uint8_t flagForButtonPress1s_3[ N0_OF_BUTTONS ];

// we define counter for automatically increasing the value
// after the button is pressed more than 1 second .
static uint16_t counterForButtonPress1s[ N0_OF_BUTTONS ];
static uint16_t counterForButtonPress1s_2[ N0_OF_BUTTONS ];
static uint16_t counterForButtonPress1s_3[ N0_OF_BUTTONS ];

void button_reading(void) {

	for (char i = 0; i < N0_OF_BUTTONS; i ++) {

		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];

		debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port,BUTTON_1_Pin);

		if(debounceButtonBuffer1[i] == debounceButtonBuffer2[i])
			buttonBuffer[i] = debounceButtonBuffer1[i];

		if( buttonBuffer[i] == BUTTON_IS_PRESSED ) {
			// if a button is pressed , we start counting

			if( counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING ) {
				counterForButtonPress1s[i]++;
			}
			else {
				// the flag is turned on when 1 second has passed
				// since the button is pressed.
				flagForButtonPress1s[i] = 1;
				// todo
			}
		}
		else {
			counterForButtonPress1s[i] = 0;
			flagForButtonPress1s[i] = 0;
		}
	}
}

unsigned char is_button_pressed( uint8_t index ) {
	if( index >= N0_OF_BUTTONS ) return 0;
	return ( buttonBuffer[index] == BUTTON_IS_PRESSED ) ;
}

unsigned char is_button_pressed_1s( unsigned char index ) {
	if( index >= N0_OF_BUTTONS ) return 0xff ;
	return ( flagForButtonPress1s [index] == 1) ;
}


// BUTTON 2
void button_reading_2( void ) {
	for (char i = 0; i < N0_OF_BUTTONS; i ++) {

		debounceButtonBuffer2_2[i] = debounceButtonBuffer1_2[i];

		debounceButtonBuffer1_2[i] = HAL_GPIO_ReadPin(BUTTON_2_GPIO_Port,BUTTON_2_Pin);

		if(debounceButtonBuffer1_2[i] == debounceButtonBuffer2_2[i])
			buttonBuffer_2[i] = debounceButtonBuffer1_2[i];

		if( buttonBuffer_2[i] == BUTTON_IS_PRESSED ) {
			// if a button is pressed , we start counting

			if( counterForButtonPress1s_2[i] < DURATION_FOR_AUTO_INCREASING ) {
				counterForButtonPress1s_2[i]++;
			}
			else {
				// the flag is turned on when 1 second has passed
				// since the button is pressed.
				flagForButtonPress1s_2[i] = 1;
				// todo
			}
		}
		else {
			counterForButtonPress1s_2[i] = 0;
			flagForButtonPress1s_2[i] = 0;
		}
	}
}

unsigned char is_button_pressed_2( uint8_t index ) {
	if( index >= N0_OF_BUTTONS ) return 0;
	return ( buttonBuffer_2[index] == BUTTON_IS_PRESSED );
}

unsigned char is_button_pressed_1s_2( unsigned char index ) {
	if( index >= N0_OF_BUTTONS ) return 0xff;
	return ( flagForButtonPress1s_2[index] == 1) ;
}

// BUTTON 3
void button_reading_3( void ) {
	for (char i = 0; i < N0_OF_BUTTONS; i ++) {

		debounceButtonBuffer2_3[i] = debounceButtonBuffer1_3[i];

		debounceButtonBuffer1_3[i] = HAL_GPIO_ReadPin(BUTTON_3_GPIO_Port,BUTTON_3_Pin);

		if(debounceButtonBuffer1_3[i] == debounceButtonBuffer2_3[i])
			buttonBuffer_3[i] = debounceButtonBuffer1_3[i];

		if( buttonBuffer_3[i] == BUTTON_IS_PRESSED ) {
			// if a button is pressed , we start counting

			if( counterForButtonPress1s_3[i] < DURATION_FOR_AUTO_INCREASING ) {
				counterForButtonPress1s_3[i]++;
			}
			else {
				// the flag is turned on when 1 second has passed
				// since the button is pressed.
				flagForButtonPress1s_3[i] = 1;
				// todo
			}
		}
		else {
			counterForButtonPress1s_3[i] = 0;
			flagForButtonPress1s_3[i] = 0;
		}
	}
}

unsigned char is_button_pressed_3( uint8_t index ) {
	if( index >= N0_OF_BUTTONS ) return 0;
	return ( buttonBuffer_3[index] == BUTTON_IS_PRESSED ) ;
}

unsigned char is_button_pressed_1s_3( unsigned char index ) {
	if( index >= N0_OF_BUTTONS ) return 0xff ;
	return ( flagForButtonPress1s_3[index] == 1) ;
}
