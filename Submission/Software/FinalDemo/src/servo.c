#include <avr/io.h>

#include "servo.h"
// Motor Control Functions -- pwm is an 16-bit value

void move_servo1(uint16_t angle)
{
	//Map the degree angle to the compare match register
	OCR1A = (310 - 110) * angle / 150 + 110;	
}

void move_servo2(uint16_t angle)
{
	//Map the degree angle to the compare match register
	OCR1B = (310 - 110) * angle / 150 + 110;
	
}
// Motor Initialization routine -- this function must be called
//  before you use any of the above functions
void servo_init()
{
	
	//Configure TIMER1
	TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);//|(0<<CS12)|(1<<CS11)|(1<<CS10);        //NON Inverted PWM
	//TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); //PRESCALER=64 MODE 14(FAST PWM)
	//ICR1=312;  //fPWM=50Hz (Period = 20ms Standard).
	
	TCCR1B|=(1<<WGM13)|(1<<WGM12)|(0<<CS12)|(1<<CS11)|(1<<CS10); //PRESCALER=8 MODE 14(FAST PWM)
	ICR1=2499;  //fPWM=50Hz (Period = 20ms Standard).
	
	// set PWM pins as digital outputs (the PWM signals will not
	// appear on the lines if they are digital inputs)
	DDRD |= (1 << PORTD5)|(1<<PORTD4);

}
