#include <util/delay.h>
#include "stepper.h"
#include "servo.h"
#include "timer2.h"

uint32_t present;

void full_step_forward (int num_step) {
	for (int i = 0; i < num_step; ++i)
	{
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
				PORTC = 0b001001000;
		 		_delay_ms(DELAY);
		
	}
}
void full_step_back (int num_step) {
	for (int i = 0; i < num_step; ++i)
	{
		
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