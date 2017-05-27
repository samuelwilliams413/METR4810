#include <stdio.h>
#include <avr/io.h>

#define DELAY 10
#define DEGREE (50/360.0)

/*
Move the stepper num_step steps forwards
*/
void full_step_forward (int num_step);

/*
Move the stepper num_step steps backwards
*/
void full_step_back (int num_step);

/*
Stepper holds the load
*/
void hold_stepper (void);

/*
relax_stepper() relaxes the stepper
*/
void relax_stepper (void);
