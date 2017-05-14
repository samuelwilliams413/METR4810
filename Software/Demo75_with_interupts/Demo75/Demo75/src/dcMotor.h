#include <avr/io.h>

void setPD(int _PD2_state, int _PD3_state);
void setPB(int _PB3_state, int _PB4_state);

void motorRfwd(uint16_t pwm);
void motorLfwd(uint16_t pwm);
void motorRbwd(uint16_t pwm);
void motorLbwd(uint16_t pwm);

void motorL_stop(void);
void motorR_stop(void);
void motor_init(void);