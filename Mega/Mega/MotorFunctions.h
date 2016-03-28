// MotorFunctions.h
#include "Robot.h"

#ifndef _MOTORFUNCTIONS_h
#define _MOTORFUNCTIONS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

void driveLeft(Robot robot, int speed, int time);
void driveRight(Robot robot, int speed, int time);
void driveForward(Robot robot, int speed, int time);
void driveBackward(Robot robot, int speed, int time);
void driveClockwise(Robot robot, int speed, int time);
void driveCounterClockwise(Robot robot, int speed, int time);

#endif

