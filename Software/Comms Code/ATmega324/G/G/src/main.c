#include <asf.h>
#define F_CPU 8000000L                    // set the CPU clock
#include <avr/io.h>
#include <util/delay.h>
#include <comms.h>

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
	
	while(1){        //Infinite loop
		send_confirmation_msg(get_char());
		//send_str(String);    //Pass the string to the USART_putstring function and sends it over the serial
		_delay_ms(10); 
	}
	
	return 0;
}
