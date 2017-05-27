#include <avr/io.h>

/*
motor_init() initiate DC motors control
motor_init() has to be called before calling any one of the functions below
*/
void motor_init(void);

/*
setPD() set the pin PD2 and PD3 to respectively _PD2_state and _PD3_state
*/
void setPD(int _PD2_state, int _PD3_state);

/*
setPB() set the pin PB3 and PD4 to respectively _PB3_state and _PB4_state
*/
void setPB(int _PB3_state, int _PB4_state);

/*
Move the right motors forwards
*/
void motorRfwd(uint16_t pwm);

/*
Move the left motors forwards
*/
void motorLfwd(uint16_t pwm);

/*
Move the right motors backwards
*/
void motorRbwd(uint16_t pwm);

/*
Move the right motor backwards
*/
void motorLbwd(uint16_t pwm);

/*
Stop the right motor
*/

void motorL_stop(void);

/*
Stop the left motor
*/
void motorR_stop(void);


