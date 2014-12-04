#pragma systemFile
//List of common motor powers for easy referencing
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
	MHTeamColorRed,
	MHTeamColorBlue,
	MHTeamColorNone,
	MHTeamColorAny
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
	MHAutonModeNoAuton = MHAutonPointValueNone
}MHAutonMode;
//typedef to frequently used amounts of time
typedef enum{
	MHTimeOneMillisecond = 1,
	MHTimeTenthSecond = 100,
	MHTimeQuarterSecond = 250,
	MHTimeHalfSecond = 500,
	MHTimeOneSecond = 1000
}MHTime;
//Map of the possible LCD button combinations to make them easy to reference
typedef enum{
	MHLCDButtonLeft = 1,
	MHLCDButtonCenter = 2,
	MHLCDButtonRight = 4,
	MHLCDButtonLeftCenter = 3,
	MHLCDButtonLeftRight = 5,
	MHLCDButtonCenterRight = 6,
	MHLCDButtonAll = 7
}MHLCDButton;
