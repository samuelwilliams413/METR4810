/*
 * main.c
 *
 *  Created on: Mar 21, 2017
 *      Author: mohamed
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "comms.h"
#include "servo.h"
#include "stepper.h"
#include "dcMotor.h"
#include "timer2.h"
#include <string.h>

#ifndef F_CPU					// if F_CPU was not defined in Project -> Properties
#define F_CPU 1000000UL			// define it now as 1 MHz unsigned long
#endif

static char carStatus[10];

static char buffer[50];
static int n;

void forwards(void);
void reverse(void);
void left(void);
void right(void);
void stop(void);

////////////////////////////////////////////////DC motors function

void forwards(void){
	 motorRfwd(0);
	 motorLfwd(0);
	 sprintf(carStatus, "Forward");
}

void reverse(void){
	motorRbwd(0);
	motorLbwd(0);
	sprintf(carStatus, "Reverse");
}

void left(void){
	motorRfwd(0);
	motorLbwd(0);
	sprintf(carStatus, "Left");
}
void right(void){
	motorRbwd(0);
	motorLfwd(0);
	sprintf(carStatus, "Right");
}

void stop(void){
	motorL_stop();
	motorR_stop();
	sprintf(carStatus, "Stopped");
}



///////////////////////////////////////// Main function

int main(void) {
	char roverState[50];
	sprintf(roverState, "Stopped");
	char stepperState[50];
	sprintf(stepperState, "Relaxed");
	//Initializations

	//Initialize timer2
	timer_init();
	
	//Initialize communication through bluetooth
	uart_init();
	
	//Initialize DC motors
	motor_init();
	stop();
	
	//Initialize servo
	int servo1Position = 0; //position of the upper claw in degree
	int servo2Position = 0; //position of the lower claw in degree
	servo_init();
	move_servo1(servo1Position);
	move_servo2(servo2Position);
	
	n = sprintf(buffer, "Ready! \n");
	send_str(buffer);

	
	
	
	//Stay forever inside this while loop
	while (1) {
		//get the control command
		char command = get_char();

		sprintf(stepperState, "Holding");
		switch (command) {
			
			case 'x':
			hold_stepper();
			sprintf(stepperState, "Holding");
			n = sprintf(buffer, "Winch holding\n");
			send_str(buffer);
			break;

			case 'z':
			relax_stepper();
			sprintf(stepperState, "Relaxed");
			n = sprintf(buffer, "Winch released\n");
			send_str(buffer);
			break;

			case 'q':
			full_step_forward(10);
			sprintf(stepperState, "Stepping forwards");
			n = sprintf(buffer, "Winch moved one step up\n");
			send_str(buffer);
			break;
			
			case 'a':
			full_step_back(10);
			sprintf(stepperState, "Stepping backwards");
			n = sprintf(buffer, "Winch moved one step down\n");
			send_str(buffer);
			break;

			case 'w':
			if (servo1Position < 150) {
				servo1Position += 5;
			}
			move_servo1(servo1Position);
			n = sprintf(buffer,"Servo 1 moved to position %d*\n",
			servo1Position);
			send_str(buffer);
			break;
			
			
			case 's':
			if (servo1Position > 0) {
				servo1Position -= 5;
			}
			move_servo1(servo1Position);
			n = sprintf(buffer,"Servo 1 moved to position %d*\n",
			servo1Position);
			send_str(buffer);
			break;
			
			
			case 'e':
			if (servo2Position < 150) {
				servo2Position += 5;
			}
			move_servo2(servo2Position);
			n = sprintf(buffer,"Servo 2 moved to position %d*\n",
			servo2Position);
			send_str(buffer);
			break;
			
			
			case 'd':
			if (servo2Position > 0) {
				servo2Position -= 5;
			}
			move_servo2(servo2Position);
			n = sprintf(buffer,"Servo 2 moved to position %d*\n",
			servo2Position);
			send_str(buffer);
			break;

			case 'i':
			forwards();
			sprintf(roverState, "moving");
			n = sprintf(buffer,"Car is moving forwards\n");
			send_str(buffer);
			break;

			case 'm':
			reverse();
			sprintf(roverState, "reversing");
			n = sprintf(buffer,"Car is moving backwards\n");
			send_str(buffer);
			break;

			case 'j':
			right();
			sprintf(roverState, "turning right");
			n = sprintf(buffer,"Car is moving to the right\n");
			send_str(buffer);
			break;

			case 'l':
			left();
			sprintf(roverState, "turning left");
			n = sprintf(buffer,"Car is moving to the left\n");
			send_str(buffer);
			break;

			case 'k':
			stop();
			sprintf(roverState, "Stopped");
			n = sprintf(buffer,"Car stopped\n");
			send_str(buffer);
			break;
	
		}

		n = sprintf(buffer, "SysSta:\tS1pos=%d, S2pos=%d\r\nRover:\t%s\r\nWinch:\t%s\n", servo1Position, servo2Position, roverState, stepperState);
		send_str(buffer);

		n = sprintf(buffer,"\n");
		send_str(buffer);

	}
	return (0);	// should never get here, this is to prevent a compiler warning
}


