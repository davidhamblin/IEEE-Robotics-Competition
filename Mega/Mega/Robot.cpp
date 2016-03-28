#include <Robot.h>
#include <Servo.h>
#include <AFMotor.h>

Robot::Robot() : motor_FL(1), motor_FR(2), motor_BL(4), motor_BR(3), servo_1(), servo_2()
{

	servo_1.attach(SERVO1_PWM);
	servo_2.attach(SERVO2_PWM);

	motor_FL.setSpeed(0);
    motor_FR.setSpeed(0);
    motor_BL.setSpeed(0);
    motor_BR.setSpeed(0);

	motor_FL.run(RELEASE);
    motor_FR.run(RELEASE);
    motor_BL.run(RELEASE);
    motor_BR.run(RELEASE);
}
 
void Robot::openClaw()
{
	servo_1.write(CLAW_OPEN);
}

void Robot::closeClaw()
{
	servo_1.write(CLAW_CLOSED);
}

void Robot::moveClawUp(int speed)
{
	servo_2.write(speed);
}

void Robot::moveClawDown(int speed)
{
	servo_2.write(speed);
}

void Robot::stopMovingClaw()
{
	servo_2.write(90);
}

void Robot::driveMotors(short direction, int speed)
{
    motor_FL.run(RELEASE);
	motor_FR.run(RELEASE);
	motor_BL.run(RELEASE);
	motor_BR.run(RELEASE);
	
	motor_FL.setSpeed(speed);
    motor_FR.setSpeed(speed);
    motor_BL.setSpeed(speed);
    motor_BR.setSpeed(speed);

    switch (direction)
	{    
    case DRIVE_F:
      motor_FL.run(FORWARD);
      motor_FR.run(FORWARD);
	  motor_BR.run(FORWARD);
      motor_BL.run(FORWARD);
      break;

    case DRIVE_B:
      motor_FL.run(BACKWARD);
      motor_FR.run(BACKWARD);
      motor_BL.run(BACKWARD);
      motor_BR.run(BACKWARD);
      break;

    case STRAFE_R:
      motor_FL.run(FORWARD);
      motor_FR.run(BACKWARD);
      motor_BL.run(BACKWARD);
      motor_BR.run(FORWARD);
      break;

    case STRAFE_L:
      motor_FL.run(BACKWARD);
      motor_FR.run(FORWARD);
      motor_BL.run(FORWARD);
      motor_BR.run(BACKWARD);
      break;

    case SPIN_R:
      motor_FL.run(FORWARD);
      motor_FR.run(BACKWARD);
      motor_BL.run(FORWARD);
      motor_BR.run(BACKWARD);
      break;

    case SPIN_L:
      motor_FL.run(BACKWARD);
      motor_FR.run(FORWARD);
      motor_BL.run(BACKWARD);
      motor_BR.run(FORWARD);
      break;

    case STOP_HARD:
      motor_FL.run(BRAKE);
      motor_FR.run(BRAKE);
      motor_BL.run(BRAKE);
      motor_BR.run(BRAKE);
      break;

    case STOP_SOFT:
    default:
      motor_FL.run(RELEASE);
      motor_FR.run(RELEASE);
      motor_BL.run(RELEASE);
      motor_BR.run(RELEASE);
      break;
    }
  }
  
void Robot::motorTest(int speed)
{
  
  driveMotors(DRIVE_F, speed);
  delay(2000);
  driveMotors(STOP_HARD, 0);
  delay(1000);
  driveMotors(DRIVE_F, speed);
  delay(2000);
  driveMotors(STOP_SOFT, 0);
  delay(1000);
  
  driveMotors(DRIVE_B, speed);
  delay(2000);
  driveMotors(STOP_HARD, 0);
  delay(1000);
  driveMotors(DRIVE_B, speed);
  delay(2000);
  driveMotors(STOP_SOFT, 0);
  delay(1000);

  driveMotors(STRAFE_R, speed);
  delay(2000);
  driveMotors(STOP_HARD, 0);
  delay(1000);
  driveMotors(STRAFE_R, speed);
  delay(2000);
  driveMotors(STOP_SOFT, 0);
  delay(1000);
  
  driveMotors(STRAFE_L, speed);
  delay(2000);
  driveMotors(STOP_HARD, 0);
  delay(1000);
  driveMotors(STRAFE_L, speed);
  delay(2000);
  driveMotors(STOP_SOFT, 0);
  delay(1000);
  
  driveMotors(SPIN_R, speed);
  delay(2000);
  driveMotors(STOP_HARD, 0);
  delay(1000);
  driveMotors(SPIN_R, speed);
  delay(2000);
  driveMotors(STOP_SOFT, 0);
  delay(1000);
  
  driveMotors(SPIN_L, speed);
  delay(2000);
  driveMotors(STOP_HARD, 0);
  delay(1000);
  driveMotors(SPIN_L, speed);
  delay(2000);
  driveMotors(STOP_SOFT, 0);
  delay(1000);
}
