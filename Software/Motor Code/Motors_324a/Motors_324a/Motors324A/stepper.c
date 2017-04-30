
#include <util/delay.h>
#include "stepper.h"




void full_step_forward (int num_step) {
	for (int i = 0; i < num_step; ++i)
	{
		
		PORTD = 0b00000001;
		_delay_ms(DELAY);
		PORTD = 0b00000011;
		_delay_ms(DELAY);
		PORTD = 0b00000010;
		_delay_ms(DELAY);
		PORTD = 0b00000110;
		_delay_ms(DELAY);
		PORTD = 0b00000100;
		_delay_ms(DELAY);
		PORTD = 0b00001100;
		_delay_ms(DELAY);
		PORTD = 0b00001000;
		_delay_ms(DELAY);
		PORTD = 0b00001001;
		_delay_ms(DELAY);
		
	}
}
void full_step_back (int num_step) {
	for (int i = 0; i < num_step; ++i)
	{
		
		PORTD = 0b00000000;
		_delay_ms(DELAY);
		PORTD = 0b00001000;
		_delay_ms(DELAY);
		PORTD = 0b00001100;
		_delay_ms(DELAY);
		PORTD = 0b00000100;
		_delay_ms(DELAY);
		PORTD = 0b00000110;
		_delay_ms(DELAY);
		PORTD = 0b00000010;
		_delay_ms(DELAY);
		PORTD = 0b00000011;
		_delay_ms(DELAY);
		PORTD = 0b00000001;
		_delay_ms(DELAY);
		
	}
}