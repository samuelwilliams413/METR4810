#include <avr/io.h>
#include "dcMotor.h"


// Motor Control Functions -- pwm is an 8-bit value
//  (i.e. ranges from 0 to 255)


void motorR(uint16_t pwm, int n)
{
	
	OCR1B = pwm;
	
	PORTD |=  (n<<PORTD2);
}

void motorL(uint16_t pwm, int l)
{

	OCR1A = pwm;
	/*OCR0B = 0;*/
	PORTD |= (l<<PORTD3);
	}

void motorStop(void){
	OCR1B=0;
	OCR1A=0;

}

// Motor Initialization routine -- this function must be called
//  before you use any of the above functions
void motor_init()
{
	// configure for inverted PWM output on motor control pins:
	//  set OCxx on compare match, clear on timer overflow
	//  Timer0 count up from 0 to 255
	
	// fast PWM | 0x03FF | bottom | MAX
	// Non-inverting mode set OCxA/B on match
	// max 1023
	TCCR1A |= (1<<COM1A1)|(0<<COM1A0)|(1<<COM1B1)|(0<<COM1B0)|(1<<WGM11)|(1<<WGM10);//0b11110001;
	
	// use the system clock/8 (=2.5 MHz) as the timer clock
	TCCR1B |= (1<<WGM12)|(1<<CS11);//0b00001010;
	
	
	// set PWM pins as digital outputs (the PWM signals will not
	// appear on the lines if they are digital inputs)

	DDRD |= (1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5);
	
}