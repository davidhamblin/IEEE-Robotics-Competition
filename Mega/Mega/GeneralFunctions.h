// GeneralFunctions.h

#include "Robot.h"

#ifndef _GENERALFUNCTIONS_h
#define _GENERALFUNCTIONS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

void blockObtainedMovement(Robot robot, bool config);

#endif

