/*
This file is the function library, the functions are basically
short cuts to control parts of the robot
*/
//nmotorencoder

void lift(int power){              //this function works the same way, using the input power to control the lift
	motor[ltLift] = motor[lmLift] = motor[llLift] = motor[rtLift] = motor[rmLift] = motor[rlLift] = power;
}
