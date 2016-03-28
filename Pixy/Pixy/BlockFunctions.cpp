#include "BlockFunctions.h"
#include "global.h"
#include <SPI.h>
#include <Pixy.h>

void outputColor(int color)
{
	switch (color)
	{
	// Red
	case 1:
		Serial.write("B0");
		break;
	// Green
	case 2:
		Serial.write("B1");
		break;
	// Yellow
	case 3:
		Serial.write("B2");
		break;
	// Blue
	case 4:
		Serial.write("B3");
		break;
	}
}

void outputMovement(int direction, int speed)
{
	switch (direction)
	{
	// Forward
	case 0:
		Serial.write("W" + speed);
		break;
	// Left
	case 1:
		Serial.write("A" + speed);
		break;
	// Backward
	case 2:
		Serial.write("S" + speed);
		break;
	// Right
	case 3:
		Serial.write("D" + speed);
		break;
	}
}

void outputTurn(int direction, int speed)
{
	switch(direction)
	{
	// Turn left
	case 0:
		Serial.write("Q" + speed);
	// Turn right
	case 1:
		Serial.write("E" + speed);
	}
}

void outputClaw(int action)
{
	Serial.write("C" + action);
}

bool checkIfGrabbed() {
	if (digitalRead(grabbedPin) == HIGH)
		return true;
	else
		return false;
}