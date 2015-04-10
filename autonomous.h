#pragma systemFile
#ifndef enums
//This file depends on enumerations.h
#include "enumerations.h"
#endif
#ifndef LCD
//This file also depends on lcd.h
#include "lcd.h"
#endif
MHRotationDirection initialSkyriseRotationDirection;
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
void liftToPositionWithPower(int value, int power){
	//Up is negative, down is positive
	if(value == (int)MHLiftPositionCurrentPosition){
		value = SensorValue[rLiftPotentiometer];
	}
	MHLiftDirection liftDirection;
	if(value > SensorValue[rLiftPotentiometer]){
		liftDirection = MHLiftDirectionDown;
	}
	else if(value < SensorValue[rLiftPotentiometer]){
		liftDirection = MHLiftDirectionUp;
	}
	else{
		liftDirection = MHLiftDirectionStop;
	}
	displayLCDCenteredString(0, "Lifting...");
	while(SensorValue[rLiftPotentiometer] != value){
		lift(power, liftDirection);
	}
	lift(MHMotorPowerStop, MHLiftDirectionStop);
}
void liftToPosition(int value){
	liftToPositionWithPower(value, MHMotorPowerMax);
}
void resetLift(){
	liftToPosition(MHLiftPositionBottom);
}
void liftForPotentiometerDistanceInDirectionWithPower(int distance, MHLiftDirection direction, int power){
	int position = MHLiftPositionCurrentPosition;
	if(direction == MHLiftDirectionUp && SensorValue[rLiftPotentiometer] - distance < (int)MHLiftPositionTop){
		position = MHLiftPositionTop;
	}
	else if(direction == MHLiftDirectionDown && SensorValue[rLiftPotentiometer] + distance > (int)MHLiftPositionBottom){
		position = MHLiftPositionBottom;
	}
	else{
		position = SensorValue[rLiftPotentiometer] + (distance * direction);
	}
	liftToPositionWithPower(position, power);
}
void liftForPotentiometerDistanceInDirection(int distance, MHLiftDirection direction){
	liftForPotentiometerDistanceInDirectionWithPower(distance, direction, MHMotorPowerMax);
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
int trueNorth = 0;
void resetGyro(){
	trueNorth += (trueNorth - SensorValue[turningGyro]);
	SensorValue[turningGyro] = 0;
}
void rotate(int power, MHRotationDirection direction){
	basicDrive(power * direction, power * (-direction));
}
//EXPERIMENTAL: Probably won't work, don't use. For research purposes only
void rotateToFaceDirectionWithPower(int destination, int power){
	destination = abs(destination);
	int currentValue = SensorValue[turningGyro];
	int clockwise = MHRotationDistanceNone;
	int counterClockwise = MHRotationDistanceNone;
	MHRotationDirection rotationDirection = MHRotationDirectionNoRotation;
	if(destination < currentValue){
		clockwise = destination + (MHRotationDistanceFullTurn - currentValue);
		counterClockwise = currentValue - destination;
	}
	else if(destination > currentValue){
		clockwise = destination - currentValue;
		counterClockwise = currentValue + (MHRotationDistanceFullTurn - destination);
	}
	if(clockwise < counterClockwise){
		rotationDirection = MHRotationDirectionCounterClockwise;
	}
	else if(clockwise > counterClockwise){
		rotationDirection = MHRotationDirectionClockwise;
	}
	while(SensorValue[turningGyro] != destination){
		rotate(power, rotationDirection);
	}
	rotate(MHMotorPowerStop, MHRotationDirectionNoRotation);
}
//EXPERIMENTAL: Same as above. Botttom line: don't use it
void rotateToFaceDirection(int direction){
	rotateToFaceDirectionWithPower(direction, MHMotorPowerMax);
}
void rotateDistanceInDirectionWithPower(int distance, MHRotationDirection direction, int power){
	resetGyro();
	distance = abs(distance);
	if(distance > SensorFullCount[turningGyro]){
		SensorFullCount[turningGyro] = distance;
	}
	while(abs(SensorValue[turningGyro]) < distance){
		rotate(power, direction);
	}
	stopDrive();
	SensorFullCount[turningGyro] = MHRotationDistanceFullTurn;
}
void rotateDistanceInDirection(int distance, MHRotationDirection direction){
	int correction = MHRotationDistanceTenDegrees * 1.5;
	if(distance > correction){
		distance -= correction;
	}
	rotateDistanceInDirectionWithPower(distance, direction, MHMotorPowerMax);
}
//This *MUST* be called before an auton is run
void initAutonomousWithTeamColor(MHTeamColor color){
	roundColor = color;
	SensorValue[skyriseClaw] = MHPneumaticPositionClosed;
	if(color == MHTeamColorRed){
		initialSkyriseRotationDirection = MHRotationDirectionClockwise;
	}
	else{
		initialSkyriseRotationDirection = MHRotationDirectionCounterClockwise;
	}
}
void runAutonomousStyleForTeamColor(MHTeamColor color, MHAutonStyle auton){
	SensorValue[cubeIntake] = MHPneumaticPositionOpen;
	if(auton == MHAutonStyleCubeAuton){
		MHRotationDirection spinDirection;
		if(color == MHTeamColorRed){
			spinDirection = MHRotationDirectionCounterClockwise;
		}
		else if(color == MHTeamColorBlue){
			spinDirection = MHRotationDirectionClockwise;
		}
		else{
			spinDirection = MHRotationDirectionNoRotation;
		}
		liftToPosition(MHLiftPositionLowPost);
		basicDrive(MHMotorPowerMax, MHMotorPowerMax);
		wait1Msec(MHTimeHalfSecond - 25);
		stopDrive();
		resetLift();
		wait1Msec(MHTimeTenthSecond);
		liftToPosition(MHLiftPositionBottom - 10);
		basicDrive(MHMotorPowerMax, MHMotorPowerMax);
		wait1Msec(MHTimeHalfSecond + MHTimeQuarterSecond);
		stopDrive();
		liftToPosition(MHLiftPositionTop);
		rotateDistanceInDirection(MHRotationDistanceQuarterRotation, spinDirection);
		basicDrive(MHMotorPowerMax, MHMotorPowerMax);
		wait1Msec(MHTimeHalfSecond);
		stopDrive();
		wait1Msec(MHTimeHalfSecond);
		//basicDrive(-MHMotorPowerMax, -MHMotorPowerMax);
		//wait1Msec(MHTimeTenthSecond * 1.5);
		//stopDrive();
		liftToPosition(MHLiftPositionMiddlePost);
		SensorValue[cubeIntake] = MHPneumaticPositionClosed;
		wait1Msec(MHTimeHalfSecond);
		liftToPosition(MHLiftPositionTop);
		basicDrive((-100), (-100));
		wait1Msec(MHTimeHalfSecond);
		stopDrive();
		liftToPosition(MHLiftPositionBottom);
		SensorValue[skyriseClaw] = MHPneumaticPositionOpen;
		SensorValue[cubeIntake] = MHPneumaticPositionOpen;
	}
	else if(auton == MHAutonStyleSkyriseAuton){
		SensorValue[skyriseClaw] = MHPneumaticPositionOpen;
		basicDrive(MHMotorPowerMax, MHMotorPowerMax);
		wait1Msec(MHTimeTenthSecond);
		stopDrive();
		wait1Msec(MHTimeHalfSecond);
		SensorValue[skyriseClaw] = MHPneumaticPositionClosed;
		liftToPosition(MHSkyriseOneSkyrise);
		wait1Msec(MHTimeHalfSecond);
		rotateDistanceInDirection(MHRotationDistanceQuarterRotation / 2, MHRotationDirectionCounterClockwise);
		resetLift();
		SensorValue[skyriseClaw] = MHPneumaticPositionOpen;
	}
}
