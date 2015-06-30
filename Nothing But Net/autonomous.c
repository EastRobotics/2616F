//Don't redefine anything
#ifndef __AUTONOMOUS_C__
#define __AUTONOMOUS_C__
//Make sure we don't cause any unnecessary warnings
#pragma systemFile
//Require our header
#include "autonomous.h"

///////////////////////////////////////////////////////////////////////////////
//MARK: - Private Enumerations
///////////////////////////////////////////////////////////////////////////////

//Enumeration to specify which direction to run the intake motors
typedef enum _MHIntakeDirection{
  //Equivalent to running the motors to pass a ball to the launch chamber
  MHIntakeDirectionIntake = 1,
  //Equivalent to running the motors to reject a ball
  MHIntakeDirectionOuttake = -1
}MHIntakeDirection;
//Enumeration to specify which direction to run the launch motors
typedef enum _MHLaunchDirection{
  //Equivalent to running the motors to launch ammunition
  MHLaunchDirectionLaunch = MHIntakeDirectionIntake,
  //Equivalent to running the motors to reject a ball and pass it back to the intake
  MHLaunchDirectionBackfire = MHIntakeDirectionOuttake
}MHLaunchDirection;

///////////////////////////////////////////////////////////////////////////////
//MARK: - Drive Function Definitions
///////////////////////////////////////////////////////////////////////////////

//Definition of the simplest of drive functions
void drive(int left, int right){
  //Pass the integers given verbatim into the main drive function for each side
  driveSideWithPower(MHDriveSideLeft, left);
  driveSideWithPower(MHDriveSideRight, right);
}
//Change the speed of only one side of the drive
void driveSideWithPower(MHDriveSide side, int power){
  //We don't want to stall any of the motors
  if((power < MHMotorPowerStall && power > 0) || (power < -MHMotorPowerStall && power > -MHMotorPowerMax)){
    //So we make sure to stop any power that would be in the stall zone
    power = MHMotorPowerStop;
  }
  //Set the desired side of the drive to the desired power
  if(side == MHDriveSideRight){
    motor[rfDrive] = motor[rmDrive] = motor[rbDrive] = power;
  }
  else if(side == MHDriveSideLeft){
    motor[lfDrive] = motor[lmDrive] = motor[lbDrive] = power;
  }
}

///////////////////////////////////////////////////////////////////////////////
//MARK: - Ball Launching Function Definitions
///////////////////////////////////////////////////////////////////////////////
#endif