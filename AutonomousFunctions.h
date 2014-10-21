/////////////////////////////////////////////////////////////////////////////////////////
//**Reset encoders**/
/////////////////////////////////////////////////////////////////////////////////////////
void    resetEncoders(){                        //Clears drive encoders
        nMotorEncoder[leftDriveMiddle] = 0;
        nMotorEncoder[rightDriveMiddle] = 0;
}
/////////////////////////////////////////////////////////////////////////////////////////
//**Basic**/
//
//Caveman-simple driving with nothing
/////////////////////////////////////////////////////////////////////////////////////////
void basicDrive(int leftPower, int rightPower){
        motor[leftDriveFront]=motor[leftDriveMiddle]=motor[leftDriveBack] = leftPower;
        motor[rightDriveFront] = motor[rightDriveMiddle] = motor[rightDriveBack] = rightPower;
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
                if(nMotorEncoder[leftDriveMiddle] == nMotorEncoder[rightDriveMiddle])
                {
                        basicDrive(power, power);
                }
                else if(nMotorEncoder[leftDriveMiddle] < nMotorEncoder[rightDriveMiddle])
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

        while(abs(nMotorEncoder[leftDriveMiddle]) < encoderCount){
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

        while(abs(nMotorEncoder[leftDriveMiddle]) < encoderCount && abs(nMotorEncoder[rightDriveMiddle]) < encoderCount - 300){
                drive(power);   //Drive robot at power

                if(nMotorEncoder[leftDriveMiddle] >= encoderCount)
                        motor[leftDriveFront]=motor[leftDriveMiddle] = motor[leftDriveBack] = 0;

                if(nMotorEncoder[rightDriveMiddle] >= encoderCount)
                        motor[rightDriveFront] = motor[rightDriveMiddle] = motor[rightDriveBack] = 0;
        }

        //Slow down near destination
        while(abs(nMotorEncoder[leftDriveMiddle]) < encoderCount && abs(nMotorEncoder[rightDriveMiddle]) < encoderCount){
                drive(power);   //Drive robot at power

                if(nMotorEncoder[leftDriveMiddle] >= encoderCount)
                        motor[leftDriveFront]=motor[leftDriveMiddle] = motor[leftDriveBack] = 0;

                if(nMotorEncoder[rightDriveMiddle] >= encoderCount)
                        motor[rightDriveFront] = motor[rightDriveMiddle] = motor[rightDriveBack] = 0;
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
                while(abs(nMotorEncoder[leftDriveMiddle]) < encoderCount){
                        basicDrive(power, -power);
                }
        }
        else{
                while(abs(nMotorEncoder[leftDriveMiddle]) < encoderCount){
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
                while(abs(nMotorEncoder[leftDriveMiddle]) < encoderCount){
                        basicDrive(power, -25);
                }
        }
        else{
                while(abs(nMotorEncoder[leftDriveMiddle]) < encoderCount){
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
		if(abs(nMotorEncoder[rightLiftBottom]) < encoderCount) {
			motor[leftLiftBottom] = motor[leftLiftTop] = motor[rightLiftBottom] = motor[rightLiftTop] = 127;
		} else {
			motor[leftLiftBottom] = motor[leftLiftTop] = motor[rightLiftBottom] = motor[rightLiftTop] = 0;
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
			motor[leftLiftBottom] = motor[leftLiftTop] = motor[rightLiftBottom] = motor[rightLiftTop] = -127;
		} else {
			motor[leftLiftBottom] = motor[leftLiftTop] = motor[rightLiftBottom] = motor[rightLiftTop] = 0;
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
