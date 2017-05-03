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

	
int main() {
	 // set port D to output

	DDRA = 0x00;
	DDRD = 0xff;
	motor_initB();
	servo_init();
	while (1) {
		//SERVO ANGLE POSITION//
		move_servo1(1);   //135 degree
		move_servo2(1);
		// STEPPER ANGLE MOVEMENT//
 		full_step_back(DEGREE*90);
// 		full_step_forward(DEGREE*90);
// 		//DC MOTOR ACTUATION//
// 		counterclockwiseB(0xff);
		
		
	}
	
}

