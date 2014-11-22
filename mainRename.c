#pragma config(Sensor, dgtl11, expander,       sensorDigitalIn)
#pragma config(Sensor, dgtl12, blockPneumatics, sensorDigitalOut)
#pragma config(Motor,  port1,           rtLift,        tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           lfDrive,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           lbDrive,       tmotorVex393_MC29, openLoop, encoderPort, None)
#pragma config(Motor,  port4,           llLift,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           rfDrive,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           rbDrive,       tmotorVex393_MC29, openLoop, encoderPort, None)
#pragma config(Motor,  port7,           rlLift,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           rmLift,        tmotorVex393_MC29, openLoop, reversed, encoderPort, None)
#pragma config(Motor,  port9,           ltLift,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          lmLift,        tmotorVex393_HBridge, openLoop, encoderPort, None)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
This file is the main link of the program, it has the button controls and specific autonomous instructions
*/

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#pragma platform(VEX)
//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)
#include "Vex_Competition_Includes.c"
//Uncomment the next line when programming the autonomous code
#include "AutonomousFunctionsRename.h"
#include "Selection.h"
#include "battery.h"
void lift(int power);
void pre_auton(){
	clearLCDLine(0);
	clearLCDLine(1);
	displayLCDVoltageString(0);
	displayLCDCenteredString(0, "This displayed");
}
task autonomous(){
	clearLCDLine(0);
	clearLCDLine(1);
	displayLCDCenteredString(0, "Hi");
	displayLCDVoltageString(1);
	/*
	//lift for 2 seconds
	motor[rtLift] = motor[rmLift] = motor[rlLift] = motor[ltLift] = motor[lmLift] = motor[llLift] = 127;
	wait1Msec(2000);
	//drive forward for .25 of a second
	motor[leftDriveFront]= motor[leftDriveBack] = motor[leftDriveMiddle] = motor[rightDriveBack] = motor[rightDriveFront] = motor[rightDriveMiddle] = 127;
	wait1Msec(250);
	//lower the lift for .5 of a second
	motor[leftLiftTop] = motor[leftLiftBottom] = motor[rightLiftTop] = motor[rightLiftBottom] = -127;
	wait1Msec(500);
	//drive backward for 1 second
	motor[leftDriveFront]= motor[leftDriveBack] = motor[leftDriveMiddle] = motor[rightDriveBack] = motor[rightDriveFront] = motor[rightDriveMiddle] = -127;
	wait1Msec(1000);
	//lower lift for 1.25 seconds and placing the skyrise in the holder
	motor[leftLiftTop] = motor[leftLiftBottom] = motor[rightLiftTop] = motor[rightLiftBottom] = -127;
	wait1Msec(1250);
	//lifting lift and releasing the skyrise section
	motor[leftLiftTop] = motor[leftLiftBottom] = motor[rightLiftTop] = motor[rightLiftBottom] = 127;
	wait1Msec(500);
	//drive forward for 1.25 seconds
	motor[leftDriveFront]= motor[leftDriveBack] = motor[leftDriveMiddle] = motor[rightDriveBack] = motor[rightDriveFront] = motor[rightDriveMiddle] = 127;
	wait1Msec(1250);
	//lift the lift to get the second skyrise section
	motor[leftLiftTop] = motor[leftLiftBottom] = motor[rightLiftTop] = motor[rightLiftBottom] = 127;
	wait1Msec(1000);
	//lower the lift to get the second skyrise
	motor[leftLiftTop] = motor[leftLiftBottom] = motor[rightLiftTop] = motor[rightLiftBottom] = -127;
	wait1Msec(750);
	//raise the lift with the skyrise section
	motor[leftLiftTop] = motor[leftLiftBottom] = motor[rightLiftTop] = motor[rightLiftBottom] = 127;
	wait1Msec(1000);
	//drive backward to the skyrise
	motor[leftDriveFront]= motor[leftDriveBack] = motor[leftDriveMiddle] = motor[rightDriveBack] = motor[rightDriveFront] = motor[rightDriveMiddle] = -127;
	wait1Msec(1000);
	//lower lift for .750 second and placing the skyrise in the holder
	motor[leftLiftTop] = motor[leftLiftBottom] = motor[rightLiftTop] = motor[rightLiftBottom] = -127;
	wait1Msec(750);
	//lifting lift and releasing the skyrise section
	motor[leftLiftTop] = motor[leftLiftBottom] = motor[rightLiftTop] = motor[rightLiftBottom] = 127;
	wait1Msec(500);




	//	liftLift(1550);
	//wait1Msec(300);
	//nMotorEncoder[leftLiftBottom] = 0;
	//	nMotorEncoder[rightLiftBottom] = 0;
	//	SensorValue[leftLiftIEM] = 0;
	//SensorValue[rightLifeIEM] = 0;

	//////Drive forward

	//encoderDrive(100, 500);
	//wait1Msec(300);
	//nMotorEncoder[leftDriveMiddle] = nMotorEncoder[rightDriveMiddle] = 0;

	//Release cube
	//	SensorValue[intakePneumatics] = 1;

	//LowerLift
	//lowerLift(-1000);
	//wait1Msec(300);
	//nMotorEncoder[leftLiftBottom] = nMotorEncoder[rightLiftBottom] = 0;

	//Grab cube
	//SensorValue[intakePneumatics] = 0;

	//Turn back
	//spin(-60, 800);
	//nMotorEncoder[leftDriveMiddle] = nMotorEncoder[rightDriveMiddle] = 0;

	//Drive forward
	//encoderDrive(60, 500);
	//nMotorEncoder[leftDriveMiddle] = nMotorEncoder[rightDriveMiddle] = 0;

	//Lift lift
	//liftLift(2550);
	//wait1Msec(300);
	//nMotorEncoder[leftLiftBottom] = nMotorEncoder[rightLiftBottom] = 0

	//Release cube
	//SensorValue[intakePneumatics] = 1;
	*/
}

task usercontrol(){
	// User control code here, inside the loop
	bool leftDriveShouldStop;
	bool rightDriveShouldStop;
	while(true){
		//Bogdan Drive
		if(abs(vexRT[Ch3]) <= 30){
			leftDriveShouldStop = true;
		}
		else{
			leftDriveShouldStop = false;
		}
		if(abs(vexRT[Ch2]) <= 30){
			rightDriveShouldStop = true;
		}
		else{
			rightDriveShouldStop = false;
		}
		if(leftDriveShouldStop){
			motor[lfDrive] = motor[lbDrive] = 0;
		}
		else{
			motor[lfDrive] = motor[lbDrive] = vexRT[Ch3];
		}
		if(rightDriveShouldStop){
			motor[rfDrive] = motor[rbDrive] = 0;
		}
		else{
			motor[rfDrive] = motor[rbDrive] = vexRT[Ch2];
		}
		//Lift
		if(vexRT[Btn6U]){//using the lift function, this says run at full speed when 6U is pressed
			lift(127);
		}
		else if (vexRT[Btn6D]){//Reverse direction
			lift(-127);
		}
		else{//If neither button is pressed it won't move, it must be set to zero or it'll keep going after being pressed
			lift(0);
		}
		//Pneumatics
		if(vexRT[Btn7R]){
			SensorValue[blockPneumatics] = true;
		}
		if(vexRT[Btn7D]){
			SensorValue[blockPneumatics] = false;
		}
	}
}
void lift(int power){
	motor[ltLift] = motor[lmLift] = motor[llLift] = motor[rtLift] = motor[rmLift] = motor[rlLift] = power;
}
