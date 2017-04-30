#include <avr/io.h>
#include "dcMotor.h"
// Motor Control Functions -- pwm is an 8-bit value
//  (i.e. ranges from 0 to 255)

void clockwiseB(uint16_t pwm)
{
	OCR0A = 0;
	OCR0B = pwm;
}

void counterclockwiseB(uint16_t pwm)
{
	OCR0A = pwm;
	OCR0B = 0;
	
}



// Motor Initialization routine -- this function must be called
//  before you use any of the above functions
void motor_initB()
{
	// configure for inverted PWM output on motor control pins:
	//  set OCxx on compare match, clear on timer overflow
	//  Timer0 count up from 0 to 255
	TCCR0A = 0b11110001;
	
	// use the system clock/8 (=2.5 MHz) as the timer clock
	TCCR0B = 0b00001010;
	
	// initialize all PWMs to 0% duty cycle (braking)
	OCR0A =  0;
	OCR0B  = 0;
	// set PWM pins as digital outputs (the PWM signals will not
	// appear on the lines if they are digital inputs)
	DDRB |= (1 << PORTB3) | (1 << PORTB4);

}