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
		if(SensorValue[armAngle] <= side + 100 && SensorValue[armAngle] >= side - 100){
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
		 displayLCDCenteredString(0, "Moving arm");
		 while(currentArmSide() != side){
		   motor[skyriseArm] = MHMotorPowerMax * direction;
		 }
		 displayLCDCenteredString(1, "Arm moved");
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
MHSkyrise MHSkyriseForInt(int count){
	if(count >= 1 && count <= 5){
		return skyrises[count - 1];
	}
	else{
		return MHSkyriseLiftInaccuracy;
	}
}
int intForMHSkyrise(MHSkyrise skyrise){
	for(int i = 0; i < (sizeof(skyrises)/sizeof(skyrises[0])); i++){
		if(skyrise == skyrises[i]){
			return i;
		}
	}
	return NULL;
}
//Right now, this is timing-based, which is far from ideal. Hopefully, I can use the potentiometer in the future
void placeSkyrise(MHSkyrise skyrise, MHTeamColor matchColor){
	if(matchColor == MHTeamColorRed || matchColor == MHTeamColorBlue){
		int wallSide = 1;
		if(matchColor == MHTeamColorBlue){
			wallSide *= -1;
		}
		int skyriseBaseSide = -wallSide;
		static int invocations = 1;
		//First, let's make sure that the claw is unclenched
		SensorValue[skyriseClaw] = MHPneumaticPositionOpen;
		//Then, let's make sure the lift is at the bottom
		resetLift();
		//Grab the skyrise
		motor[skyriseArm] = MHMotorPowerMax * wallSide;
		//If this is the first time we're running, we only need to take half as long to move to the wall
		if(invocations == 1){
			wait1Msec(MHTimeHalfSecond);
		}
		else{
			wait1Msec(MHTimeOneSecond);
		}
		motor[skyriseArm] = MHMotorPowerStop;
		SensorValue[skyriseClaw] = MHPneumaticPositionClosed;
		wait1Msec(MHTimeOneSecond);
		//Actually place the skyrise
		liftForEncoderDistance(skyrise, MHMotorPowerMax);
		//If this is the first time we've run, we want to make sure the cube intake is out of the way, and ready to use in driver control
		if(invocations == 1){
			liftCubeForTime(MHTimeTenthSecond * 3, MHLiftDirectionDown);
		}
		motor[skyriseArm] = MHMotorPowerHalf * skyriseBaseSide;
		wait1Msec(MHTimeOneSecond);
		liftForEncoderDistance(MHSkyriseLiftInaccuracy, -MHMotorPowerMax);
		//If this is still the first time we're running, we need to just continue to the bottom
		if(intForMHSkyrise(skyrise) == 1){
			resetLift();
		}
		wait1Msec(MHTimeHalfSecond);
		SensorValue[skyriseClaw] = MHPneumaticPositionOpen;
		invocations++;
	}
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
void runAutonomousForTeamColor(MHTeamColor color){
	if(color == MHTeamColorRed || color == MHTeamColorBlue){
		int wallSide = 1;
		if(color == MHTeamColorBlue){
			wallSide *= -1;
		}
		int skyriseBaseSide = -wallSide;
		//Release the claw
		liftCubeForTime(MHTimeTenthSecond * 2, MHLiftDirectionDown);
		SensorValue[skyriseClaw] = MHPneumaticPositionOpen;
		//Grab the first skyrise
		resetLift();
		motor[skyriseArm] = MHMotorPowerHalf * wallSide;
		wait1Msec(MHTimeHalfSecond);
		motor[skyriseArm] = MHMotorPowerStop;
		SensorValue[skyriseClaw] = MHPneumaticPositionClosed;
		wait1Msec(MHTimeOneSecond);
		//Place the skyrise
		liftForEncoderDistance(MHSkyriseOneSkyrise, MHMotorPowerMax);
		liftCubeForTime(MHTimeTenthSecond * 7, MHLiftDirectionDown);
		motor[skyriseArm] = MHMotorPowerHalf * skyriseBaseSide;
		wait1Msec(MHTimeOneSecond);
		resetLift();
		wait1Msec(MHTimeHalfSecond);
		SensorValue[skyriseClaw] = MHPneumaticPositionOpen;
		//Grab the next skyrise
		motor[skyriseArm] = MHMotorPowerHalf * wallSide;
		wait1Msec(MHTimeOneSecond);
		motor[skyriseArm] = MHMotorPowerStop;
		wait1Msec(MHTimeHalfSecond);
		SensorValue[skyriseClaw] = MHPneumaticPositionClosed;
		//Place the skyrise
		liftForEncoderDistance(MHSkyriseTwoSkyrises, MHMotorPowerMax);
		motor[skyriseArm] = MHMotorPowerHalf * skyriseBaseSide;
		wait1Msec(MHTimeOneSecond);
		liftForEncoderDistance(MHSkyriseLiftInaccuracy, -MHMotorPowerMax);
		SensorValue[skyriseClaw] = MHPneumaticPositionOpen;
		//Grab the 3rd skyrise
		resetLift();
		motor[skyriseArm] = MHMotorPowerMax * wallSide;
		wait1Msec(MHTimeOneSecond);
		motor[skyriseArm] = MHMotorPowerStop;
		SensorValue[skyriseClaw] = MHPneumaticPositionClosed;
		//Place the skyrise
		liftForEncoderDistance(MHSkyriseThreeSkyrises, MHMotorPowerMax);
		motor[skyriseArm] = MHMotorPowerHalf * skyriseBaseSide;
		wait1Msec(MHTimeOneSecond);
		liftForEncoderDistance(MHSkyriseLiftInaccuracy * 1.5, -MHMotorPowerMax);
		SensorValue[skyriseClaw] = MHPneumaticPositionOpen;
		//Reset the skyrise arm
		resetLift();
		motor[skyriseArm] = MHMotorPowerMax * wallSide;
		wait1Msec(MHTimeOneSecond);
		motor[skyriseArm] = MHMotorPowerStop;
	}
}
