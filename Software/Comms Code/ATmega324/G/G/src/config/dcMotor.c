#include <avr/io.h>
#include "dcMotor.h"
// Motor Control Functions -- pwm is an 8-bit value
//  (i.e. ranges from 0 to 255)



void motorR(uint16_t pwm, int n)
{
	
	OCR0B = pwm;
	
	PORTD |=  ((1^n)<<PORTD2);
}

void motorL(uint16_t pwm, int l)
{

	OCR0A = pwm;
	
	PORTD |= ((1^l)<<PORTD3);
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
	DDRB |= (1 << DDRB3) | (1 << DDRB4);
	DDRD |= (1<<DDRD2) | (1<<DDRD3);
}