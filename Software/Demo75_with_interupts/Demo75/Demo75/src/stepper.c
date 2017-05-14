#include "stepper.h"

extern volatile short currentPosition;
extern volatile short stepperDirection;
extern volatile uint64_t stepperQueue;


void stepper_init(void){
	DDRC |= (1 << 5) | (1 << 4) | (1 << 3) | (1 << 2);
	currentPosition = 0;
	stepperDirection = 0;
	stepperQueue = 0;
}

void move_stepper(void) {
	if(stepperDirection) {
		currentPosition = (currentPosition + 1) % 4;
	} else {
		currentPosition = (currentPosition - 1) % 4;
		if(currentPosition == -1){
			currentPosition = 3;
		}
	}
	stepperQueue = (stepperQueue >> 1);

	step();
}

void forward_stepper(int n) {
	int i = 0;
	if (stepperDirection == 0) {
		stepperDirection = 1;
		stepperQueue = 0;
	}
	for(i = 0; i < n; i++) {
		stepperQueue |= (stepperQueue << 1) | (1 << 1);
	}
}

void backward_stepper(int n) {
	int i = 0; 
	if (stepperDirection == 1) {
		stepperDirection = 0;
		stepperQueue = 0;
	}
	for(i = 0; i < n; i++) {
		stepperQueue |= (stepperQueue << 1) | (1 << 1);
	}
}

void step(void) {
	char buffer[75];
	int r0 = (((currentPosition+0) % 4) + 2);
	int r1 = (((currentPosition+1) % 4) + 2);
	int r2 = (((currentPosition+2) % 4) + 2);
	int r3 = (((currentPosition+3) % 4) + 2);

	PORTC |=  (1<<r0);
	PORTC |=  (1<<r1);
	PORTC &= ~(1<<r2);
	PORTC &= ~(1<<r3);

	sprintf(buffer, "stepperDirection: %d\tcurrentPosition: %d\tr0: %d\tr1: %d\tr2: %d\tr3: %d\n", stepperDirection, currentPosition, r0, r1, r2, r3);
	send_str(buffer);
}