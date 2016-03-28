#include "BlockFunctions.h"
#include "global.h"
#include <SPI.h>  
#include <Pixy.h>

Pixy pixy;

/*
Serial commands:
 C[y] - set claw open or closed
	0 - close
	1 - open
 B[c] - set color of block
	0 - red
	1 - green
	2 - yellow
	3 - blue
 V[h] - set vertical lift to height h
	0-7 - lowest position, 5", 6.5", 7", 8.5", 10", 11.5", and highest position
 W|A|S|D[n] - move in direction WASD at speed n.
	0-9 - speed from stopped to max
 Q|E[n] - turn in direction QE at speed n
	0-9 - speed from stopped to max
*/

bool test = false;
bool moveClaw = true;

void setup()
{
	Serial.begin(9600);
	
	pinMode(readyPin, OUTPUT);
	pinMode(powerPin, INPUT);
	pinMode(grabbedPin, OUTPUT);
	pinMode(distanceRightPin, INPUT);
	pinMode(distanceLeftPin, INPUT);
	pinMode(alignRightPin, INPUT);
	pinMode(alignLeftPin, INPUT);

	pixy.init();

	while (false) {
		while (digitalRead(powerPin) == HIGH) {
			/*
			Serial.write("C1");
			digitalWrite(readyPin, HIGH);
			delay(2000);
			Serial.write("C0");
			*/

			if (Serial.available()) {
				String response = Serial.readString();
				if (response.equals("REC"))
					digitalWrite(readyPin, LOW);
			}

			bool hasBlock = checkIfGrabbed();
			if (!hasBlock)
			{
				uint16_t blocks = pixy.getBlocks();

				if (blocks)
				{
					//int colorPicker = identifyColor(blocks);

					// Send the Mega the color of the block being seen
					outputColor(2);
					outputMovement(0, 5);
					outputTurn(0, 3);
					outputClaw(1);
					digitalWrite(readyPin, HIGH);
				}
			}

			// State 0 = Looking for blocks
			// State 1 = Adjusting to block
			// State 2 = Looking for bins
			// State 3 = Adjusting to bin

			int state = 0;
			int robotDelay = 0;

			// TODO: Code for finding the barges that contain the blocks based on current position.
			if (state == 10) {
				Serial.println("W9");
				delay(500);
				Serial.println("W0");
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

void loop(){}

int identifyColor(uint16_t blocks)
{
	int redCount = 0;
	int greenCount = 0;
	int yellowCount = 0;
	int blueCount = 0;
	for (int j = 0; j < blocks; j++)
	{
		if (pixy.blocks[j].width >= 20 && pixy.blocks[j].height >= 20) {
			switch (pixy.blocks[j].signature) {
			case 1:
				redCount++;
				break;
			case 2:
				greenCount++;
				break;
			case 3:
				yellowCount++;
				break;
			case 4:
				blueCount++;
				break;
			}
		}
	}
	int counts[] = { redCount, greenCount, yellowCount, blueCount };
	int maxValue = counts[0];
	int colorPicker = 0;

	// Find the highest occurring block color
	for (int k = 1; k <= 4; k++) {
		if (counts[k] > counts[k - 1]) {
			maxValue = counts[k];
			colorPicker = k;
		}
	}

	return colorPicker;
}
