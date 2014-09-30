/////////////////////////////////////////////////////////////////////////////////////////
//**Reset encoders**/
/////////////////////////////////////////////////////////////////////////////////////////
void    resetEncoders(){                        //Clears drive encoders
        nMotorEncoder[lfDrive] = 0;
        nMotorEncoder[rfDrive] = 0;
}
/////////////////////////////////////////////////////////////////////////////////////////
//**Basic**/
//
//Caveman-simple driving with nothing
/////////////////////////////////////////////////////////////////////////////////////////
void basicDrive(int leftPower, int rightPower){
        motor[lfDrive] = motor[lbDrive] = leftPower;
        motor[rfDrive] = motor[rbDrive] = rightPower;
}
/////////////////////////////////////////////////////////////////////////////////////////
//**Drive**/
//
//Simple driving with straighening but no stopping limit
/////////////////////////////////////////////////////////////////////////////////////////
void drive(int power){

        if(power != 0)          //Adds ability to use to use function to stop drive
        {
                basicDrive(power, power);
                //Compares left and right encoder values to straighten robot
                if(nMotorEncoder[lbDrive] == nMotorEncoder[rbDrive])
                {
                        basicDrive(power, power);
                }
                else if(nMotorEncoder[lbDrive] < nMotorEncoder[rbDrive])
                {
                        basicDrive(power, power-40);
                }
                else
                {
                        basicDrive(power-40,power);
                }

        }
        else    //Stops drive if power is zero
        {
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
                basicDrive(power, power);   //Drive robot at power
        }
        drive(0);       //Turn off after it has reached destination
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
                drive(power);   //Drive robot at power

                if(nMotorEncoder[lbDrive] >= encoderCount)
                        motor[lbDrive]=motor[lfDrive] = 0;

                if(nMotorEncoder[rbDrive] >= encoderCount)
                        motor[rbDrive] = motor[rfDrive] = 0;
        }

        //Slow down near destination
        while(abs(nMotorEncoder[lbDrive]) < encoderCount && abs(nMotorEncoder[rbDrive]) < encoderCount){
                drive(power);   //Drive robot at power

                if(nMotorEncoder[lbDrive] >= encoderCount)
                        motor[lbDrive]=motor[lfDrive] = 0;

                if(nMotorEncoder[rbDrive] >= encoderCount)
                        motor[rbDrive] = motor[rfDrive] = 0;
        }
        drive(0);       //Turn off after it has reached destination
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
void liftLift(int encoderCount)
{
	//int encoderAverage = (abs(nMotorEncoder[leftLiftBottom]) + abs(nMotorEncoder[rightLiftBottom]))/2;
	while(true) {
		if(abs(nMotorEncoder[rlLift]) < encoderCount) {
			motor[llLift] = motor[lmLift] = motor[ltLift] = motor[rlLift] = motor[rmLift] = motor[rtLift] = 127;
		} else {
			motor[llLift] = motor[lmLift] = motor[ltLift] = motor[rlLift] = motor[rmLift] = motor[rtLift] = 0;
			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
//**Lower the lift down**/
/////////////////////////////////////////////////////////////////////////////////////////
void lowerLift(int encoderCount)
{
	//int encoderAverage = (abs(nMotorEncoder[leftLiftBottom]) + abs(nMotorEncoder[rightLiftBottom]))/2;
	while(true) {
		if(abs(nMotorEncoder[rightLiftBottom]) > encoderCount) {
			motor[llLift] = motor[lmLift] = motor[ltLift] = motor[rlLift] = motor[rmLift] = motor[rtLift] = -127;
		} else {
			motor[llLift] = motor[lmLift] = motor[ltLift] = motor[rlLift] = motor[rmLift] = motor[rtLift] = 0;
			return;
		}
	}
}

void timeLift(int power, int time)
{
}

/////////////////////////////////////////////////////////////////////////////////////////
//**Time-based intake**
//
//Spins intake for designated time
/////////////////////////////////////////////////////////////////////////////////////////
void intake(int power, int time){
}
