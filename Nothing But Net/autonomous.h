//Make sure this file only gets #included once
#ifndef __AUTONOMOUS_H__
#define __AUTONOMOUS_H__
//Prevent any unnecessary warnings
#pragma systemFile
//Define all constants
#include "constants.h"

//MARK: - Function Prototype Declarations

//Prototype for the simplest of drive functions
void drive(int left, int right);
//Prototype to change only one side of the drive
void driveSideWithPower(MHDriveSide side, int power);

//MARK: - Function Definitions

//Definition of the simplest of drive functions
void drive(int left, int right){
  driveSideWithPower(MHDriveSideLeft, left);
  driveSideWithPower(MHDriveSideRight, right);
}
//Change the speed of only one side of the drive
void driveSideWithPower(MHDriveSide side, int power){
  if(power <= MHMotorPowerStall){
    power = MHMotorPowerStop;
  }
  if(side == MHDriveSideRight){
    motor[rfDrive] = motor[rmDrive] = motor[rbDrive] = power;
  }
  else if(side == MHDriveSideLeft){
    motor[lfDrive] = motor[lmDrive] = motor[lbDrive] = power;
  }
}
#endif