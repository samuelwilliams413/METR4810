#include <avr/io.h>

void motorRfwd(uint16_t pwm);
void motorLfwd(uint16_t pwm);
void motorRbwd(uint16_t pwm);
void motorLbwd(uint16_t pwm);

void motorL_stop(void);
void motorR_stop(void);
void motor_initB(void);