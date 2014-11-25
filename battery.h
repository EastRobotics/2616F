#pragma systemFile
#define VOLTAGE_THRESHOLD 1250
void displayLCDVoltageString(int line);
void displayVoltage(int line, int position, int millivolts, bool leftAligned);
void displayLCDVoltageString(int line){
	bLCDBacklight = true;
	clearLCDLine(line);
	int otherBatteryLevel = (float)SensorValue[otherBattery] * 1000 / 280;
	displayVoltage(1, 0, nImmediateBatteryLevel, true);
	displayVoltage(1, 11, otherBatteryLevel, false);
}
void displayVoltage(int line, int position, int millivolts, bool leftAligned){
	displayLCDPos(line, position);

	if (millivolts <= VOLTAGE_THRESHOLD) {
		displayNextLCDString(leftAligned ? "None " : " None");
		return;
	}

	float volts = ((float)millivolts / 1000);

	string displayString;
	sprintf(displayString, "%1.2f", volts);
	displayNextLCDString(displayString);
	displayNextLCDChar('V');
}
