//Don't redefine anything
#ifndef __ROBOT_C__
#define __ROBOT_C__
//Make sure we don't cause any unnecessary warnings
#pragma systemFile
//Require our header
#include "robot.h"

///////////////////////////////////////////////////////////////////////////////
//MARK: - Private Enumerations
///////////////////////////////////////////////////////////////////////////////

//Enumeration to specify which direction to run the intake motors
typedef enum _MHIntakeDirection{
  //Equivalent to running the motors to pass a ball to the launch chamber
  MHIntakeDirectionIntake = 1,
  //Equivalent to running the motors to reject a ball
  MHIntakeDirectionOuttake = -1,
  //Just stop the motors
  MHIntakeDirectionStop = 0
}MHIntakeDirection;
//Enumeration to specify which direction to run the launch motors
typedef enum _MHLaunchDirection{
  //Equivalent to running the motors to launch ammunition
  MHLaunchDirectionLaunch = MHIntakeDirectionIntake,
  //Equivalent to running the motors to reject a ball and pass it back to the intake
  MHLaunchDirectionBackfire = MHIntakeDirectionOuttake,
  //Just stop the motors
  MHLaunchDirectionStop = MHIntakeDirectionStop
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
//Stop the whole drive
void stop(){
  stopDriveSide(MHDriveSideLeft);
  stopDriveSide(MHDriveSideRight);
}
//Stop only one side of the drive
void stopDriveSide(MHDriveSide side){
  driveSideWithPower(side, MHMotorPowerStop);
}
///////////////////////////////////////////////////////////////////////////////
//MARK: - Private Ball Launching Function Definitions
///////////////////////////////////////////////////////////////////////////////

//Function to run intake motors
void intakeInDirection(MHIntakeDirection direction){
  //direction is either 1 or -1. This will run the intake motor(s) at full speed times the direction
  motor[in] = MHMotorPowerMax * direction;
}
//Function to run launch mechanism motors
void launchInDirection(MHLaunchDirection direction){
  //direction is either 1 or -1. This will run the launch motors at full speed times the direction
  motor[lLaunch] = motor[rLaunch] = MHMotorPowerMax * direction;
}
//Function to run the entire cannon assembly in a direction
void fireInDirection(MHLaunchDirection direction){
  //Run the intake motors in the specified direction, but treat it as the proper enumeration
  intakeInDirection((MHIntakeDirection)direction);
  //Run the launch motors in the specified driection
  launchInDirection(direction);
}

///////////////////////////////////////////////////////////////////////////////
//MARK: - Public Ball Launching Function Definitions
///////////////////////////////////////////////////////////////////////////////
//See header file for details on these functions

void intake(){
  //Run the intake in the logical direction
  intakeInDirection(MHIntakeDirectionIntake);
}
void holdIntake(){
  //Stop the intake motors
  intakeInDirection(MHIntakeDirectionStop);
}
void launch(){
  //Run the launch motors in the logical direction
  launchInDirection(MHLaunchDirectionLaunch);
}
void holdLaunch(){
  //Stop the launch motors
  holdLaunch();
}
void fire(){
  //Run the entire cannon assembly in the logical direction
  fireInDirection(MHLaunchDirectionLaunch);
}
void holdFire(){
  //Stop the entire cannon assembly
  fireInDirection(MHLaunchDirectionStop);
}
#endif