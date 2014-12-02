#pragma systemFile
//The maximum power for any VEX motor. Easily manipulated with math
static const int MHPowerMax = 127;
//The team color that the robot is on in a particualr match. Chosen in the pre_auton function
typedef enum{
	MHTeamColorRed,
	MHTeamColorBlue,
	MHTeamColorNone
}MHTeamColor;
//All the possible point values that the robot can score during the autonomous task. Chosen in the pre_auton function
typedef enum{
	MHAutonValue3,
	MHAutonValue5,
	//MHAutonValueNoAuton is bridged toll-free to MHTeamColorNone, since they're the same thing
	MHAutonValueNoAuton = MHTeamColorNone
}MHAutonValue;
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
