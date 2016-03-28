#include "GeneralFunctions.h"
#include "Robot.h"
#include "MotorFunctions.h"

void blockObtainedMovement(Robot robot, bool config)
{
	driveBackward(robot, robot.SPEED_FACTOR * 6, 900);
	delay(1000);
	if(config)
		driveClockwise(robot, robot.SPEED_FACTOR * 6, robot.SPEED_FACTOR * 6 * 7 + 50);
	else
		driveCounterClockwise(robot, robot.SPEED_FACTOR * 6, robot.SPEED_FACTOR * 6 * 7 + 50);

}
