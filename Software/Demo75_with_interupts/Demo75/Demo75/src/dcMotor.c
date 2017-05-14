#include <avr/io.h>
#include "dcMotor.h"
// Motor Control Functions -- pwm is an 8-bit value
//  (i.e. ranges from 0 to 255)


static int PD2_sta = 0;
static int PD3_sta = 0;

static int PB3_sta = 0;
static int PB4_sta = 0;

void setPD(int _PD2_state, int _PD3_state){

	if (_PD2_state == 0){
		if (_PD3_state == 0) {
			PORTD = 0b0000;
		}
		else {
			PORTD = 0b1000;
		}
	}

	else {
		if (_PD3_state == 0) {
			PORTD = 0b0100;
		}
		else {
			PORTD = 0b1100;
		}
	}

}


void setPB(int _PB3_state, int _PB4_state){

	if (_PB3_state == 0){
		if (_PB4_state == 0) {
			PORTB = 0b0000;
		}
		else {
			PORTB = 0b10000;
		}
	}

	else {
		if (_PB4_state == 0) {
			PORTB = 0b01000;
		}
		else {
			PORTB = 0b11000;
		}
	}

}


void motorRfwd(uint16_t pwm)
{
	
	//OCR0B = 255-pwm;
	
	//PORTD |=  (1<<PORTD2);
	PB3_sta = 0;
	setPB(PB3_sta, PB4_sta);
	PD2_sta = 1;
	setPD(PD2_sta, PD3_sta);
}

void motorLfwd(uint16_t pwm)
{

	//OCR0A = 255-pwm;
	//PORTD |= (1<<PORTD3);
	PB4_sta = 0;
	setPB(PB3_sta, PB4_sta);
	PD3_sta = 1;
	setPD(PD2_sta, PD3_sta);
}

void motorRbwd(uint16_t pwm)
{
	
	//OCR0B = pwm;
	
	//PORTD &=  !(1<<PORTD2);
	PB3_sta = 1;
	setPB(PB3_sta, PB4_sta);
	PD2_sta = 0;
	setPD(PD2_sta, PD3_sta);
}

void motorLbwd(uint16_t pwm)
{

	//OCR0A = pwm;

	//PORTD &= !(1<<PORTD3);
	PB4_sta = 1;
	setPB(PB3_sta, PB4_sta);
	PD3_sta = 0;
	setPD(PD2_sta, PD3_sta);
	
}

void motorR_stop(void){
	
	//OCR0B = 0;
	//PORTD &= !(1<<PORTD2);
	PB3_sta = 0;
	setPB(PB3_sta, PB4_sta);
	PD2_sta = 0;
	setPD(PD2_sta, PD3_sta);
	
}

void motorL_stop(void){
	
	//OCR0A = 0;
	
	PB4_sta = 0;
	setPB(PB3_sta, PB4_sta);//PORTD &= !(1<<PORTD3);
	PD3_sta = 0;
	setPD(PD2_sta, PD3_sta);
	
}

// Motor Initialization routine -- this function must be called
//  before you use any of the above functions
void motor_init()
{
	// configure for inverted PWM output on motor control pins:
	//  set OCxx on compare match, clear on timer overflow
	//  Timer0 count up from 0 to 255
	//TCCR0A = 0b10100011;
	//00100011
	// use the system clock/8 (=2.5 MHz) as the timer clock
	//TCCR0B = 0b00001001;
// 	TCCR0A |= (1<WGM00) | (1<< WGM01) | (1<< COM0A0) | (1<<COM0B0);
// 	
// 	// use the system clock/8 (=2.5 MHz) as the timer clock
// 	TCCR0B |= (1<<CS01);


	// initialize all PWMs to 0% duty cycle (braking)
	//OCR0A =  0;
	//OCR0B  = 0;
	// set PWM pins as digital outputs (the PWM signals will not
	// appear on the lines if they are digital inputs)
	DDRB |= (1 << PORTB3) | (1 << PORTB4);
	DDRD |= (1 << PORTD2) | (1 << PORTD3);
	DDRB = 0b11111111;
	DDRD = 0b11111111;
}