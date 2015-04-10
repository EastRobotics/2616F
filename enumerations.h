#pragma systemFile
#ifndef enums
#define enums
#endif
//List of common motor powers for easy referencing
static const int MHLiftMaxHeight = 904;
typedef enum{
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
//The team color that the robot is on in a particualr match. Chosen in the pre_auton function
typedef enum{
	MHTeamColorNone,
	MHTeamColorAny,
	MHTeamColorRed,
	MHTeamColorBlue
}MHTeamColor;
//All the possible point values that the robot can score during the autonomous task. Chosen in the pre_auton function
typedef enum{
	MHAutonStyleOnePoint = 1,
	MHAutonStyleCubeAuton = 3,
	MHAutonStyleSkyriseAuton = 12,
	MHAutonStyleSkills = 30,
	//MHAutonValueNone is bridged toll-free to MHTeamColorNone, since they're the same thing
	MHAutonStyleNoAuton = MHTeamColorNone
}MHAutonStyle;
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
	MHPneumaticPositionClosed = 1,
	MHPneumaticPositionOpen = 0
}MHPneumaticPosition;
typedef enum{
	//These all are raw approximate encoder count values, for use in the liftForEncoderDistance function of autonomous.h
	MHSkyriseOneSkyrise = 900,
	MHSkyriseTwoSkyrises = 1100,
	MHSkyriseThreeSkyrises = 1700,
	MHSkyriseFourSkyrises = 2200,
	MHSkyriseFiveSkyrises = 3100,
	MHSkyriseLiftInaccuracy = 400
}MHSkyrise;
//In a couple places, it's useful to have all of the above in an array, so they can be referenced by index, and not raw value
static const MHSkyrise skyrises[5] = {MHSkyriseOneSkyrise, MHSkyriseTwoSkyrises, MHSkyriseThreeSkyrises, MHSkyriseFourSkyrises, MHSkyriseFiveSkyrises};
//Constants to designate which direction the robot should rotate
typedef enum{
	MHRotationDirectionClockwise = 1,
	MHRotationDirectionCounterClockwise = -1,
	MHRotationDirectionNoRotation = 0
}MHRotationDirection;
//Constants to define different signifcant points in the lift in potentiometer values
typedef enum{
	MHLiftPositionCurrentPosition = (-1),
	MHLiftPositionTop = 0,
	MHLiftPositionLowPost = 1100,
	MHLiftPositionBottom = 1620
}MHLiftPosition;
//Constants to define positions for the turning gyroscope
typedef enum{
	MHRotationDistanceNone = 0,
	MHRotationDistanceTenthDegree = 1,
	MHRotationDistanceOneDegree = 10,
	MHRotationDistanceTenDegrees = 100,
	MHRotationDistanceHundredDegrees = 1000,
	MHRotationDistanceQuarterRotation = 900,
	MHRotationDistanceHalfRotation = 1800,
	MHRotationDistanceFullTurn = 3600
}MHRotationDistance;
