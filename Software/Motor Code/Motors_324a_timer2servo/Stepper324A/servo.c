#include <avr/io.h>

#include "servo.h"
// Motor Control Functions -- pwm is an 8-bit value

void move_servo1(uint8_t angle)
{
	OCR2A = angle;
}

void move_servo2(uint8_t angle)
{
	
	OCR2B = angle;
	
}
// Motor Initialization routine -- this function must be called
//  before you use any of the above functions
void servo_init()
{
	
	//Configure TIMER2
	TCCR2A|=(1<<COM2A1)|(1<<COM2B1)|(1<<WGM21)|(1<<WGM20); //NON Inverted PWM
	TCCR2B|=(0<<WGM22)|(1<<CS22)|(0<<CS20); //PRESCALER=8 MODE 3(FAST PWM)
	

	// set PWM pins as digital outputs (the PWM signals will not
	// appear on the lines if they are digital inputs)
	DDRD |= (1 << DDD6)|(1<<DDD7);

}