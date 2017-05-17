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
		currentPosition = (currentPosition + 1) % 8;
	} else {
		currentPosition = (currentPosition - 1) % 8;
		if(currentPosition == -1){
			currentPosition = 7;
		}
	}
	stepperQueue = stepperQueue - 1;

	stepBinary();
}

void forward_stepper(int n) {
	if (stepperDirection == 0) {
		stepperDirection = 1;
		stepperQueue = 0;
	}
	stepperQueue = stepperQueue + n;
}

void backward_stepper(int n) {
	if (stepperDirection == 1) {
		stepperDirection = 0;
		stepperQueue = 0;
	}
	stepperQueue = stepperQueue + n;
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

	//sprintf(buffer, "stepperDirection: %d\tcurrentPosition: %d\tr0: %d\tr1: %d\tr2: %d\tr3: %d\n", stepperDirection, currentPosition, r0, r1, r2, r3);
	sprintf(buffer, "step: %d\n", currentPosition);
	send_str(buffer);
}

void stepBinary(void) {
	char buffer[75];
	
	switch(currentPosition) {
	case 0:
		PORTC = 0b00000100;
		break;
	case 1:
		PORTC = 0b00001100;
		break;
	case 2:
		PORTC = 0b00001000;
		break;
	case 3:
		PORTC = 0b00011000;
		break;
	case 4:
		PORTC = 0b00010000;
		break;
	case 5:
		PORTC = 0b00110000;
		break;
	case 6:
		PORTC = 0b00100000;
		break;
	case 7:
		PORTC = 0b001001000;
		break;
	}
	sprintf(buffer, "step: %d\n", stepperQueue);
	send_str(buffer);
}

