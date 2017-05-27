#include <util/delay.h>
#include "stepper.h"
#include "servo.h"
#include "timer2.h"

uint32_t present;

void hold_stepper (void) {
	//Set PC5 high to hold the load
	PORTC = 0b00100000;
}

void relax_stepper (void) {
	//Set all pins of PORTC to low
	PORTC &= 0b0;
}

void full_step_forward (int num_step) {

	//For loop to repeat num_step times executing a step up
	for (int i = 0; i < num_step; ++i)
	{
		//Set PORTC pins successively to execute one step up
		//Delay after each change
		PORTC = 0b001001000;
		_delay_ms(DELAY);
		PORTC = 0b00000100;
		_delay_ms(DELAY);
		PORTC = 0b00001100;
		_delay_ms(DELAY);
		PORTC = 0b00001000;
		_delay_ms(DELAY);
		PORTC = 0b00011000;
		_delay_ms(DELAY);
		PORTC = 0b00010000;
		_delay_ms(DELAY);
		PORTC = 0b00110000;
		_delay_ms(DELAY);
		PORTC = 0b00100000;
		_delay_ms(DELAY);
		
	}
}
void full_step_back (int num_step) {
	//For loop to repeat num_step times executing a step down
	for (int i = 0; i < num_step; ++i)
	{
		//Set PORTC pins successively to execute one step down
		//Delay after each change
		PORTC = 0b00100100;
		_delay_ms(DELAY);
		PORTC = 0b00100000;
		_delay_ms(DELAY);
		PORTC = 0b00110000;
		_delay_ms(DELAY);
		PORTC = 0b00010000;
		_delay_ms(DELAY);
		PORTC = 0b00011000;
		_delay_ms(DELAY);
		PORTC = 0b00001000;
		_delay_ms(DELAY);
		PORTC = 0b00001100;
		_delay_ms(DELAY);
		PORTC = 0b00000100;
		_delay_ms(DELAY);
		
	}
}
