//Make sure we're never redefining anything
#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
//Prevent any unnecessary warnings
#pragma systemFile

///////////////////////////////////////////////////////////////////////////////
//MARK: - Controller Enumerations
///////////////////////////////////////////////////////////////////////////////

typedef enum _MHControl{
	MHControlJoystickRightXAxis = Ch1,
	MHControlJoystickPartnerRightXAxis = Ch1Xmtr2,
	MHControlJoystickRightYAxis = Ch2,
	MHControlJoystickPartnerRightYAxis = Ch2Xmtr2,
	MHControlJoystickLeftXAxis = Ch4,
	MHControlJoystickPartnerLeftXAxis = Ch4Xmtr2,
	MHControlJoystickLeftYAxis = Ch3,
	MHControlJoystickPartnerLeftYAxis = Ch3Xmtr2,
	MHControlButtonShoulderLeftTop = Btn5U,
	MHControlButtonPartnerShoulderLeftTop = Btn5UXmtr2,
	MHControlButtonShoulderLeftBottom = Btn5D,
	MHControlButtonPartnerShoulderLeftBottom = Btn5DXmtr2,
	MHControlButtonShoulderRightTop = Btn6U,
	MHControlButtonPartnerShoulderRightTop = Btn6UXmtr2,
	MHControlButtonShoulderRightBottom = Btn6D,
	MHControlButtonPartnerShoulderRightBottom = Btn6DXmtr2,
	MHControlButtonLeftDPadUp = Btn7U,
	MHControlButtonPartnerLeftDPadUp = Btn7UXmtr2,
	MHControlButtonLeftDPadDown = Btn7D,
	MHControlButtonPartnerLeftDPadDown = Btn7DXmtr2,
	MHControlButtonLeftDPadLeft = Btn7L,
	MHControlButtonPartnerLeftDPadLeft = Btn7LXmtr2,
	MHControlButtonLeftDPadRight = Btn7R,
	MHControlButtonPartnerLeftDPadRight = Btn7RXmtr2,
	MHControlButtonRightDPadUp = Btn8U,
	MHControlButtonPartnerRightDPadUp = Btn8UXmtr2,
	MHControlButtonRightDPadDown = Btn8D,
	MHControlButtonPartnerRightDPadDown = Btn8DXmtr2,
	MHControlButtonRightDPadLeft = Btn8L,
	MHControlButtonPartnerRightDPadLeft = Btn8LXmtr2,
	MHControlButtonRightDPadRight = Btn8R,
	MHControlButtonPartnerRightDPadRight = Btn8RXmtr2
}MHControl;

typedef enum _MHJoystick{
	MHJoystickLeftYAxis = MHControlJoystickLeftYAxis,
	MHJoystickPartnerLeftYAxis = MHControlJoystickPartnerLeftYAxis,
	MHJoystickLeftXAxis = MHControlJoystickLeftXAxis,
	MHJoystickPartnerLeftXAxis = MHControlJoystickPartnerLeftXAxis,
	MHJoystickRightYAxis = MHControlJoystickRightYAxis,
	MHJoystickPartnerRightYAxis = MHControlJoystickPartnerRightYAxis,
	MHJoystickRightXAxis = MHControlJoystickRightXAxis,
	MHJoystickPartnerRightXAxis = MHControlJoystickPartnerRightXAxis
}MHJoystick;
