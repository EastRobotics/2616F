#pragma systemFile
#ifndef enums
#define enums
#endif
//List of common motor powers for easy referencing
static const int MHLiftMaxHeight = 904;
typedef enum{
	MHMotorPowerStop = 0,
	//31 is about the minimum power you can assign to a motor before it begins to twitch
	MHMotorPowerMin = 31,
	//While a true half is 63.5, we're defining integer constants here, so we'll give it the high end
	MHMotorPowerHalf = 64,
	//For some reason, the maximum possible power for a VEX motor is 127. Don't ask me why.
	MHMotorPowerMax = 127
}MHMotorPower;
//The team color that the robot is on in a particualr match. Chosen in the pre_auton function
typedef enum{
	MHTeamColorNone,
	MHTeamColorAny,
	MHTeamColorRed,
	MHTeamColorBlue
}MHTeamColor;
//All the possible point values that the robot can score during the autonomous task. Chosen in the pre_auton function
typedef enum{
	MHAutonPointValue3 = 3,
	MHAutonPointValue5 = 5,
	//MHAutonValueNone is bridged toll-free to MHTeamColorNone, since they're the same thing
	MHAutonPointValueNone = MHTeamColorNone
}MHAutonPointValue;
//Easy reference to the types of automomous modes our robot can handle
typedef enum{
	MHAutonModeBlue3 = MHTeamColorBlue * MHAutonPointValue3,
	MHAutonModeBlue5 = MHTeamColorBlue * MHAutonPointValue5,
	MHAutonModeRed3 = MHTeamColorRed * MHAutonPointValue3,
	MHAutonModeRed5 = MHTeamColorRed * MHAutonPointValue5,
	//MHAutonModeNoAuton is bridged toll-free to MHAutonValueNone, because they're the same thing
	MHAutonModeNoAuton = MHAutonPointValueNone,
	MHAutonModeNoneSelected
}MHAutonMode;
//typedef to frequently used amounts of time
typedef enum{
	MHTimeOneMillisecond = 1,
	MHTimeTenthSecond = 100,
	MHTimeQuarterSecond = 250,
	MHTimeHalfSecond = 500,
	MHTimeOneSecond = 1000
}MHTime;
//Constant to define the power threshold where the motors will begin to twitch
static const int MHMotorTwitchThreshold = 30;
//Defines the side of the robot that something should take place on
typedef enum{
	MHRobotSideRight = 0,
	MHRobotSideLeft = 1,
	MHRobotSideFront = 2,
	MHRobotSideBack = 3,
}MHRobotSide;
typedef enum{
	MHLiftDirectionUp = -1,
	MHLiftDirectionDown = 1,
	//MHLiftDirectionStop is bridged toll-free to MHMotorPowerStop, because they're the same thing
	MHLiftDirectionStop = MHMotorPowerStop
}MHLiftDirection;
typedef enum{
	//Handily, normal C does not have a boolean type. In that language, 0 is false and anything else is true. Since ROBOTC is derived from C, the same logic can be used here
	MHPneumaticPositionClosed = 0,
	MHPneumaticPositionOpen = 1
}MHPneumaticPosition;
typedef enum{
	//These all are raw approximate encoder count values, for use in the liftForEncoderDistance function of autonomous.h
	MHSkyriseOneSkyrise = 700,
	MHSkyriseTwoSkyrises = 900,
	MHSkyriseThreeSkyrises = 1500,
	MHSkyriseFourSkyrises = 2000,
	MHSkyriseFiveSkyrises = 2900,
	MHSkyriseLiftInaccuracy = 200
}MHSkyrise;
typedef enum{
	//These are all raw approximate potentiometer values, for use in the swingArmToSide fuction of autonomous.h
	MHSkyriseArmRotationSideRightSide = 925,
	MHSkyriseArmRotationSideLeftSide = 2760,
	MHSkyriseArmRotationSideMiddle = 1850,
	MHSkyriseArmRotationSideOutOfBounds
}MHSkyriseArmRotationSide;
