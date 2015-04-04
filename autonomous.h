#pragma systemFile
#ifndef enums
//This file depends on enumerations.h
#include "enumerations.h"
#endif
#ifndef LCD
//This file also depends on lcd.h
#include "lcd.h"
#endif
MHSkyriseArmRotationSide skyriseSide;
MHTeamColor roundColor;
/////////////////////////////////////////////////////////////////////////////////////////
//**Reset encoders**/
/////////////////////////////////////////////////////////////////////////////////////////
void resetEncoders(){                        //Clears lift encoders
	nMotorEncoder[lmLift] = 0;
  nMotorEncoder[rbLift] = 0;
}
/////////////////////////////////////////////////////////////////////////////////////////
//**Basic**/
//
//Caveman-simple driving with nothing
/////////////////////////////////////////////////////////////////////////////////////////
void basicDrive(int leftPower, int rightPower){
	motor[lfDrive] = motor[lbDrive] = leftPower;
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
    	motor[lbDrive] = motor[lfDrive] = 0;
    }
    if(nMotorEncoder[rDrive] >= encoderCount){
     	motor[rDrive] = motor[rDrive] = 0;
    }
  }
  //Slow down near destination
	while(abs(nMotorEncoder[lbDrive]) < encoderCount && abs(nMotorEncoder[rDrive]) < encoderCount){
  	drive(power);
   	if(nMotorEncoder[lbDrive] >= encoderCount){
    	motor[lbDrive] = motor[lfDrive] = 0;
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
			motor[lbLift] = motor[lmLift] = motor[ltLift] =  motor[rtLift] = motor[rmLift] = motor[rbLift]  = 127;
		}
		else{
			motor[lbLift] = motor[lmLift] = motor[ltLift] =  motor[rtLift] = motor[rmLift] = motor[rbLift] = 0;
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
			motor[lbLift] = motor[lmLift] = motor[ltLift] = motor[rmLift] = motor[rbLift] = motor[rtLift] = -127;
		}
		else{
			motor[lbLift] = motor[lmLift] = motor[ltLift] = motor[rmLift] = motor[rbLift] = motor[rtLift] = 0;
			return;
		}
	}
}
void lift(int power, MHLiftDirection direction){
	motor[rtLift] = motor[rbLift] = motor[rmLift] = motor[lbLift] = motor[lmLift] = motor[ltLift] = abs(power) * direction;
}
void stopDriveSide(MHRobotSide side){
	 if(side == MHRobotSideRight){
	   motor[rDrive] = MHMotorPowerStop;
	 }
	 else if(side == MHRobotSideLeft){
	   motor[lfDrive] = motor[lbDrive] = MHMotorPowerStop;
	 }
	 else{
	   motor[rDrive] = motor[lfDrive] = motor[lbDrive] = MHMotorPowerStop;
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
	while((abs(nMotorEncoder[lmLift]) + abs(nMotorEncoder[rbLift])) / 2 < count){
		sprintf(first, "%d", abs(nMotorEncoder[lmLift]));
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
	liftForEncoderDistance(nMotorEncoder[lmLift], -MHMotorPowerMax);
}
void liftCube(MHLiftDirection direction){
	motor[cubeIntake] = MHMotorPowerMax * direction;
}
void liftCubeForTime(int time, MHLiftDirection direction){
	liftCube(direction);
	wait1Msec(time);
	liftCube(MHLiftDirectionStop);
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
void runAutonomousStyleForTeamColor(MHTeamColor color, MHAutonStyle auton){
	static bool shouldClear = true;
	int wallSide = 1;
	if(color == MHTeamColorBlue){
		wallSide *= -1;
	}
	int skyriseBaseSide = -wallSide;
	if((color == MHTeamColorRed || color == MHTeamColorBlue) && auton == MHAutonStyleSkyriseAuton){
		//Release the claw
		liftCubeForTime(MHTimeTenthSecond * 2, MHLiftDirectionDown);
		SensorValue[skyriseClaw] = MHPneumaticPositionOpen;
		//Grab the first skyrise
		resetLift();
		//motor[skyriseArm] = MHMotorPowerHalf * wallSide;
		wait1Msec(MHTimeOneSecond);
		//motor[skyriseArm] = MHMotorPowerStop;
		SensorValue[skyriseClaw] = MHPneumaticPositionClosed;
		wait1Msec(MHTimeOneSecond);
		//Place the skyrise
		liftForEncoderDistance(MHSkyriseOneSkyrise, MHMotorPowerMax);
		liftCubeForTime(MHTimeHalfSecond, MHLiftDirectionDown);
		//motor[skyriseArm] = MHMotorPowerHalf * skyriseBaseSide;
		wait1Msec(MHTimeOneSecond);
		resetLift();
		wait1Msec(MHTimeOneSecond);
		SensorValue[skyriseClaw] = MHPneumaticPositionOpen;
		//Grab the next skyrise
		//motor[skyriseArm] = MHMotorPowerHalf * wallSide;
		wait1Msec(MHTimeOneSecond * 2);
		SensorValue[skyriseClaw] = MHPneumaticPositionClosed;
		//Place the skyrise
		liftForEncoderDistance(MHSkyriseTwoSkyrises, MHMotorPowerMax);
		//motor[skyriseArm] = MHMotorPowerHalf * skyriseBaseSide;
		wait1Msec(MHTimeOneSecond);
		liftForEncoderDistance(MHSkyriseLiftInaccuracy, -MHMotorPowerMax);
		SensorValue[skyriseClaw] = MHPneumaticPositionOpen;
		//Reset the skyrise arm
		//motor[skyriseArm] = MHMotorPowerMax * wallSide;
		wait1Msec(MHTimeOneSecond);
		//motor[skyriseArm] = MHMotorPowerStop;
	}
	else if(auton == MHAutonStyleCubeAuton){
		liftForEncoderDistance(1000, MHMotorPowerMax);
		basicDrive(-MHMotorPowerMax, -MHMotorPowerMax);
		wait1Msec(MHTimeHalfSecond);
		stopDrive();
		liftCubeForTime(MHTimeOneSecond, MHLiftDirectionDown);
	}
	else if((color == MHTeamColorRed || color == MHTeamColorBlue) && auton == MHAutonStyleSkills){
		int diff = 0;
		shouldClear = false;
		runAutonomousStyleForTeamColor(MHTeamColorRed, MHAutonStyleSkyriseAuton);
		//Grab the third skyrise
		//motor[skyriseArm] = MHMotorPowerMax * wallSide;
		wait1Msec(MHTimeTenthSecond);
		SensorValue[skyriseClaw] = MHPneumaticPositionClosed;
		wait1Msec(MHTimeOneSecond);
		//Place the skyrise
		liftForEncoderDistance(MHSkyriseThreeSkyrises, MHMotorPowerMax);
		//motor[skyriseArm] = MHMotorPowerHalf * skyriseBaseSide;
		wait1Msec(MHTimeOneSecond);
		diff = nMotorEncoder[lmLift] - MHSkyriseLiftInaccuracy;
		liftForEncoderDistance(MHSkyriseLiftInaccuracy * 2, -MHMotorPowerMax);
		SensorValue[skyriseClaw] = MHPneumaticPositionOpen;
		liftForEncoderDistance(diff, -MHMotorPowerMax);
		//Count down for 5 seconds
		countDownForTime(MHTimeOneSecond * 5);
		//Drive forward to push stuff
		basicDrive(MHMotorPowerMax, MHMotorPowerMax);
		wait1Msec(MHTimeOneSecond * 5);
		//Return to the starting tile
		basicDrive(-MHMotorPowerMax, -MHMotorPowerMax);
		wait1Msec(MHTimeOneSecond * 6);
		stopDrive();
		//Give some time to reposition
		countDownForTime(MHTimeOneSecond * 5);
		//Drive forward one last time
		basicDrive(MHMotorPowerMax, MHMotorPowerMax);
		wait1Msec(MHTimeOneSecond * 5);
		//Retreat a little so as not to lose points
		basicDrive(-MHMotorPowerMax, -MHMotorPowerMax);
		wait1Msec(MHTimeOneSecond + MHTimeHalfSecond);
		stopDrive();
	}
	if(shouldClear){
		basicDrive(MHMotorPowerMax, MHMotorPowerMax);
		wait1Msec(MHTimeTenthSecond * 2);
		stopDrive();
	}
	shouldClear = true;
}
