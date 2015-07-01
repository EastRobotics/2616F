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
#define MHControllerJoystickLeftXAxisValue vexRT[Ch4]
#define MHControllerJoystickLeftYAxisValue vexRT[Ch3]
#define MHControllerJoystickRightXAxValue vexRT[Ch1]
#define MHControllerJoystickRightYAxValue vexRT[Ch2]
#define MHControllerDPadLeftButtonTopPressed vexRT[Btn7U]
#define MHControllerDPadLeftButtonBottomPressed vexRT[Btn7D]
#define MHControllerDPadLeftButtonLeftPressed vexRT[Btn7L]
#define MHControllerDPadLeftButtonRightPressed vexRT[Btn7R]
#define MHControllerDPadRightButtonTopPressed vexRT[Btn8U]
#define MHControllerDPadRightButtonBottomPressed vexRT[Btn8D]
#define MHControllerDPadRightButtonLeftPressed vexRT[Btn8L]
#define MHControllerDPadRightButtonRightPressed vexRT[Btn8R]
#define MHControllerShoulderLeftButtonTopPressed vexRT[Btn5U]
#define MHControllerShoulderLeftButtonBottomPressed vexRT[Btn5D]
#define MHControllerShoulderRightButtonTopPressed vexRT[Btn6U]
#define MHControllerShoulderRightButtonBottomPressed vexRT[Btn6D]
#endif