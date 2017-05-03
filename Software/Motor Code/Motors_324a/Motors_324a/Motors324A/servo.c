#include <avr/io.h>

#include "servo.h"
// Motor Control Functions -- pwm is an 16-bit value

void move_servo1(uint16_t angle)
{
	OCR1A = (2500/180)*angle;
	
	
}

void move_servo2(uint16_t angle)
{
	
	OCR1B = (2500/180)*angle;;
	
}

// Motor Initialization routine -- this function must be called
//  before you use any of the above functions
void servo_init()
{
	
	//Configure TIMER1
	TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);        //NON Inverted PWM
	TCCR1B|=(1<<WGM13)|(1<<WGM12)|(0<<CS11)|(1<<CS10); //PRESCALER=64 MODE 14(FAST PWM)
	ICR1=19999;  //fPWM=50Hz (Period = 20ms Standard).

	// set PWM pins as digital outputs (the PWM signals will not
	// appear on the lines if they are digital inputs)
	DDRD |= (1 << PORTD5)|(1<<PORTD4);

}