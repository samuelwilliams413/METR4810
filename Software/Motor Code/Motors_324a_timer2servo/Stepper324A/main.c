/*
 * Stepper324A.c
 *
 * Created: 21/03/2017 6:06:26 PM
 * Author : s4371792
 */ 


#define F_CPU 1000000UL
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "stepper.h"
#include "dcMotor.h"
#include "servo.h"


	
int main() {
	 // set port D to output
	DDRC = 0xff;
	//DDRA = 0xff;
	//DDRD = 0xff;
	//DDRB=0xff;
	//DDRC |= (1<<DDC0)|(1<<DDC1)|(1<<DDC2)|(1<<DDC3);
	//DDRA = 0x00;
	//DDRD = 0b00000100;
	//motor_init();
	//ADCSRA |= _BV(ADEN);
	//init_timer2();
	servo_init();
	//DDRB |= (1<<DDB3);
	//uint16_t x_axis;
	while (1) {
		//PORTA = 0xff;
		//PORTB = 0xff;
		//PORTC = 0xff;
		//PORTD = 0xff;
		
		//motorR(100,0);
		//PORTC = 0b00000000;
		//SERVO ANGLE POSITION//
		for (int i =0;i<256;i++)
		{
			move_servo1(i);
			_delay_ms(100);
		}
		   //135 degree
		// STEPPER ANGLE MOVEMENT//
		//full_step_back(DEGREE*90);

// 		_delay_ms(1000);
// 		full_step_forward(DEGREE*90);
// 		_delay_ms(1000);
// 		PORTC = 0b00111100;
// 		_delay_ms(1000);
// 		PORTC = 0b00000000;
// 		_delay_ms(1000);

		//DC MOTOR ACTUATION//
		//PORTD |= (1<<PORTD3);
// 		x_axis = adc_read(1);
 		//_delay_ms(200);
// 		PORTA = 0x00;
// 		PORTB = 0x00;
// 		PORTC = 0x00;
// 		PORTD = 0x00;
		//_delay_ms(200);
// 		if (x_axis >= ADC_THRESHOLD+300){
// 		motorL(250,0);
// 		motorR(250,0);
// 		}else if(x_axis <= ADC_THRESHOLD-300){
// 		motorL(10,1);
// 		motorR(10,1);
// 		}else{
// 		motorStop();	
// 		}
		//motorL(250,0);
		//_delay_ms(1000);
		
//  		PORTB =(0<<PORTB3);
//  		_delay_ms(1000);
// 		PORTB = (1<<PORTB3);
// 		_delay_ms(1000);
// 		
	}
	
}

