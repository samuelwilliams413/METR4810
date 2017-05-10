
#define _ASSERT_ENABLE_
#include <string.h>
#include "compiler.h"
#include "comms.h"
#include "conf_clock.h"
#include "conf_uart.h"
#include <util/setbaud.h>
#include <avr/interrupt.h>
#include "ring_buffer.h"
int main(void)
{

	uint8_t data = 0;

	cli();
	uart_init();
	sei();
	send_str("HELLO WORLD");
	while(1) {
		data = get_char(); // THIS IS THE RECEIVED CHARACTER
		if (data != '\0') {
			send_confirmation_msg(data);
		}

	}

}