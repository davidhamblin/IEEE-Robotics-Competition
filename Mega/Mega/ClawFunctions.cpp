#include "ClawFunctions.h"
#include "globals.h"

bool detectGrabbedBlock() {
	return false;
}

void setClawPosition(Robot robot, int position, int zeroPosition)
{
	switch (position) {
		// Move claw to lowest position
	case 0:
		if (analogRead(analogClawPin) > (zeroPosition + 43))
			robot.moveClawUp(140);
		else
			robot.moveClawDown(80);
		while (analogRead(analogClawPin) != (zeroPosition + 41)) {}
		robot.stopMovingClaw();
		break;
		// Move claw to position 6.5"
	case 1:
		if (analogRead(analogClawPin) > zeroPosition)
			robot.moveClawUp(140);
		else
			robot.moveClawDown(80);
		while (analogRead(analogClawPin) > (zeroPosition) + 1 || analogRead(analogClawPin) < (zeroPosition - 30) - 1) {}
		robot.stopMovingClaw();
		break;
		// Move claw to position 7"
	case 2:
		if (analogRead(analogClawPin) > (zeroPosition - 37))
			robot.moveClawUp(140);
		else
			robot.moveClawDown(80);
		while (analogRead(analogClawPin) > (zeroPosition - 37) + 1 || analogRead(analogClawPin) < (zeroPosition - 37) - 1) { Serial.println(analogRead(analogClawPin)); }
		robot.stopMovingClaw();
		break;
		// Move claw to position 8.5"
	case 3:
		if (analogRead(analogClawPin) > (zeroPosition - 142))
			robot.moveClawUp(140);
		else
			robot.moveClawDown(80);
		while (analogRead(analogClawPin) > (zeroPosition - 142) + 1 || analogRead(analogClawPin) < (zeroPosition - 142) - 1) {}
		robot.stopMovingClaw();
		break;
		// Move claw to position 10"
	case 4:
		if (analogRead(analogClawPin) > (zeroPosition - 256))
			robot.moveClawUp(140);
		else
			robot.moveClawDown(80);
		while (analogRead(analogClawPin) > (zeroPosition - 256) + 1 || analogRead(analogClawPin) < (zeroPosition - 256) - 1) {}
		robot.stopMovingClaw();
		break;
		// Move claw to position 11.5"
	case 5:
		if (analogRead(analogClawPin) > (zeroPosition - 365))
			robot.moveClawUp(140);
		else
			robot.moveClawDown(80);
		while (analogRead(analogClawPin) > (zeroPosition - 365) + 1 || analogRead(analogClawPin) < (zeroPosition - 365) - 1) {}
		robot.stopMovingClaw();
		break;
	default:
		setClawPosition(robot, 1, zeroPosition);
	}
}
