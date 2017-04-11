#include <asf.h>
#define F_CPU 8000000L                    // set the CPU clock
#include <avr/io.h>
#include <util/delay.h>

#define BAUD 9600                           // define baud
#define BAUD_PRESCALLER 51    // set baudrate value for UBRR
//#define BAUD_PRESCALLER		(((F_CPU / (8 * BAUD)) + 1)/2 - 1)

void USART_init(void);
unsigned char USART_receive(void);
void USART_send( unsigned char data);
void USART_putstring(char* StringPtr);

char String[]="TEST\n\r";

void USART_init(void){
	UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8);
	UBRR0L = (uint8_t)(BAUD_PRESCALLER);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	//UCSR0C = (3<<UCSZ00);
	UCSR0C = (3<<UCSZ00)|(1<<USBS0);
}

int main(void){
	board_init();
	USART_init();        //Call the USART initialization code
	
	while(1){        //Infinite loop
		//USART_send(USART_receive());
		USART_putstring(String);    //Pass the string to the USART_putstring function and sends it over the serial
		_delay_ms(10); 
	}
	
	return 0;
}



unsigned char USART_receive(void){
	
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
	
}

void USART_send( unsigned char data){
	
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
	
}

void USART_putstring(char* StringPtr){
	
	while(*StringPtr != 0x00){
		USART_send(*StringPtr);
	StringPtr++;}
	
}