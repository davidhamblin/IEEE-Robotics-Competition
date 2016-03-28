#include "MotorFunctions.h"
#include "Robot.h"

void driveLeft(Robot robot, int speed, int time)
{
	robot.driveMotors(robot.STRAFE_L, speed);
	delay(time);
	robot.driveMotors(robot.STOP_SOFT, 0);
}
void driveRight(Robot robot, int speed, int time)
{
	robot.driveMotors(robot.STRAFE_R, speed);
	delay(time);
	robot.driveMotors(robot.STOP_SOFT, 0);
}
void driveForward(Robot robot, int speed, int time)
{
	robot.driveMotors(robot.DRIVE_F, speed);
	delay(time);
	robot.driveMotors(robot.STOP_SOFT, 0);
	delay(50);
	robot.driveMotors(robot.SPIN_L, 100);
	delay(100);
	robot.driveMotors(robot.STOP_SOFT, 0);
}
void driveBackward(Robot robot, int speed, int time)
{
	robot.driveMotors(robot.DRIVE_B, speed);
	delay(time);
	robot.driveMotors(robot.STOP_SOFT, 0);
}

void driveClockwise(Robot robot, int speed, int time)
{
	robot.driveMotors(robot.SPIN_R, speed);
	delay(time);
	robot.driveMotors(robot.STOP_SOFT, 0);
}

void driveCounterClockwise(Robot robot, int speed, int time)
{
	robot.driveMotors(robot.SPIN_L, speed);
	delay(time);
	robot.driveMotors(robot.STOP_SOFT, 0);
}
