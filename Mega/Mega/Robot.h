#ifndef Robot_h
#define Robot_h

#include "Arduino.h"
#include <Servo.h>
#include <AFMotor.h>

class Robot
{
public:
  Robot();
  void driveMotors(short direction, int speed);
  void motorTest(int speed);
  void openClaw();
  void closeClaw();

  void moveClawUp(int speed);
  void moveClawDown(int speed);
  void stopMovingClaw();
  
  const static int SERVO1_PWM = 10;
  const static int SERVO2_PWM = 9;

  const static int DRIVE_F   = 40;
  const static int DRIVE_B   = 41;
  const static int STRAFE_R  = 42;
  const static int STRAFE_L  = 43;
  const static int SPIN_R    = 44;
  const static int SPIN_L    = 45;
  const static int STOP_SOFT = 46;
  const static int STOP_HARD = 47;

  const static int CLAW_OPEN   = 10;
  const static int CLAW_CLOSED = 130;

  const static int MAX_SPEED = 255;
  const static int MIN_SPEED = 0;
  const static int SPEED_FACTOR = 28;

private:
	AF_DCMotor motor_FL;
	AF_DCMotor motor_FR;
	AF_DCMotor motor_BL;
	AF_DCMotor motor_BR;
	Servo servo_1;
	Servo servo_2;
};

#endif


