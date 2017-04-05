/*
 * main.c
 *
 *  Created on: Mar 21, 2017
 *      Author: mohamed
 */
#include <stdio.h>
#include <stdint.h>
#include "comms.h"
#include <stdbool.h>
#include "ring_buffer.h"
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef F_CPU					// if F_CPU was not defined in Project -> Properties
#define F_CPU 1000000UL			// define it now as 1 MHz unsigned long
#endif

//#define DEMO_MODE


//move the rope one step up
void stepUp() {
	send_str("Step up\n");
}

//move the rope one step down
void stepDown() {
	send_str("Step down\n");
}

//set position of servo motor
void setServo(int pin, int positionDegree) {
	char buffer[50];
	int n;
	n = sprintf(buffer, "Servo is moving to position %d*\n", positionDegree);
	send_str(buffer);
}

void setSpeedDC(int staticPin, int pwmPin, int speed) {
	char buffer[50];
	int n;
	if (speed > 255) {
		speed = 255;
	} else if (speed < -255) {
		speed = -255;
	} else if ((speed > -10) && (speed < 10)) {
		speed = 0;
	}
	n = sprintf(buffer, "DC motor is moving with duty cycle %d\n", speed);
	send_str(buffer);
}

void INITMOTOR(int PinStatic, int PinPWM) {
	DDRD |= (1 << PinStatic); // set Port D bit 3 for output to IN2 for MOTOR 1
	DDRD |= (1 << PinPWM);			// set Port D bit 6 for output to motor
}

/**SetSpeed function sets speed of motor. Register = 1
 is for Motor 1, Register = 0 is for Motor 2*/

int checkDuty (int duty){
	if (duty > 255) {
		duty = 255;
	} 
	else if (duty < -255) {
		duty = -255;
	}
}

void SetSpeed(int Speed, unsigned int Register) {
	if (Speed > 255) {
		Speed = 255;
	} else if (Speed < -255) {
		Speed = -255;
	} else if ((Speed > -10) && (Speed < 10)) {
		Speed = 0;
	}

	if (Register == 1) {
		if (Speed < 0) {
			PORTD |= (1 << DDD3);
			OCR0A = 255 + Speed;
		} else if ((Speed > 0) && (Speed < 255)) {
			PORTD &= !(1 << DDD3);
			OCR0A = Speed;
		}
	}

	else if (Register == 0) {
		if (Speed < 0) {
			PORTD |= (1 << DDD4);
			OCR0B = 255 + Speed;
		} else if ((Speed > 0) && (Speed < 255)) {
			PORTD &= !(1 << DDD4);
			OCR0B = Speed;
		}
	}

}

int getDutyOfDriveMode(int mode){
	switch (mode) {
		case 0: return 255;
		case 1: return 130;
		case 2: return 190;
	}
}


int main(void) {

	char buffer[50];
	int n;

	int dutyMotorR = 0; //duty cycle of the right motor, range 0..255
	int dutyMotorL = 0; //duty cycle of the left motor, range 0..255

	int dutyRightWithoutTurning = dutyMotorR; //duty for right motor when the turning buttons are not pressed 
	int dutyLefttWithoutTurning = dutyMotorL; //duty for right motor when the turning buttons are not pressed

	int driveMode = 0; //0 fast (255), 1 medium speed (190), 2 slow (130)
	int speedOfDriveMode = 255; // speed that corresponds to the drive mode

	float turnFactor = 0; // range -1..1 -1 is left, 1 is right

	int lightState = 0; //State of the light

	int upperClawPosition = 0; //position of the upper 3 quarters of the claw in degree
	int lowerClawPosition = 0; //position of the lower quarter of the claw in degree

	int cameraPosition = 90; // camera servo motor position in degree

	char previousChar = '\0'; // remember the previous character

	int carStatus = 0; // 0 break, 1 forward, 2 reverse

	int pinCameraServo = 1;
	int pinUpperClaw = 2;
	int pinLowerClaw = 3;
	int pinLight = 4;
	int staticPinR = 5;
	int pwmPinR = 6;
	int staticPinL = 7;
	int pwmPinL = 8;
	
	//Initialisations

	INITMOTOR(DDD3, DDD6); //Initialise DCmotor1
	INITMOTOR(DDD4, DDD5); //Initialise DCmotor2

	TCCR0A |= (1 << COM0A1); //compare output mode bit for non-inverting mode of OC0A
	TCCR0A |= (1 << COM0B1); //compare output mode bit for non-inverting mode of OC0B
	// set none-inverting mode
	TCCR0A |= (1 << WGM01) | (1 << WGM00); //wave generator bits
	// set fast PWM Mode
	TCCR0B |= (1 << CS01);
	// set prescaler to 8 and starts PWM

	cli();
	uart_init();
	sei();

	setServo(pinCameraServo, cameraPosition);
	setServo(pinUpperClaw, upperClawPosition);
	setServo(pinLowerClaw, lowerClawPosition);

	while (1) {
		char command = get_char();
		if (((previousChar == 'j') && (command != 'j')) ||
		((previousChar == 'l') && (command != 'l')) ||
		((previousChar == 'J') && (command != 'J')) ||
		((previousChar == 'L') && (command != 'L'))) {
			dutyMotorR = dutyRightWithoutTurning;
			dutyMotorL = dutyLefttWithoutTurning;
			dutyMotorR = checkDuty(dutyMotorR);
			dutyMotorL = checkDuty(dutyMotorL);
			setSpeedDC(staticPinR, pwmPinR, dutyMotorR);
			setSpeedDC(staticPinL, pwmPinL, dutyMotorL);
		}
		switch (command) {
		case 'z':
			if (cameraPosition > 0) {
				cameraPosition -= 5;
			}
			setServo(pinCameraServo, cameraPosition);
			n = sprintf(buffer, "Camera moved to position %d*\n",
					cameraPosition);
			send_str(buffer);
			break;
		case 'x':
			if (cameraPosition < 180) {
				cameraPosition += 5;
			}
			n = sprintf(buffer, "Camera moved to position %d*\n",
					cameraPosition);
			send_str(buffer);
			break;
		case 'q':
			stepUp();
			n = sprintf(buffer, "Winch moved one step up\n");
			send_str(buffer);
			break;
		case 'a':
			stepDown();
			n = sprintf(buffer, "Winch moved one step down\n");
			send_str(buffer);
			break;

		case 'r':
			if (upperClawPosition < 180) {
				upperClawPosition += 5;
			}
			setServo(pinUpperClaw, upperClawPosition);
			n = sprintf(buffer,"Upper claw moved to position %d*\n",
					upperClawPosition);
			send_str(buffer);
			break;
		case 'f':
			if (upperClawPosition > 0) {
				upperClawPosition -= 5;
			}
			setServo(pinUpperClaw, upperClawPosition);
			n = sprintf(buffer,"Upper claw moved to position %d*\n",
					upperClawPosition);
			send_str(buffer);
			break;
		case 't':
			if (lowerClawPosition < 180) {
				lowerClawPosition += 5;
			}
			setServo(pinLowerClaw, lowerClawPosition);
			n = sprintf(buffer,"Lower claw moved to position %d*\n",
					lowerClawPosition);
			send_str(buffer);
			break;
		case 'g':
			if (lowerClawPosition > 0) {
				lowerClawPosition -= 5;
			}
			setServo(pinLowerClaw, lowerClawPosition);
			n = sprintf(buffer,"Lower claw moved to position %d*\n",
					lowerClawPosition);
			send_str(buffer);
			break;
		case '1':
			lightState = 0;
			// Set light pin
			n = sprintf(buffer,"Light off \n");
			send_str(buffer);
			break;
		case '2':
			lightState = 1;
			// Set light pin
			n = sprintf(buffer,"Light on \n");
			send_str(buffer);
			break;
		case 'y':
			driveMode = 0;
			speedOfDriveMode = getDutyOfDriveMode(0);
			n = sprintf(buffer,"Drive mode was set to fast\n");
			send_str(buffer);
			break;
		case 'h':
			driveMode = 1;
			speedOfDriveMode = getDutyOfDriveMode(1);
			n = sprintf(buffer,"Drive mode was set to medium speed\n");
			send_str(buffer);
			break;
		case 'n':
			driveMode = 2;
			speedOfDriveMode = getDutyOfDriveMode(2);
			n = sprintf(buffer,"Drive mode was set to slow\n");
			send_str(buffer);
			break;
		case 'J':
			dutyRightWithoutTurning = 0;
			dutyLefttWithoutTurning = 0;
			dutyMotorR = speedOfDriveMode;
			dutyMotorL = -speedOfDriveMode;
			dutyMotorR = checkDuty(dutyMotorR);
			dutyMotorL = checkDuty(dutyMotorL);
			setSpeedDC(staticPinR, pwmPinR, dutyMotorR);
			setSpeedDC(staticPinL, pwmPinL, dutyMotorL);
			if (previousChar != command){
				n = sprintf(buffer,"Counterclockwise spinning\n");
				send_str(buffer);
			}
			break;
		case 'L':
			dutyRightWithoutTurning = 0;
			dutyLefttWithoutTurning = 0;
			dutyMotorR = -speedOfDriveMode;
			dutyMotorL = speedOfDriveMode;
			dutyMotorR = checkDuty(dutyMotorR);
			dutyMotorL = checkDuty(dutyMotorL);
			setSpeedDC(staticPinR, pwmPinR, dutyMotorR);
			setSpeedDC(staticPinL, pwmPinL, dutyMotorL);
			if (previousChar != command){
				n = sprintf(buffer,"Clockwise spinning\n");
				send_str(buffer);			
			}
			break;
		case 'i':
			dutyMotorR = speedOfDriveMode;
			dutyMotorL = speedOfDriveMode;
			dutyMotorR = checkDuty(dutyMotorR);
			dutyMotorL = checkDuty(dutyMotorL);
			setSpeedDC(staticPinR, pwmPinR, dutyMotorR);
			setSpeedDC(staticPinL, pwmPinL, dutyMotorL);
			carStatus = 1;
			n = sprintf(buffer,"Car moves forwards with the duty cycle %d\n",
					((dutyMotorR + dutyMotorL))/2);
			send_str(buffer);
			break;
		case 'm':
			dutyMotorR = -speedOfDriveMode;
			dutyMotorL = -speedOfDriveMode;
			dutyMotorR = checkDuty(dutyMotorR);
			dutyMotorL = checkDuty(dutyMotorL);
			setSpeedDC(staticPinR, pwmPinR, dutyMotorR);
			setSpeedDC(staticPinL, pwmPinL, dutyMotorL);
			carStatus = 2;
			n = sprintf(buffer,"Car moves backwards with the duty cycle %d\n",
					((dutyMotorR + dutyMotorL))/2);
			send_str(buffer);
			break;
		case 'k':
			dutyMotorR = 0;
			dutyMotorL = 0;
			dutyMotorR = checkDuty(dutyMotorR);
			dutyMotorL = checkDuty(dutyMotorL);
			setSpeedDC(staticPinR, pwmPinR, dutyMotorR);
			setSpeedDC(staticPinL, pwmPinL, dutyMotorL);
			carStatus = 0;
			n = sprintf(buffer,"Car breaks \n");
			send_str(buffer);
			break;
		case 'j':
			dutyRightWithoutTurning = dutyMotorR;
			dutyLefttWithoutTurning = dutyMotorL;
			dutyMotorR = dutyMotorR * 1.2;
			dutyMotorL = dutyMotorR * 0.8;
			dutyMotorR = checkDuty(dutyMotorR);
			dutyMotorL = checkDuty(dutyMotorL);
			setSpeedDC(staticPinR, pwmPinR, dutyMotorR);
			setSpeedDC(staticPinL, pwmPinL, dutyMotorL);
			if (previousChar != command){
				n = sprintf(buffer,"Car turns left \n");
				send_str(buffer);
			}
			break;
		case 'l':
			dutyRightWithoutTurning = dutyMotorR;
			dutyLefttWithoutTurning = dutyMotorL;
			dutyMotorR = dutyMotorR * 0.8;
			dutyMotorL = dutyMotorL * 1.2;
			dutyMotorR = checkDuty(dutyMotorR);
			dutyMotorL = checkDuty(dutyMotorL);
			setSpeedDC(staticPinR, pwmPinR, dutyMotorR);
			setSpeedDC(staticPinL, pwmPinL, dutyMotorL);
			if (previousChar != command){
				n = sprintf(buffer,"Car turns right \n");
				send_str(buffer);
			}
			break;
		}

		if ((command == 'y' || (command == 'h') || (command == 'n'))){
			if (carStatus == 1) {
				dutyMotorR = speedOfDriveMode;
				dutyMotorL = speedOfDriveMode;
				dutyRightWithoutTurning = dutyMotorR;
				dutyLefttWithoutTurning = dutyMotorL;
				dutyMotorR = checkDuty(dutyMotorR);
				dutyMotorL = checkDuty(dutyMotorL);
				setSpeedDC(staticPinR, pwmPinR, dutyMotorR);
				setSpeedDC(staticPinL, pwmPinL, dutyMotorL);
			}
			else if (carStatus == 2) {
				dutyMotorR = -speedOfDriveMode;
				dutyMotorL = -speedOfDriveMode;
				dutyRightWithoutTurning = dutyMotorR;
				dutyLefttWithoutTurning = dutyMotorL;
				dutyMotorR = checkDuty(dutyMotorR);
				dutyMotorL = checkDuty(dutyMotorL);
				setSpeedDC(staticPinR, pwmPinR, dutyMotorR);
				setSpeedDC(staticPinL, pwmPinL, dutyMotorL);
			}
		}

		if ((command != 'J') && (command != 'L') && (command != 'j') && (command != 'l')){
			n = sprintf(buffer, "SysSta: DuR=%d DuL=%d CamPos=%d UpClPos=%d LoClPos=%d Light=%d \n",
			dutyMotorR, dutyMotorL, cameraPosition, upperClawPosition, lowerClawPosition, lightState);
		}
		if (((command == 'J')&&(previousChar != 'J')) || ((command == 'L')&&(previousChar != 'L')) || ((command == 'j')&&(previousChar != 'j')) || ((command == 'l')&&(previousChar != 'l'))){
			n = sprintf(buffer, "SysSta: DuR=%d DuL=%d CamPos=%d UpClPos=%d LoClPos=%d Light=%d \n",
			dutyMotorR, dutyMotorL, cameraPosition, upperClawPosition, lowerClawPosition, lightState);
		}
		previousChar = command;
	}

//SetSpeed(Speed, 0);
//SetSpeed(Orientation, 1);

///////////////////////////////////////////////////////////////////////////////////////////////////

//int main(void) {

//DDRC &= !(1 << PC5);// set Port C bit 5 for Analog Read from joystick - x axis
//DDRC &= !(1 << PC4);// set Port C bit 5 for Analog Read from joystick - y axis

//ADCSRA = 0b10100011;

//ADCSRB = 0b00000000;

//ADCSRA |= (1 << ADSC);		// start ADC

//while (1) {
//_delay_ms(1);
//ADMUX = 0b01100100;
//ADCSRA = 0b10100011;
//ADCSRB = 0b00000000;
//ADCSRA |= (1 << ADSC);
//signed int Speed = ADCH;
//_delay_ms(1);
//ADMUX = 0b01100101;
//ADCSRA = 0b10100011;

//ADCSRA |= (1 << ADSC);
//_delay_ms(10);

//signed int Orientation = ADCH;// assign contents of ADCH to Analog variable
//Speed = (Speed - 127) * 2;
//Orientation = (Orientation - 127) * 2;

//float Adjust = (float)Orientation/127;
//int Speed1 = Speed * (Adjust);
//int Speed2 = Speed * (2 - Adjust);
//signed int Speed2 = ADCH;								// assign contents of ADCH to Analog variable
//signed int Speed2 = (Speed1 - 127) * 2;

//}
	return (0);	// should never get here, this is to prevent a compiler warning
}

