/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>

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
	
int main(void) {
	 // set port D to output
	board_init();
	motor_initB();
	servo_init();
	timer_init();
	uart_init();
	uint16_t present = 0;
	int character = 47;//get_char();
	send_confirmation_msg(48); // 0
	while (1) {
		
		//SERVO ANGLE POSITION//
		motorLfwd(0xff);
		
		//move_servo1(125);   //135 degree
		//move_servo2(125);
		// STEPPER ANGLE MOVEMENT//
		send_confirmation_msg(49); // 1
 		full_step_back(DEGREE*10);
		 motorL_stop();
		 motorR_stop();
		 send_confirmation_msg(50); // 2
		 send_confirmation_msg(get_char());
		 motorRfwd(0xff);
		 send_confirmation_msg(51); // 3
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
	  	
 		
		// move_servo1(0);   //135 degree
		 //move_servo2(0);
		//PORTD |= (1<<PORTD3)|(1<<PORTD2);
		//PORTB |= (1<<PORTB3)|(1<<PORTD4);
	}
	
}

