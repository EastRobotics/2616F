//Make sure this file only gets #included once
#ifndef __AUTONOMOUS_H__
#define __AUTONOMOUS_H__
//Define all constants
#include "enumerations.h"

//MARK: - Function Prototype Declarations

//Prototype for the simplest of drive functions
void drive(MHMotorPower left, MHMotorPower right);

//MARK: - Function Definitions

//Definition of the simplest of drive functions
void drive(MHMotorPower left, MHMotorPower right){
  motor[lfDrive] = motor[lmDrive] = motor[lbDrive] = left;
  motor[rfDrive] = motor[rmDrive] = motor[rbDrive] = right;
}
#endif