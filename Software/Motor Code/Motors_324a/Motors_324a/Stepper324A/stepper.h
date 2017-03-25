#include <stdio.h>
#include <avr/io.h>

#define DELAY 2
#define DEGREE (523/360.0)

void full_step_forward (int num_step);

void full_step_back (int num_step);