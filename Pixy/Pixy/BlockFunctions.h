// BlockFunctions.h

#ifndef _BLOCKFUNCTIONS_h
#define _BLOCKFUNCTIONS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

void outputColor(int color);
void outputMovement(int direction, int speed);
void outputTurn(int direction, int speed);
void outputClaw(int action);
bool checkIfGrabbed();

#endif

