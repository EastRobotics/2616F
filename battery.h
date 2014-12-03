#pragma systemFile
#define VOLTAGE_THRESHOLD 1250
void displayLCDVoltageString(int line);
void displayVoltage(int line, int position, int millivolts, bool leftAligned);
void LCDVoltageString(string *text, int batteryLevel);
void LCDVoltageLine(string *line);
void displayLCDVoltageString(int line){
	bLCDBacklight = true;
	clearLCDLine(line);
	int otherBatteryLevel = (float)SensorValue[otherBattery] * 1000 / 280;
	displayVoltage(line, 0, nImmediateBatteryLevel, true);
	displayVoltage(line, 11, otherBatteryLevel, false);
}
void displayVoltage(int line, int position, int millivolts, bool leftAligned){
	displayLCDPos(line, position);
	if(millivolts <= VOLTAGE_THRESHOLD){
		displayNextLCDString(leftAligned ? "None " : " None");
		return;
	}
	float volts = ((float)millivolts / 1000);
	string displayString;
	sprintf(displayString, "%1.2f", volts);
	displayNextLCDString(displayString);
	displayNextLCDChar('V');
}
void LCDVoltageString(string *text, int batteryLevel){
	if(batteryLevel <= VOLTAGE_THRESHOLD){
		*text = "None";
		return;
	}
	float volts = ((float)batteryLevel / 1000);
	sprintf(*text, "1.2%fV", volts);
	return;
}
void LCDVoltageLine(string *line){
	string primary;
	string other;
	LCDVoltageString(&primary, nImmediateBatteryLevel);
	LCDVoltageString(&other, SensorValue[otherBattery]);
	int length = strlen(primary) + strlen(other);
	switch(length){
		case 10:
			//Strings in ROBOTC must be added one at a time, because ROBOTC is stupid
			*line = primary + "      ";
			*line += other;
			return;
		case 9:
			*line = primary + "       ";
			*line += other;
			return;
		case 8:
			*line = primary + "        ";
			*line += other;
			return;
		default:
			*line = " Battery Error  ";
	}
}
