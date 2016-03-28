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
	Serial.begin(4800);
	pinMode(A0, INPUT);

	state = 0;
	
	Robot robot;
	robot.stopMovingClaw();

	// true = config A/LED off, false = config B/LED on
	bool configuration = true;

	int zeroPosition = analogRead(A0);

	setClawPosition(robot, 3, zeroPosition);

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
				}
			}
		}
	}
}

// the loop function runs over and over again until power down or reset
void loop() {}
