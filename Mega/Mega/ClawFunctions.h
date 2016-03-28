// ClawFunctions.h

#include "Robot.h"

#ifndef _CLAWFUNCTIONS_h
#define _CLAWFUNCTIONS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

bool detectGrabbedBlock();
void setClawPosition(Robot robot, int position, int zeroPosition);

#endif

