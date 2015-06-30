//Make sure this file only gets #included once
#ifndef __AUTONOMOUS_H__
#define __AUTONOMOUS_H__
//Prevent any unnecessary warnings
#pragma systemFile
//Define all constants
#include "constants.h"

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

///////////////////////////////////////////////////////////////////////////////
//MARK: - Ball Launching Functions
///////////////////////////////////////////////////////////////////////////////

/* Runs the motors to accept ammunition into the launching chamber

This function takes no parameters

This function does not return anything

Called like: intake(); */
void intake();
/* Runs the motors to launch any ammunition in the launching chambers

This function takes no parameters

This function does not return anything

Called like: launch(); */
void launch();
/* Runs all motors in the cannon assembly to immediately launch any ammunition that comes in the intake

This function takes no parameters

This function does not return anything

Called like: fire(); */
void fire();

//Actually implement the functions declared above
#include "autonomous.c"
#endif