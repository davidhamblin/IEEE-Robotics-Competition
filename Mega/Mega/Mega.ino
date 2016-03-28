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
	Serial1.begin(9600);
	
	// Initialize the input and output pins.
	pinMode(blockAlignedPin, INPUT);
	pinMode(blockGrabbedPin, OUTPUT);
	pinMode(readyPin, INPUT);
	pinMode(A8, INPUT);
	pinMode(A9, INPUT);
	pinMode(A10, INPUT);
	pinMode(configLEDPin, OUTPUT);
	pinMode(powerPin, INPUT);
	pinMode(configPin, INPUT);
	pinMode(distanceRightPin, INPUT);
	pinMode(distanceLeftPin, INPUT);
	pinMode(alignRightPin, INPUT);
	pinMode(alignLeftPin, INPUT);

	state = 0;
	
	Robot robot;
	robot.stopMovingClaw();

	// true = config A/LED off, false = config B/LED on
	bool configuration = true;

	int zeroPosition = analogRead(A1);
	//robot.closeClaw();
	//robot.openClaw();
	//Serial.println(zeroPosition);

	robot.moveClawUp(140);
	delay(1500);
	robot.stopMovingClaw();

	//setClawPosition(robot, 3, zeroPosition);
	//delay(500);
	
	/*
	robot.driveMotors(robot.DRIVE_F, robot.SPEED_FACTOR * 4);
	while (digitalRead(distanceRightPin) == HIGH && digitalRead(distanceLeftPin) == HIGH) {}
	robot.driveMotors(robot.STOP_HARD, 0);
	delay(50);
	robot.driveMotors(robot.SPIN_L, 107);
	delay(150);
	robot.driveMotors(robot.STOP_HARD, 0);
	delay(500);

	
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
		/*
		bool temp = false;
		if (digitalRead(distanceRightPin) == LOW) {
			Serial.println("RIGHT");
			temp = true;
		}
		if (digitalRead(distanceLeftPin) == LOW) {
			Serial.println("LEFT");
			temp = true;
		}
		if (temp)
			Serial.println();
		delay(2000);
		*/

	//robot.driveMotors(robot.STOP_SOFT, 0);

	bool firstMovement = true;
	while (false) {
		//Serial.println("OFF");
		digitalWrite(powerUnoPin, LOW);

		if (digitalRead(configPin) == HIGH) {
			configuration = !configuration;
			delay(200);
		}

		if (!configuration)
			digitalWrite(configLEDPin, HIGH);
		else
			digitalWrite(configLEDPin, LOW);

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
				if (Serial1.available()) {
					incomingMessage = Serial1.readString();
					Serial1.print("REC");
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

				bool blockGrabbed;
				int robotDelay = 0;
				//robotDelay = pulseIn(timerPin, HIGH);
				//if (robotDelay > 0)
				//	state = 1;

				// State 0 = Looking for blocks
				// State 1 = Adjusting to block
				// State 2 = Looking for bins
				// State 3 = Adjusting to bin

				// TODO: Code for finding the barges that contain the blocks based on current position.
				if (state == 10) {
					driveForward(robot, robot.MAX_SPEED, robotDelay);
				}
				// Once the blocks are found, adjust the robot so that it can pick up the block, with info sent from the Uno.
				else if (state == 1) {
					while (digitalRead(blockAlignedPin) == LOW) {
						//String blockColor = extractColor(colorPins);
						switch (6) {
						// 0 = left
						case 0:
							driveLeft(robot, robot.MAX_SPEED, robotDelay);
							break;
						// 1 = right
						case 1:
							driveRight(robot, robot.MAX_SPEED, robotDelay);
							break;
						// 2 = forward
						case 2:
							driveForward(robot, robot.MAX_SPEED, robotDelay);
							break;
						// 3 = backward
						case 3:
							driveBackward(robot, robot.MAX_SPEED, robotDelay);
							break;
						// 4 = turn right
						case 4:
							driveClockwise(robot, robot.MAX_SPEED, robotDelay);
							break;
						// 5 = turn left
						case 5:
							driveCounterClockwise(robot, robot.MAX_SPEED, robotDelay);
							break;
						}
					}

					if (digitalRead(blockAlignedPin) == HIGH) {
						setClawPosition(robot, 3, zeroPosition);
						delay(1000);
						driveForward(robot, robot.SPEED_FACTOR * 5, 500);
						delay(1000);
						robot.closeClaw();
					}

					blockGrabbed = detectGrabbedBlock();
					if (blockGrabbed) {
						digitalWrite(blockGrabbedPin, HIGH);
						blockObtainedMovement(robot, configuration);
						state = 2;
					}
				}
				// TODO: With the block in the claw, drive towards the appropriate bin.
				else if (state == 2) {

				}
				// TODO: Adjust the robots position to properly drop the block in its designated location.
				else if (state == 3) {

					if (openClaw)
						robot.openClaw();
					else
						robot.closeClaw();

					blockGrabbed = detectGrabbedBlock();
					if (!blockGrabbed) {
						digitalWrite(blockGrabbedPin, LOW);
						state = 0;
					}
				}
			}
		}
	}
}

// the loop function runs over and over again until power down or reset
void loop() {}
