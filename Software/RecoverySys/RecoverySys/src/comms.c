#include <asf.h>
#define F_CPU 8000000L                    // set the CPU clock
#include <avr/io.h>
#include <util/delay.h>

#define BAUD 9600                           // define baud
#define BAUD_PRESCALLER 51    // set baudrate value for UBRR
#define _ASSERT_ENABLE_
#include "string.h"
#include "compiler.h"
#include "comms.h"
#include "stdio.h"

/**
 * \def BUFFER_SIZE
 * \brief The size of the UART buffer
 */
#define BUFFER_SIZE 100

volatile unsigned char value;  

#include "ring_buffer.h"

// buffers for use with the ring buffer (belong to the UART)
uint8_t out_buffer[BUFFER_SIZE];
uint8_t in_buffer[BUFFER_SIZE];


extern void uart_init(void)
{	
	
	UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8);
	UBRR0L = (uint8_t)(BAUD_PRESCALLER);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (3<<UCSZ00)|(1<<USBS0);

	// enable RX and TX and set interrupts on rx complete
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);

	// 8-bit, 1 stop bit, no parity, asynchronous UART
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00) | (0 << USBS0) |
			(0 << UPM01) | (0 << UPM00) | (0 << UMSEL01) |
			(0 << UMSEL00);

	sei();
}

/**
 * \brief Function for putting a char in the UART buffer
 *
 * \param data the data to add to the UART buffer and send
 *
 */
static inline void uart_putchar(uint8_t data)
{
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = data;
}

/**
 * \brief Function for getting a char from the UART receive buffer
 *
 * \retval Next data byte in receive buffer
 */
static inline uint8_t uart_getchar(void)
{
		unsigned char temp = value;
		value = '\0';
		return temp;
}


extern void send_confirmation_msg(uint8_t data)
{
	// the string we send and receive on UART
	char buffer [30];
	
	if (data == '\0') {
		sprintf (buffer, "Received: '\\0'(0)\n");
	} else {
		sprintf (buffer, "Received: %c(%d)\n", data, data);
	}
	send_str(buffer);
}

extern void send_str(char* StringPtr)
{
		while(*StringPtr != 0x00) {
			uart_putchar(*StringPtr);
			StringPtr++;
		}
		uart_putchar('\r');
}

extern uint8_t get_char(void)
{	
	uint8_t data = '\0';
	data = uart_getchar();
	return data;
}

ISR (USART0_RX_vect)
{
	/* Put data into buffer, sends the data */
	value = UDR0;
}