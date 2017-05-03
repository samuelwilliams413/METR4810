#include <avr/io.h>
#include "dcMotor.h"
// Motor Control Functions -- pwm is an 8-bit value
//  (i.e. ranges from 0 to 255)



void motorRfwd(uint16_t pwm)
{
	
	OCR0B = pwm;
	
	PORTD |=  (1<<PORTD2);
}

void motorLfwd(uint16_t pwm)
{

	OCR0A = pwm;
	PORTD |= (1<<PORTD3);
	
}

void motorRfbwd(uint16_t pwm)
{
	
	OCR0B = pwm;
	
	PORTD |=  (0<<PORTD2);
}

void motorLbwd(uint16_t pwm)
{

	OCR0A = pwm;
	PORTD |= (0<<PORTD3);
	
}

void motorR_stop(void){
	
	OCR0B = 0;
	PORTD &= (0<<PORTD2);
	
}

void motorL_stop(void){
	
	OCR0A = 0;
	PORTD &= (0<<PORTD3);
	
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