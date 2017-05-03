#include <asf.h>
#define F_CPU 8000000L                    // set the CPU clock
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <comms.h>
#include "stepper.h"
#include "dcMotor.h"
#include "servo.h"
#include "timer2b.h"


#define BAUD 9600                           // define baud
#define BAUD_PRESCALLER 51    // set baudrate value for UBRR

void USART_init(void);
unsigned char USART_receive(void);
void USART_send( unsigned char data);
void USART_putstring(char* StringPtr);

char String[]="Woo\n\r";

int main(void){
	board_init();
	uart_init();        //Call the USART initialization code
	DDRA = 0x00;
	DDRD = 0xff;
	DDRB = 0xff;
	motor_initB();
	servo_init();
	timer_init();
	int character;
	
	while(1){        //Infinite loop
		character = get_char();
		send_confirmation_msg(character);
		full_step_back(DEGREE*90);
		//send_str(String);    //Pass the string to the USART_putstring function and sends it over the serial
		_delay_ms(10); 
	}
	
	return 0;
}
