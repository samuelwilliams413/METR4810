#include <avr/io.h>
#include <avr/interrupt.h>
extern volatile short currentPosition;
extern volatile short stepperDirection;
extern volatile uint64_t stepperQueue;

#include "timer2.h"
#include "stepper.h"
#include "comms.h"
// Motor Control Functions -- pwm is an 8-bit value

static volatile uint32_t clock_ticks;
char buffer[50];

uint32_t get_clock_ticks(void){
	uint32_t return_value;

  /* Disable interrupts so we can be sure that the interrupt
   * doesn't fire when we've copied just a couple of bytes
   * of the value. Interrupts are re-enabled if they were
   * enabled at the start.
   */
  uint8_t interrupts_were_on = bit_is_set(SREG, SREG_I);
  cli();
  return_value = clock_ticks;
  if(interrupts_were_on) {
    sei();
  }
  return return_value;

}
void mil_delay(int milliseconds){
	int start_time;
	start_time = get_clock_ticks();
	while (get_clock_ticks()<= start_time + milliseconds)
	{
		;
	}
}
// Motor Initialization routine -- this function must be called
//  before you use any of the above functions
void timer_init()
{
	DDRA = 0xff;
	/* Reset clock tick count. L indicates a long (32 bit) 
	 * constant. 
	 */
	clock_ticks = 0L;
	
	/* Clear the timer */
	TCNT0 = 0;

	/* Set the output compare value to be 124 */
	OCR0A = 124;
	
	/* Set the timer to clear on compare match (CTC mode)
	 * and to divide the clock by 64. This starts the timer
	 * running.
	 */
	TCCR0A = (1<<WGM21);
	TCCR0B = (1<<CS21)|(1<<CS20);

	/* Enable an interrupt on output compare match. 
	 * Note that interrupts have to be enabled globally
	 * before the interrupts will fire.
	 */
	TIMSK0 |= (1<<OCIE2A);
	
	/* Make sure the interrupt flag is cleared by writing a 
	 * 1 to it.
	 */
	TIFR0 &= (1<<OCF2A);

}

ISR (TIMER0_COMPA_vect) {
	clock_ticks++;
	if (clock_ticks%100 == 0) { // Periodically step if needed
		if (stepperQueue > 0) {
			move_stepper();
		}
	}

	if (clock_ticks%500 == 0) { // Status LED
		PORTA ^= (1<<4);
	}
}