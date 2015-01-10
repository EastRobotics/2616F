#pragma systemFile
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
 	motor[rmDrive] = motor[rbDrive] = rightPower;
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
    if(nMotorEncoder[lbDrive] == nMotorEncoder[rbDrive]){
    	basicDrive(power, power);
    }
    else if(nMotorEncoder[lbDrive] < nMotorEncoder[rbDrive]){
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
	while(abs(nMotorEncoder[lbDrive]) < encoderCount && abs(nMotorEncoder[rbDrive]) < encoderCount - 300){
		//Drive robot at power
  	drive(power);
    if(nMotorEncoder[lbDrive] >= encoderCount){
    	motor[lbDrive] = motor[lmDrive] = 0;
    }
    if(nMotorEncoder[rbDrive] >= encoderCount){
     	motor[rbDrive] = motor[rmDrive] = 0;
    }
  }
  //Slow down near destination
	while(abs(nMotorEncoder[lbDrive]) < encoderCount && abs(nMotorEncoder[rbDrive]) < encoderCount){
  	drive(power);
   	if(nMotorEncoder[lbDrive] >= encoderCount){
    	motor[lbDrive] = motor[lmDrive] = 0;
    }
    if(nMotorEncoder[rbDrive] >= encoderCount){
    	motor[rbDrive] = motor[rmDrive] = 0;
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
	//if(direction == MHLiftDirectionUp){
		//if(speed > 82){
			//motor[lbLift] = motor[lfLift] = speed - 52;
		//}
		//else{
			//motor[lbLift] = motor[lfLift] = MHMotorTwitchThreshold;
		//}
	//}
	//else if(direction == MHLiftDirectionDown){
		//if(speed > 72){
			//motor[lbLift] = motor[lfLift] = -speed + 42;
		//}
		//else{
			//motor[lbLift] = motor[lfLift] = -MHMotorTwitchThreshold;
		//}
	//}
	//else if(direction == MHLiftDirectionStop){
		//motor[lbLift] = motor[lfLift] = MHMotorPowerStop;
	//}
}
void stopDrive(MHRobotSide side){
	 if(side == MHRobotSideRight){
	   motor[rmDrive] = motor[rbDrive] = MHMotorPowerStop;
	 }
	 else if(side == MHRobotSideLeft){
	   motor[lmDrive] = motor[lbDrive] = MHMotorPowerStop;
	 }
	 else{
	   motor[rmDrive] = motor[rbDrive] = motor[lmDrive] = motor[lbDrive] = MHMotorPowerStop;
	 }
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
void liftCube(MHMotorPower speed, MHLiftDirection direction){
	motor[cubeIntake] = speed * -direction;
}
