#include <avr/io.h>
#include "dcMotor.h"
// Motor Control Functions -- pwm is an 8-bit value
//  (i.e. ranges from 0 to 255)


//Global variable stores the status of PD2
static int PD2_sta = 0;

//Global variable stores the status of PD3
static int PD3_sta = 0;

//Global variable stores the status of PB3
static int PB3_sta = 0;

//Global variable stores the status of PB4
static int PB4_sta = 0;

void setPD(int _PD2_state, int _PD3_state){

	if (_PD2_state == 0){
		if (_PD3_state == 0) {
			//Case PD2 low and PD3 should be low
			PORTD = 0b0000;
		}
		else {
			//Case PD2 should be low and PD3 high
			PORTD = 0b1000;
		}
	}

	else {
		if (_PD3_state == 0) {
			//Case PD2 should be high and PD3 low
			PORTD = 0b0100;
		}
		else {
			//Case PD2 and PD3 should be high
			PORTD = 0b1100;
		}
	}

}


void setPB(int _PB3_state, int _PB4_state){

	if (_PB3_state == 0){
		if (_PB4_state == 0) {
			//Case PB3 low and PB4 should be low
			PORTB = 0b0000;
		}
		else {
			//Case PB3 should be low and PB4 high
			PORTB = 0b10000;
		}
	}

	else {
		if (_PB4_state == 0) {
			//Case PB3 should be high and PB4 low
			PORTB = 0b01000;
		}
		else {
			//Case PB3 and PB4 should be high
			PORTB = 0b11000;
		}
	}

}


void motorRfwd(uint16_t pwm)
{
	//Change status of PB3 to low
	PB3_sta = 0;
	setPB(PB3_sta, PB4_sta);
	//Change status of PD2 to high
	PD2_sta = 1;
	setPD(PD2_sta, PD3_sta);
}

void motorLfwd(uint16_t pwm)
{
	//Change status of PB4 to low
	PB4_sta = 0;
	setPB(PB3_sta, PB4_sta);
	//Change status of PD3 to high
	PD3_sta = 1;
	setPD(PD2_sta, PD3_sta);
}

void motorRbwd(uint16_t pwm)
{
	//Change status of PB3 to high
	PB3_sta = 1;
	setPB(PB3_sta, PB4_sta);
	//Change status of PD2 to low
	PD2_sta = 0;
	setPD(PD2_sta, PD3_sta);
}

void motorLbwd(uint16_t pwm)
{
	//Change status of PB4 to high
	PB4_sta = 1;
	setPB(PB3_sta, PB4_sta);
	//Change status of PD3 to low
	PD3_sta = 0;
	setPD(PD2_sta, PD3_sta);
	
}

void motorR_stop(void){
	//Change status of PB3 to low
	PB3_sta = 0;
	setPB(PB3_sta, PB4_sta);
	//Change status of PD2 to low
	PD2_sta = 0;
	setPD(PD2_sta, PD3_sta);
	
}

void motorL_stop(void){
	//Change status of PB4 to low
	PB4_sta = 0;
	setPB(PB3_sta, PB4_sta);
	//Change status of PD3 to low
	PD3_sta = 0;
	setPD(PD2_sta, PD3_sta);
	
}

// Motor Initialization routine -- this function must be called
//  before you use any of the above functions
void motor_init()
{
	// Set PB3, PB4, PD2, and PD3 digital outputs
	DDRB |= (1 << PORTB3) | (1 << PORTB4);
	DDRD |= (1 << PORTD2) | (1 << PORTD3);
	DDRB = 0b11111111;
	DDRD = 0b11111111;
}
