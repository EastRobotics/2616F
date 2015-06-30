//Make sure this file only gets #included once
#ifndef __ROBOT_H__
#define __ROBOT_H__
//Prevent any unnecessary warnings
#pragma systemFile
//Define all constants
#include "constants.h"

///////////////////////////////////////////////////////////////////////////////
//MARK: - Enumerations
///////////////////////////////////////////////////////////////////////////////

//Enumeration to define easy motor speeds
typedef enum _MHMotorPower{
  //To stop is to not move. Duh.
  MHMotorPowerStop = 0,
	//If you wanna stall the motors, it's safe to put it at a power of 30, but that's about the lowest it's safe to go
	MHMotorPowerStall = 30,
	//31 is about the minimum power you can assign to a motor before it begins to twitch
	MHMotorPowerMin = 31,
	//While a true half is 63.5, we're defining integer constants here, so we'll give it the high end
	MHMotorPowerHalf = 64,
	//For some reason, the maximum possible power for a VEX motor is 127. Don't ask me why.
	MHMotorPowerMax = 127
}MHMotorPower;
//Enumeration to define robot drive sides
typedef enum _MHDriveSide{
  //The left side of the drive, when the robot is facing away from you
  MHDriveSideLeft,
  //The right drive side, when the robot is facing away from you
  MHDriveSideRight
}MHDriveSide;

///////////////////////////////////////////////////////////////////////////////
//MARK: - Drive Functions
///////////////////////////////////////////////////////////////////////////////

/* The simplest of drive functions

int left: Integer to represent how fast you want the left side of the drive to go
int right: Integer to represent how fast you want the right side of the drive to go

This function does not return anything

Called like: drive(42, 42); */
void drive(int left, int right);
/* Change the speed of only one side of the drive

MHDriveSide side: Constant to represent which side of the drive you want to change speed
int power: Integer to represent the power you want the side of the drive to move

This function does not return anything

Called like: driveSideWithPower(MHDriveSideLeft, 42); */
void driveSideWithPower(MHDriveSide side, int power);
/* Brings the robot to a full stop

This function takes no parameters

This function does not return anything

Called like: stop(); */
void stop();
/* Stops the motors on only one side of the drive

MHDriveSide side: Constant to represent which side of the drive you want to stop

This function does not return anything

Called like: stopDriveSide(MHDriveSideLeft); */
void stopDriveSide(MHDriveSide side);

///////////////////////////////////////////////////////////////////////////////
//MARK: - Ball Launching Functions
///////////////////////////////////////////////////////////////////////////////

/* Runs the motors to accept ammunition into the launching chamber

This function takes no parameters

This function does not return anything

Called like: intake(); */
void intake();
/* Stops the intake motors to prevent any more ammunition from coming into the launch chamber

This function takes no parameters

This function does not return anything

Called like: holdIntake(); */
void holdIntake();
/* Runs the motors to launch any ammunition in the launching chambers

This function takes no parameters

This function does not return anything

Called like: launch(); */

void launch();
/* Stops the launch motors, to prevent any ammunition from being fired from the launch chamber

This function takes no parameters

This function does not return anything

Called like: holdLaunch(); */
void holdLaunch();
/* Runs all motors in the cannon assembly to immediately launch any ammunition that comes in the intake

This function takes no parameters

This function does not return anything

Called like: fire(); */
void fire();
/* Stops all motors in the cannon assembly, to prevent anything from entering or leaving the launch chamber

This function takes no parameters

This function does not return anything

Called like: holdFire(); */
void holdFire();

//Actually implement the functions declared above
#include "robot.c"
#endif