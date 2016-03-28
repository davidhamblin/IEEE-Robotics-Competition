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
		if (analogRead(A1) > (zeroPosition + 40))
			robot.moveClawUp(140);
		else
			robot.moveClawDown(80);
		while (analogRead(A1) != (zeroPosition + 40)) {}
		robot.stopMovingClaw();
		break;
	// Move claw to position 6.5"
	case 1:
		if (analogRead(A1) > zeroPosition)
			robot.moveClawUp(140);
		else
			robot.moveClawDown(80);
		while (analogRead(A1) > (zeroPosition) + 1 || analogRead(A1) < (zeroPosition - 31) - 1) {}
		robot.stopMovingClaw();
		break;
	// Move claw to position 7"
	case 2:
		if (analogRead(A1) > (zeroPosition - 40))
			robot.moveClawUp(140);
		else
			robot.moveClawDown(80);
		while (analogRead(A1) > (zeroPosition - 40) + 1 || analogRead(A1) < (zeroPosition - 62) - 1) {}
		robot.stopMovingClaw();
		break;
	// Move claw to position 8.5"
	case 3:
		if (analogRead(A1) > (zeroPosition - 144))
			robot.moveClawUp(140);
		else
			robot.moveClawDown(80);
		while (analogRead(A1) > (zeroPosition - 144) + 1 || analogRead(A1) < (zeroPosition - 162) - 1) {}
		robot.stopMovingClaw();
		break;
	// Move claw to position 10"
	case 4:
		if (analogRead(A1) > (zeroPosition - 257))
			robot.moveClawUp(140);
		else
			robot.moveClawDown(80);
		while (analogRead(A1) > (zeroPosition - 257) + 1 || analogRead(A1) < (zeroPosition - 268) - 1) {}
		robot.stopMovingClaw();
		break;
	// Move claw to position 11.5"
	case 5:
		if (analogRead(A1) > (zeroPosition - 367))
			robot.moveClawUp(140);
		else
			robot.moveClawDown(80);
		while (analogRead(A1) > (zeroPosition - 367) + 1 || analogRead(A1) < (zeroPosition - 370) - 1) {}
		robot.stopMovingClaw();
		break;
	// Move clawn to highest position
	case 6:
		if (analogRead(A1) > (zeroPosition - 406))
			robot.moveClawUp(140);
		while (analogRead(A1) > (zeroPosition - 406) + 1) {}
		robot.stopMovingClaw();
		break;
	}
}
