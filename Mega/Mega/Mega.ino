#include <AFMotor.h>
#include <Servo.h>
#include "globals.h"
#include "MotorFunctions.h"
#include "GeneralFunctions.h"
#include "ClawFunctions.h"
#include "Robot.h"

int robotTimer;
int state;

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	pinMode(analogClawPin, INPUT);
	pinMode(distanceRightPin, INPUT);
	pinMode(distanceLeftPin, INPUT);
	pinMode(A1, INPUT);
	pinMode(A2, INPUT);

	for (int i = 0; i < 30; i++) { analogRead(analogClawPin); }
	state = 0;
	
	Robot robot;
	robot.stopMovingClaw();

	// true = config A/LED off, false = config B/LED on
	bool configuration = true;

	int zeroPosition = analogRead(analogClawPin);

	/*
	while (true) {
		if (Serial.available() > 0) {
			char incomingMessage[] = "";
			Serial.readBytes(incomingMessage, 2);
			if (incomingMessage[0] == 'V') {
				int clawPosition = incomingMessage[1] - '0';
				setClawPosition(robot, clawPosition, zeroPosition);
			}
			Serial.write("REC");
			delay(1000);
		}
	}
	*/

	//delay(2000);
	//setClawPosition(robot, 3, zeroPosition);
	
	delay(1000);
	robot.driveMotors(robot.DRIVE_F, robot.SPEED_FACTOR * 4);
	while (digitalRead(A1) == HIGH && digitalRead(A2) == HIGH) {}
	//delay(1000);
	robot.driveMotors(robot.STOP_HARD, 0);
	delay(50);
	robot.driveMotors(robot.SPIN_L, 107);
	delay(150);
	robot.driveMotors(robot.STOP_HARD, 0);
	delay(500);
	
	/*

	setClawPosition(robot, 2, zeroPosition);
	delay(500);

	while (digitalRead(alignRightPin) == LOW && digitalRead(alignLeftPin) == LOW) {
		robot.driveMotors(robot.STRAFE_L, robot.SPEED_FACTOR * 7);
	}
	robot.driveMotors(robot.STOP_SOFT, 0);
	delay(500);

	driveForward(robot, robot.SPEED_FACTOR * 7, 300);
	delay(500);

	setClawPosition(robot, 1, zeroPosition);
	delay(500);

	robot.closeClaw();
	delay(500);

	setClawPosition(robot, 3, zeroPosition);
	delay(500);

	driveBackward(robot, robot.SPEED_FACTOR * 7, 800);
	delay(500);
	*/

	bool firstMovement = true;
	while (false) {

		while (digitalRead(powerPin) == HIGH) {
			delay(3000);
			digitalWrite(powerUnoPin, HIGH);
			Serial.println("ON");
			if (firstMovement) {
				setClawPosition(robot, 5, zeroPosition);
				delay(1000);
				driveForward(robot, robot.SPEED_FACTOR * 8, 3000);
				delay(1000);
				driveLeft(robot, robot.SPEED_FACTOR * 7, 900);
				delay(1000);
				setClawPosition(robot, 2, zeroPosition);
				delay(1000);
				driveForward(robot, robot.SPEED_FACTOR * 7, 200);
				delay(1000);
				robot.closeClaw();
				delay(1000);
				setClawPosition(robot, 3, zeroPosition);
				delay(1000);
				blockObtainedMovement(robot, configuration);
				firstMovement = false;
			}

			while (false) {
			//while (digitalRead(readyPin) == HIGH) {
				String incomingMessage = "";
				if (Serial.available()) {
					incomingMessage = Serial.readString();
					Serial.print("REC");
				}

				Serial.println(incomingMessage);

				int movement;
				int speed;
				bool openClaw;
				int color;
				int clawPosition;

				switch (incomingMessage.charAt(0)) {
				case 'W':
					movement = 2;
					speed = (incomingMessage.charAt(1) - '0') * robot.SPEED_FACTOR;
					state = 1;
					break;
				case 'A':
					movement = 0;
					speed = (incomingMessage.charAt(1) - '0') * robot.SPEED_FACTOR;
					state = 1;
					break;
				case 'S':
					movement = 3;
					speed = (incomingMessage.charAt(1) - '0') * robot.SPEED_FACTOR;
					state = 1;
					break;
				case 'D':
					movement = 1;
					speed = (incomingMessage.charAt(1) - '0') * robot.SPEED_FACTOR;
					state = 1;
					break;
				case 'Q':
					movement = 5;
					speed = (incomingMessage.charAt(1) - '0') * robot.SPEED_FACTOR;
					state = 1;
					break;
				case 'E':
					movement = 4;
					speed = (incomingMessage.charAt(1) - '0') * robot.SPEED_FACTOR;
					state = 1;
					break;
				case 'V':
					clawPosition = incomingMessage.charAt(1) - '0';
					setClawPosition(robot, clawPosition, zeroPosition);
					break;
				case 'C':
					if (incomingMessage.charAt(1) == '0')
						openClaw = false;
					else if (incomingMessage.charAt(1) == '1')
						openClaw = true;
					state = 3;
					break;
				case 'B':
					color = incomingMessage.charAt(1) - '0';
					break;
				default:
					break;
				}
			}
		}
	}
}

// the loop function runs over and over again until power down or reset
void loop() {}
