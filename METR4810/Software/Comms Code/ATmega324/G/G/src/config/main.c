/*
 * Stepper324A.c
 *
 * Created: 21/03/2017 6:06:26 PM
 * Author : s4371792
 */ 



#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "stepper.h"
#include "dcMotor.h"
#include "servo.h"
#include "timer2b.h"
#include "comms.h"

// #ifndef F_CPU
// #define F_CPU 1000000UL
// #endif
	
int main() {
	 // set port D to output

	DDRA = 0x00;
	DDRD = 0xff;
	DDRB = 0xff;
	motor_initB();
	servo_init();
	timer_init();
	uint16_t present = 0;
	int character = 47;//get_char();
	while (1) {
		//SERVO ANGLE POSITION//
		
		//move_servo1(125);   //135 degree
		//move_servo2(125);
		// STEPPER ANGLE MOVEMENT//
 		full_step_back(DEGREE*90);
		 //character = get_char();
		 send_confirmation_msg(character);
//  		 present = get_clock_ticks();
//  		 while (get_clock_ticks()-1000<=present)
//  		 {
//  			move_servo1(125);   //135 degree
//  			move_servo2(125);
//  		 }
//  		 present = get_clock_ticks();
//  		 while (get_clock_ticks()-1000<=present)
//  		 {
//  			 move_servo1(240);   //135 degree
//  			 move_servo2(240);
//  		 }
 		//full_step_forward(DEGREE*90);
// 		//DC MOTOR ACTUATION//
	  	//motorL(0xff,0);
 		//motorR(0xff,0);
		// move_servo1(0);   //135 degree
		 //move_servo2(0);
		//PORTD |= (1<<PORTD3)|(1<<PORTD2);
		//PORTB |= (1<<PORTB3)|(1<<PORTD4);
	}
	
}

