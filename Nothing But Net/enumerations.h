//Make sure we're never redefining anything
#ifndef __ENUM_H__
#define __ENUM_H__
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
//Enumeration to define lines on the LCD
typedef enum _MHLCDLine{
  //Represents the top line on a VEX LCD screen
  MHLCDLineTop = 0,
  //Represents the bottom line of a VEX LCD
  MHLCDLineBottom = 1
}MHLCDLine;
#endif