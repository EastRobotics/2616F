#pragma systemFile
#ifndef enums
//This file depends on enumerations.h
#include "enumerations.h"
#endif
MHSkyriseArmRotationSide skyriseSide;
MHTeamColor roundColor;
/////////////////////////////////////////////////////////////////////////////////////////
//**Reset encoders**/
/////////////////////////////////////////////////////////////////////////////////////////
void resetEncoders(){                        //Clears lift encoders
	nMotorEncoder[lbLift] = 0;
  nMotorEncoder[rbLift] = 0;
}
/////////////////////////////////////////////////////////////////////////////////////////
//**Basic**/
//
//Caveman-simple driving with nothing
/////////////////////////////////////////////////////////////////////////////////////////
void basicDrive(int leftPower, int rightPower){
	motor[lmDrive] = motor[lbDrive] = leftPower;
 	motor[rDrive] = rightPower;
}
/////////////////////////////////////////////////////////////////////////////////////////
//**Drive**/
//
//Simple driving with straighening but no stopping limit
/////////////////////////////////////////////////////////////////////////////////////////
void drive(int power){
	//Adds ability to use to use function to stop drive
	if(power != 0){
  	basicDrive(power, power);
    //Compares left and right encoder values to straighten robot
    if(nMotorEncoder[lbDrive] == nMotorEncoder[rDrive]){
    	basicDrive(power, power);
    }
    else if(nMotorEncoder[lbDrive] < nMotorEncoder[rDrive]){
    	basicDrive(power, power-40);
    }
    else{
      basicDrive(power-40,power);
    }
  }
  //Stops drive if power is zero
  else{
  	basicDrive(0,0);
  }
}


/////////////////////////////////////////////////////////////////////////////////////////
//**Encoder-based Drive**/
//
//Info:
// • + or - power determines front or back
// • encoder count must be positive
// • drive power of 80 is very reliable
/////////////////////////////////////////////////////////////////////////////////////////
void encoderDrive(int power, int encoderCount){
	while(abs(nMotorEncoder[lbDrive]) < encoderCount){
     basicDrive(power, power);
  }
  //Stop when you're at your destination
  drive(0);
}

/////////////////////////////////////////////////////////////////////////////////////////
//**Encoder-based Drive w/ Lift**/
//
//Info:
// • + or - power determines front or back
// • + or - position determines lift up or down
// • encoder count must be positive
/////////////////////////////////////////////////////////////////////////////////////////
void encoderDriveWithLift(int power, int encoderCount, int position){
	while(abs(nMotorEncoder[lbDrive]) < encoderCount && abs(nMotorEncoder[rDrive]) < encoderCount - 300){
		//Drive robot at power
  	drive(power);
    if(nMotorEncoder[lbDrive] >= encoderCount){
    	motor[lbDrive] = motor[lmDrive] = 0;
    }
    if(nMotorEncoder[rDrive] >= encoderCount){
     	motor[rDrive] = motor[rDrive] = 0;
    }
  }
  //Slow down near destination
	while(abs(nMotorEncoder[lbDrive]) < encoderCount && abs(nMotorEncoder[rDrive]) < encoderCount){
  	drive(power);
   	if(nMotorEncoder[lbDrive] >= encoderCount){
    	motor[lbDrive] = motor[lmDrive] = 0;
    }
    if(nMotorEncoder[rDrive] >= encoderCount){
    	motor[rDrive] = 0;
  	}
  }
  //Turn off after it has reached destination
  drive(0);
}

/////////////////////////////////////////////////////////////////////////////////////////
//**Spin**/
//
//Spin robot using encoders
//positive degrees10 = clockwise
/////////////////////////////////////////////////////////////////////////////////////////
void spin(int power, int encoderCount){
	//Clockwise with positive power
  if(power > 0){
  	while(abs(nMotorEncoder[lbDrive]) < encoderCount){
    	basicDrive(power, -power);
    }
  }
  else{
  	while(abs(nMotorEncoder[lbDrive]) < encoderCount){
    	basicDrive(power, -power);
    }
  }
  drive(0);
}


/////////////////////////////////////////////////////////////////////////////////////////
//**Hook turn**/
//
//Spin robot using encoders
//positive degrees10 = clockwise
/////////////////////////////////////////////////////////////////////////////////////////
void hookSpin(int power, int encoderCount){
	//Clockwise with positive power
  if(power > 0){
  	while(abs(nMotorEncoder[lbDrive]) < encoderCount){
    	basicDrive(power, -25);
    }
  }
  else{
  	while(abs(nMotorEncoder[lbDrive]) < encoderCount){
    	basicDrive(25, -power);
    }
  }
  drive(0);
}

/////////////////////////////////////////////////////////////////////////////////////////
//**Lift the lift up**/
// Encodercount sign does not matter. sign of power determines
/////////////////////////////////////////////////////////////////////////////////////////
void liftLift(int encoderCount){
	//int encoderAverage = (abs(nMotorEncoder[leftLiftBottom]) + abs(nMotorEncoder[rightLiftBottom]))/2;
	while(true){
		if(abs(nMotorEncoder[rbLift]) < encoderCount){
			motor[lfLift] = motor[lbLift] =  motor[rfLift] = motor[rbLift]  = 127;
		}
		else{
			motor[lfLift] = motor[lbLift] =  motor[rfLift] = motor[rbLift] = 0;
			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
//**Lower the lift down**/
/////////////////////////////////////////////////////////////////////////////////////////
void lowerLift(int encoderCount){
	//int encoderAverage = (abs(nMotorEncoder[leftLiftBottom]) + abs(nMotorEncoder[rightLiftBottom]))/2;
	while(true){
		if(abs(nMotorEncoder[rbLift]) > encoderCount){
			motor[lfLift] = motor[lbLift] = motor[rfLift] = motor[rbLift] = -127;
		}
		else{
			motor[lfLift] = motor[lbLift] = motor[rfLift] = motor[rbLift] = 0;
			return;
		}
	}
}
void lift(int power, MHLiftDirection direction){
	motor[rfLift] = motor[rbLift] = motor[lfLift] = motor[lbLift] = abs(power) * direction;
}
void stopDriveSide(MHRobotSide side){
	 if(side == MHRobotSideRight){
	   motor[rDrive] = MHMotorPowerStop;
	 }
	 else if(side == MHRobotSideLeft){
	   motor[lmDrive] = motor[lbDrive] = MHMotorPowerStop;
	 }
	 else{
	   motor[rDrive] = motor[lmDrive] = motor[lbDrive] = MHMotorPowerStop;
	 }
}
void stopDrive(){
	stopDriveSide(MHRobotSideLeft);
	stopDriveSide(MHRobotSideRight);
}
void liftForEncoderDistance(int count, int power){
	resetEncoders();
	string first;
	string second;
	while(abs(nMotorEncoder[lbLift]) < count){
		sprintf(first, "%d", abs(nMotorEncoder[lbLift]));
		sprintf(second, "%d", abs(nMotorEncoder[rbLift]));
		displayLCDCenteredString(0, first);
		displayLCDCenteredString(1, second);
		if(power > 0){
			lift(power, MHLiftDirectionUp);
		}
		else if(power < 0){
			lift(power, MHLiftDirectionDown);
		}
		//Because power is not greater than or less than 0, it's safe to assume it is 0, and the lift should stop
		else{
			lift(MHMotorPowerStop, MHLiftDirectionStop);
		}
	}
	lift(MHMotorPowerStop, MHLiftDirectionStop);
}
void resetLift(){
	liftForEncoderDistance(nMotorEncoder[lbLift], -MHMotorPowerMax);
}
void liftCube(MHLiftDirection direction){
	motor[cubeIntake] = MHMotorPowerMax * direction;
}
void liftCubeForTime(int time, MHLiftDirection direction){
	liftCube(direction);
	wait1Msec(time);
	liftCube(MHLiftDirectionStop);
}
bool armIsInRangeOfSide(MHSkyriseArmRotationSide side){
	if(side == MHSkyriseArmRotationSideRightSide || side == MHSkyriseArmRotationSideLeftSide){
		if(SensorValue[armAngle] <= side + 50 && SensorValue[armAngle] >= side - 50){
			return true;
		}
	}
	else if(side == MHSkyriseArmRotationSideMiddle){
		if(SensorValue[armAngle] > MHSkyriseArmRotationSideRightSide && SensorValue[armAngle] < MHSkyriseArmRotationSideLeftSide){
			return true;
		}
		else{
			return false;
		}
	}
	else if(side == MHSkyriseArmRotationSideOutOfBounds){
		if(SensorValue[armAngle] < MHSkyriseArmRotationSideRightSide || SensorValue[armAngle] > MHSkyriseArmRotationSideLeftSide){
			return true;
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}
MHSkyriseArmRotationSide currentArmSide(){
	if(armIsInRangeOfSide(MHSkyriseArmRotationSideLeftSide)){
		return MHSkyriseArmRotationSideLeftSide;
	}
	else if(armIsInRangeOfSide(MHSkyriseArmRotationSideMiddle)){
		return MHSkyriseArmRotationSideMiddle;
	}
	else if(armIsInRangeOfSide(MHSkyriseArmRotationSideRightSide)){
		return MHSkyriseArmRotationSideRightSide;
	}
	else{
		return MHSkyriseArmRotationSideOutOfBounds;
	}
}
void swingArmToSide(MHSkyriseArmRotationSide side){
	if(side != MHSkyriseArmRotationSideOutOfBounds){
		int direction = 1;
		 if(side == MHSkyriseArmRotationSideRightSide || (side == MHSkyriseArmRotationSideMiddle && SensorValue[armAngle] > MHSkyriseArmRotationSideMiddle)){
		   direction *= -1;
		 }
		 while(currentArmSide() != side){
		   motor[skyriseArm] = MHMotorPowerMax * direction;
		 }
	}
}
void toggleArmSide(){
	if(currentArmSide() == MHSkyriseArmRotationSideRightSide){
		swingArmToSide(MHSkyriseArmRotationSideLeftSide);
	}
	else if(currentArmSide() == MHSkyriseArmRotationSideLeftSide){
		swingArmToSide(MHSkyriseArmRotationSideRightSide);
	}
	else{
		//Just in case it's out of bounds (or in the middle), we'll default to swinging to whatever side the skyrise is on
		swingArmToSide(skyriseSide);
	}
}
void placeSkyrise(MHSkyrise skyrise){
	//First, let's make sure that the claw is unclenched
	SensorValue[skyriseClaw] = MHPneumaticPositionOpen;
	//Then, let's make sure the lift is at the bottom
	resetLift();
	//At this point, we always want the claw to be on the side of the new skyrise piece
	if(currentArmSide() != skyriseSide){
		toggleArmSide();
	}
	SensorValue[skyriseClaw] = MHPneumaticPositionClosed;
	liftForEncoderDistance(skyrise, MHMotorPowerMax);
	toggleArmSide();
	liftForEncoderDistance(MHSkyriseLiftInaccuracy, -MHMotorPowerMax);
	SensorValue[skyriseClaw] = MHPneumaticPositionOpen;
	resetLift();
}
//This *MUST* be called before an auton is run
void initSkyriseIntakeWithTeamColor(MHTeamColor color){
	roundColor = color;
	SensorValue[skyriseClaw] = MHPneumaticPositionOpen;
	if(color == MHTeamColorRed){
		skyriseSide = MHSkyriseArmRotationSideRightSide;
	}
	else{
		skyriseSide = MHSkyriseArmRotationSideLeftSide;
	}
}
MHSkyrise MHSkyriseForInt(int count){
	switch(count){
		case 1:
			return MHSkyriseOneSkyrise;
		case 2:
			return MHSkyriseTwoSkyrises;
		case 3:
			return MHSkyriseThreeSkyrises;
		case 4:
			return MHSkyriseFourSkyrises;
		case 5:
			return MHSkyriseFiveSkyrises;
		default:
			return MHSkyriseLiftInaccuracy;
	}
}
int intForMHSkyrise(MHSkyrise skyrise){
	switch(skyrise){
		case MHSkyriseOneSkyrise:
			return 1;
		case MHSkyriseTwoSkyrises:
			return 2;
		case MHSkyriseThreeSkyrises:
			return 3;
		case MHSkyriseFourSkyrises:
			return 4;
		case MHSkyriseFiveSkyrises:
			return 5;
		default:
			return MHSkyriseLiftInaccuracy;
	}
}
