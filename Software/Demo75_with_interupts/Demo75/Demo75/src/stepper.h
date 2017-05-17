#include "stdio.h"
#include "avr/io.h"
#include "servo.h"
#include "comms.h"
#include "timer2.h"
#include "util/delay.h"

#define DELAY 10
#define DEGREE (50/360.0)

volatile short currentPosition;
volatile short stepperDirection;
volatile uint64_t stepperQueue;

void stepper_init(void);
void move_stepper(void);
void forward_stepper(int);
void backward_stepper(int);
void step(void);
void stepBinary(void);