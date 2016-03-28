#include <Servo.h>
#include <AFMotor.h>
#include <Robot.h>


/*
Capstone Robot
 
 Drive = 3 bits (000)_2
 	000 No action
 	001 Foreward
 	010 Slide Right
 	011 Spin right
 	100 No action
 	101 Backward
 	110 Slide Left
 	111 Spin Left
 
 Claw  = 1 bit    (0)_2
 
 	0 Open Claw
 	1 Close Claw
 	
 Speed = analog
 
 	(0-1023) mapped to (0-255)
 */

const int controlBits [] =
{
  53,  // Claw Control
  51,  // Drive Control Invert
  49,  // Drive Control B
  47   // Drive Control A
};
const int nControlBits = 4;
int prevCommand[nControlBits];
int currCommand[nControlBits];

const int speedControl = A15;
int prevSpeedValue;
int currSpeedValue;

void setup()
{
  Serial.begin(9600);

  // Pin initialization
  for (int i = 0; i < nControlBits; ++i)
  {
    pinMode(controlBits[i], INPUT);
  }

  // Initialization of data and structures.
  Robot robot;
  prevSpeedValue = 0;
  currSpeedValue = 0;
  for (int i = 0; i < nControlBits; ++i)
  {
    prevCommand[i] = LOW;
    currCommand[i] = LOW;
  }

  
  while(true)
  {
    readControlLines();
    if (commandChanged())
    {
      if (currCommand[0] == HIGH)
      {
        robot.closeClaw();
      }
      else
      {
        robot.openClaw();
      }
      
      // 000 -> Brake
      if (currCommand[1] == LOW && currCommand[2] == LOW && currCommand[3] == LOW)
      {
        robot.driveMotors(Robot::STOP_HARD, currSpeedValue);
      }
      // 001 -> Drive Forward
      if (currCommand[1] == LOW && currCommand[2] == LOW && currCommand[3] == HIGH)
      {
        robot.driveMotors(Robot::DRIVE_F, currSpeedValue);
      }
      // 010 -> Strafe Right
      if (currCommand[1] == LOW && currCommand[2] == HIGH && currCommand[3] == LOW)
      {
        robot.driveMotors(Robot::STRAFE_R, currSpeedValue);
      }
      // 011 -> Spin Right
      if (currCommand[1] == LOW && currCommand[2] == HIGH && currCommand[3] == HIGH)
      {
        robot.driveMotors(Robot::SPIN_R, currSpeedValue);
      }
      // 100 -> Release
      if (currCommand[1] == HIGH && currCommand[2] == LOW && currCommand[3] == LOW)
      {
        robot.driveMotors(Robot::STOP_SOFT, currSpeedValue);
      }
      // 101 -> Drive Backward
      if (currCommand[1] == HIGH && currCommand[2] == LOW && currCommand[3] == HIGH)
      {
        robot.driveMotors(Robot::DRIVE_B, currSpeedValue);
      }
            // 000 -> Release
      if (currCommand[1] == HIGH && currCommand[2] == HIGH && currCommand[3] == LOW)
      {
        robot.driveMotors(Robot::STRAFE_L, currSpeedValue);
      }
            // 000 -> Release
      if (currCommand[1] == HIGH && currCommand[2] == HIGH && currCommand[3] == HIGH)
      {
        robot.driveMotors(Robot::SPIN_L, currSpeedValue);
      }
    }
  }
}

void loop() {
}

void readControlLines()
{
  for (int i = 0; i < nControlBits; ++i)
  {
    // Shift speed values
    prevSpeedValue = currSpeedValue;
    currSpeedValue = analogRead(speedControl);
    currSpeedValue = map(currSpeedValue, 0, 1023, 0, 255);

    // Shift command values
    prevCommand[i] = currCommand[i];
    currCommand[i] = digitalRead(controlBits[i]);
  }
}

boolean  commandChanged()
{
  for (int i = 0; i < nControlBits; ++i)
    if (prevCommand[i] != currCommand[i])
      return (prevSpeedValue == currSpeedValue);
  return (prevSpeedValue == currSpeedValue);
}
