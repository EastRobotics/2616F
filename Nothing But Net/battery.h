#pragma systemFile
#define VOLTAGE_THRESHOLD 1250
void displayLCDVoltageString(const int line);
void displayVoltage(int line, int position, int millivolts, bool leftAligned);
void LCDVoltageString(string *text, int batteryLevel);
void LCDVoltageLine(string *line);
void displayLCDVoltageString(int line){
	bLCDBacklight = false;
	clearLCDLine(line);
	int otherBatteryLevel = (float)BackupBatteryLevel * 1000 / 280;
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
	LCDVoltageString(&other, BackupBatteryLevel);
	const int backupLength = strlen(other);
	*line = primary;
	for(int i = 0; i < ((backupLength + strlen(primary)) - 4) / 2; ++i){
		*line += " ";
	}
	*line += "Back"
	for(int i = 0; i < 16 - (strlen(*line) + backupLength); ++i){
		*line += " ";
	}
	*line += other;
}
