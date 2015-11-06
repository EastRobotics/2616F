//Make sure this file only gets #included once
#ifndef __BATTERY_H__
#define __BATTERY_H__
//Prevent any unnecessary warnings
#pragma systemFile
//Make sure this file only gets #included once
#pragma once

///////////////////////////////////////////////////////////////////////////////
//MARK: - Enumerations
///////////////////////////////////////////////////////////////////////////////

//Enumeration to enable easy referencing of individual batteries
typedef enum _MHBattery{
	MHBatteryMain,
	MHBatteryBackup
}MHBattery;

//Define all the functions declared above
#include "battery.c"
#endif
