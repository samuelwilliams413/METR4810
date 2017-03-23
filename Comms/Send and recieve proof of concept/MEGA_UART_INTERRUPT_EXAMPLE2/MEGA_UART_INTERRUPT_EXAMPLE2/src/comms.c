/********************************************************************************* @file    comms.c* @author  SamuelWilliams – 43219667* @date    23032017* @brief   Comms driver*******************************************************************************//* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "compiler.h"
#include "comms.h"
#include "uart_atmel.h"
#include "ring_buffer.h"

/* Private define ------------------------------------------------------------*/
#define _ASSERT_ENABLE_		// _ASSERT_ENABLE_ is used for enabling assert, typical for debug purposes
#define BUFFER_SIZE 100

/* Private variables ---------------------------------------------------------*/
char test_string[] = "r[";
char test_string2[] = "]\n";

//! ring buffer to use for the UART transmission
struct ring_buffer ring_buffer_out;
//! ring buffer to use for the UART reception
struct ring_buffer ring_buffer_in;

// buffers for use with the ring buffer (belong to the UART)
uint8_t out_buffer[BUFFER_SIZE];
uint8_t in_buffer[BUFFER_SIZE];


/**
 * \brief Transmit character received confirmation (for debugging purposes)
 *
 * \param character (ASCII) to be transmitted
 */
extern void send_confirmation_msg(uint8_t data)
{
	uint8_t cnt = 0;
	for (cnt = 0; cnt < strlen(test_string); cnt++) {
		while(!ring_buffer_is_empty(&ring_buffer_out)) {
			;
		}
		uart_putchar(test_string[cnt]);
	}
	while(!ring_buffer_is_empty(&ring_buffer_out)) {
		;
	}
	uart_putchar(data);
	for (cnt = 0; cnt < strlen(test_string2); cnt++) {
		while(!ring_buffer_is_empty(&ring_buffer_out)) {
			;
		}
		uart_putchar(test_string2[cnt]);
	}
}

/**
 * \brief Send string via serial
 *
 * \param String to be sent via serial
 */
extern void send_str(char msg[])
{
	uint8_t cnt = 0;
	for (cnt = 0; cnt < strlen(msg); cnt++) {
		while(!ring_buffer_is_empty(&ring_buffer_out)) {
			;
		}
		uart_putchar(msg[cnt]);
	}
	while(!ring_buffer_is_empty(&ring_buffer_out)) {
		;
	}
	uart_putchar('\r');
}

/**
 * \brief Returns the first character in the received buffer, or the null terminator
 *
 * \retval First character (ASCII) in received buffer 
 */
extern uint8_t get_char(void)
{	
	uint8_t data = '\0';
	if (uart_char_waiting()) {
		data = uart_getchar(); // THIS IS THE RECEIVED CHARACTER
	}
	return data;
}
