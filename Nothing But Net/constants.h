//Make sure we're never redefining anything
#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__
//Prevent any unnecessary warnings
#pragma systemFile

///////////////////////////////////////////////////////////////////////////////
//MARK: - Standalone Type Definitions
///////////////////////////////////////////////////////////////////////////////

//Type to annotate a variable meant to represent a duration
typedef int MHDuration;

///////////////////////////////////////////////////////////////////////////////
//MARK: - Game Mode Duration Constants
///////////////////////////////////////////////////////////////////////////////

//The autonomous mode lasts 15 seconds
static const MHDuration MHAutonomousDuration = 15;
//The driver control mode lasts 1:45, or 105 seconds
static const MHDuration MHDriverControlDuration = 105;

///////////////////////////////////////////////////////////////////////////////
//MARK: - Preprocessor Definitions
///////////////////////////////////////////////////////////////////////////////

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
#endif