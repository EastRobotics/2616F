//Make sure we're never redefining anything
#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__
//Prevent any unnecessary warnings
#pragma systemFile

//MARK: - Standalone Type Definitions

//Type to annotate a variable meant to represent a duration
typedef int MHDuration;

//MARK: - Game Mode Duration Constants

//The autonomous mode lasts 15 seconds
static const MHDuration MHAutonomousDuration = 15;
//The driver control mode lasts 1:45, or 105 seconds
static const MHDuration MHDriverControlDuration = 105;

//MARK: - Preprocessor Definitions

//Preprocessor definitions for vexRT manipulation
#define MHControllerJoystickLeftXAxis vexRT[Ch4]
#define MHControllerJoystickLeftYAxis vexRT[Ch3]
#define MHControllerJoystickRightXAxis vexRT[Ch1]
#define MHControllerJoystickRightYAxis vexRT[Ch2]
#define MHControllerDPadLeftButtonTop vexRT[Btn7U]
#define MHControllerDPadLeftButtonBottom vexRT[Btn7D]
#define MHControllerDPadLeftButtonLeft vexRT[Btn7L]
#define MHControllerDPadLeftButtonRight vexRT[Btn7R]
#define MHControllerDPadRightButtonTop vexRT[Btn8U]
#define MHControllerDPadRightButtonBottom vexRT[Btn8D]
#define MHControllerDPadRightButtonLeft vexRT[Btn8L]
#define MHControllerDPadRightButtonRight vexRT[Btn8R]
#define MHControllerShoulderLeftButtonTop vexRT[Btn5U]
#define MHControllerShoulderLeftButtonBottom vexRT[Btn5D]
#define MHControllerShoulderRightButtonTop vexRT[Btn6U]
#define MHControllerShoulderRightButtonBottom vexRT[Btn6D]

//MARK: - Enumerations

//Enumeration to define easy motor speeds
typedef enum _MHMotorPower{
  //To stop is to not move. Duh.
  MHMotorPowerStop = 0,
	//If you wanna stall the motors, it's safe to put it at a power of 30, but that's about the lowest it's safe to go
	MHMotorPowerStall = 30,
	//31 is about the minimum power you can assign to a motor before it begins to twitch
	MHMotorPowerMin = 31,
	//While a true half is 63.5, we're defining integer constants here, so we'll give it the high end
	MHMotorPowerHalf = 64,
	//For some reason, the maximum possible power for a VEX motor is 127. Don't ask me why.
	MHMotorPowerMax = 127
}MHMotorPower;
//Enumeration to define robot drive sides
typedef enum _MHDriveSide{
  //The left side of the drive, when the robot is facing away from you
  MHDriveSideLeft,
  //The right drive side, when the robot is facing away from you
  MHDriveSideRight
}MHDriveSide;
#endif