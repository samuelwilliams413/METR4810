#include <avr/io.h>


void motorR(uint16_t pwm, int n);
void motorL(uint16_t pwm,int l);
void motorStop(void);
void motor_init();