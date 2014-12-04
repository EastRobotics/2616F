#pragma systemFile
//ROBOTC Default Values: string = "", numbers = 536885932
#ifndef VOLTAGE_THRESHOLD
#include "battery.h"
#endif
//Different default screen types, used by the displayScreen function in lcd.h to display a preconfigured screen
typedef enum{
	MHLCDScreenStyleMain,
	MHLCDScreenStylePointSelection,
	MHLCDScreenStyleVoltage,
	MHLCDScreenStyleOff,
	MHLCDScreenStyleCustom
}MHLCDScreenStyle;
//Map of the possible LCD button combinations to make them easy to reference
typedef enum{
	MHLCDButtonLeft = 1,
	MHLCDButtonCenter = 2,
	MHLCDButtonRight = 4,
	MHLCDButtonLeftCenter = 3,
	MHLCDButtonLeftRight = 5,
	MHLCDButtonCenterRight = 6,
	MHLCDButtonAll = 7,
	MHLCDButtonNone = 0
}MHLCDButton;
//Constant to denote a string to be centered to the LCD width in the centerString function
static const int MHStringPaddingLCDCenter = 0;
//At the time of this writing (December 3, 2014), the standard VEX LCD width is 16 charachters. This is a constant to make that more obvious. If that ever changes, this constant will have to, too
static const int MHLCDScreenWidth = 16;
typedef struct MHLCDScreen{
	MHLCDScreenStyle style;
	MHLCDScreenStyle lastScreenStyle;
	MHLCDScreenStyle nextScreenStyle;
	string header;
	string footer;
	string topLine;
	string leftOption;
	string middleOption;
	string rightOption;
	string bottomLine;
	bool backlight;
}MHLCDScreen;
MHLCDScreen lastScreen;
MHLCDScreen nextScreen;
MHLCDScreen liveScreen;
//This sets up a screen based off of a default. It will operate on a custom screen, if a pointer to one is passed, but it defaults to nextScreen, if there is none passed.
void screenForScreenStyle(MHLCDScreenStyle style, MHLCDScreen *screen);
//This makes the passed screen go live on the VEX LCD. If both a header and a topLine is set, then the header will display. Same for the footer - bottomLine relationship
void displayScreen(MHLCDScreen screen);
//If it has a configuration, this makes the screen stored in nextScreen go live on the VEX LCD
void displayNextScreen();
//If it has a configuration, this makes the screen stroed in lastScreen go live on the VEX LCD
void displayLastScreen();
//This edits a string that is passed so that it will be centered within a given space. If no area is given, it will be centered to the VEX LCD
void centerString(string *original, int area);
//Prepares a MHLCDScreen for display by the displayScreen function
void prepareScreen(MHLCDScreen *screen);
//Clears the LCD screen when necessary
void clearLCD();
//Prints a string to the first line of the LCD, and the second line, if a string for that line is specified
void print(const string lineOne, const string lineTwo);
//Checks to see if the buttons pressed are different from the ones passed in
bool otherButtonsPressed(MHLCDButton button);
//Halts program execution until a button is pressed on the VEX LCD, then waits an extra tenth of a second
void waitForPress();
//Halts program execution until all buttons on the VEX LCD are released
void waitForRelease();
//Displays a screen for 5 seconds, then switches back to the previous
void flashScreen(MHLCDScreen screen);
//Displays a screen style for 5 seconds, then switches back to the previous
void flashScreenStyle(MHLCDScreenStyle screenStyle);
void centerString(string *original, int area){
	if(area == MHStringPaddingLCDCenter){
		area = MHLCDScreenWidth;
	}
	int space = area - strlen(*original);
	string whitespace = "";
	for(int i = 0; i < floor(space / 2); i++){
			whitespace += " ";
	}
	if(space % 2 == 0){
		//This has to be split into 2 lines, because ROBOTC is stupid
		*original = whitespace + *original;
		*original += whitespace;
	}
	else{
		//Also has to be split into 2 lines, also because ROBOTC is stupid
		*original = whitespace + *original;
		*original += whitespace + " ";
	}
}
void screenForScreenStyle(MHLCDScreenStyle style, MHLCDScreen *screen){
	if(!*screen){
		*screen = nextScreen;
	}
	screen->style = style;
	string header;
	string footer;
	switch(style){
		case MHLCDScreenStyleMain:
			screen->style = MHLCDScreenStyleMain;
			screen->lastScreenStyle = MHLCDScreenStyleMain;
			screen->nextScreenStyle = MHLCDScreenStylePointSelection;
			screen->backlight = true;
			header = "2616F";
			screen->header = header;
			centerString(&header, MHStringPaddingLCDCenter);
			screen->topLine = header;
			screen->rightOption = "Red";
			screen->middleOption = "None";
			screen->leftOption = "Blue";
			screen->bottomLine = "Red   None  Blue";
			screen->footer = screen->bottomLine;
			break;
		case MHLCDScreenStylePointSelection:
			screen->style = MHLCDScreenStylePointSelection;
			screen->lastScreenStyle = MHLCDScreenStyleMain;
			screen->backlight = true;
			header = "Points";
			screen->header = header;
			centerString(&header, MHStringPaddingLCDCenter);
			screen->topLine = header;
			screen->leftOption = "3";
			screen->middleOption = "Back";
			screen->rightOption = "5";
			screen->bottomLine = "3     Back     5";
			screen->footer = screen->bottomLine;
			break;
		case MHLCDScreenStyleVoltage:
			screen->style = MHLCDScreenStyleVoltage;
			screen->lastScreenStyle = MHLCDScreenStylePointSelection;
			screen->nextScreenStyle = MHLCDScreenStyleOff;
			screen->backlight = false;
			header = "2616F";
			screen->header = header;
			centerString(&header, MHStringPaddingLCDCenter);
			screen->topLine = header;
			LCDVoltageLine(&footer);
			screen->footer = footer;
			screen->bottomLine = footer;
			break;
		case MHLCDScreenStyleOff:
			screen->style = MHLCDScreenStyleOff;
			screen->nextScreenStyle = MHLCDScreenStyleOff;
			screen->lastScreenStyle = MHLCDScreenStyleOff;
			screen->backlight = false;
			screen->header = "";
			screen->topLine = "";
			screen->footer = "";
			screen->bottomLine = "";
			break;
		case MHLCDScreenStyleCustom:
			screen->style = MHLCDScreenStyleCustom;
			screen->nextScreenStyle = MHLCDScreenStyleCustom;
			screen->lastScreenStyle = MHLCDScreenStyleCustom;
			screen->backlight = true;
			screen->header = "";
			screen->topLine = "";
			screen->footer = "";
			screen->bottomLine = "";
		default:
			screen->style = MHLCDScreenStyleCustom;
			screen->nextScreenStyle = MHLCDScreenStyleCustom;
			screen->lastScreenStyle = MHLCDScreenStyleCustom;
			screen->backlight = true;
			screen->header = "";
			screen->topLine = "";
			screen->footer = "";
			screen->bottomLine = "";
			break;
	}
		return;
}
void displayScreen(MHLCDScreen screen){
	prepareScreen(&screen);
	clearLCD();
	lastScreen = liveScreen;
	bLCDBacklight = screen.backlight;
	displayLCDString(0, 0, screen.topLine);
	displayLCDString(1, 0, screen.bottomLine);
	liveScreen = screen;
	screenForScreenStyle(screen.nextScreenStyle, &nextScreen);
}
void clearLCD(){
	clearLCDLine(0);
	clearLCDLine(1);
}
void displayNextScreen(){
	if(nextScreen){
		displayScreen(nextScreen);
	}
}
void displayLastScreen(){
	if(lastScreen){
		displayScreen(lastScreen);
	}
}
void prepareScreen(MHLCDScreen *screen){
	//These are all checking if the value is null, and assigning one, if it is. The probelm is that it might just be a null pointer. Pray that doesn't happen
	if(screen->backlight == NULL){
		screen->backlight = false;
	}
	if(screen->nextScreenStyle == NULL){
		screen->nextScreenStyle = MHLCDScreenStyleCustom;
	}
	if(screen->lastScreenStyle == NULL){
		screen->lastScreenStyle = MHLCDScreenStyleCustom;
	}
	if(screen->style == NULL){
		screen->style = MHLCDScreenStyleCustom;
	}
	if(screen->header != ""){
		centerString(screen->header, MHStringPaddingLCDCenter);
		screen->topLine = screen->header;
	}
	if(screen->footer != ""){
		centerString(screen->footer, MHStringPaddingLCDCenter);
		screen->bottomLine = screen->footer;
	}
	if(screen->rightOption != "" || screen->middleOption != "" || screen->leftOption != ""){
		if(strlen(screen->rightOption) + strlen(screen->middleOption) + strlen(screen->leftOption) <= 16){
			int space = MHLCDScreenWidth - strlen(screen->rightOption) + strlen(screen->leftOption);
			centerString(screen->middleOption, space);
			sprintf(screen->bottomLine, "%s%s%s", screen->leftOption, screen->middleOption, screen->rightOption);
		}
		else{
			screen->bottomLine = "Too many chars";
			centerString(screen->bottomLine, MHStringPaddingLCDCenter);
		}
	}
}
void print(const string lineOne, const string lineTwo){
	clearLCDLine(0);
	displayLCDPos(0, 0);
	displayNextLCDString(lineOne);
	if(lineTwo != ""){
		clearLCDLine(1);
		displayLCDPos(1, 0);
		displayNextLCDString(lineTwo);
	}
}
bool otherButtonsPressed(MHLCDButton button){
	if(nLCDButtons == button){
		return false;
	}
	else{
		return true;
	}
}
void waitForPress(){
	while(nLCDButtons == MHLCDButtonNone){/*We just have to wait a while*/}
	wait1Msec(MHTimeTenthSecond);
}
void waitForRelease(){
	while(nLCDButtons != MHLCDButtonNone){/*We just have to wait a while*/}
}
void flashScreen(MHLCDScreen screen){
	displayScreen(screen);
	wait1Msec(MHTimeOneSecond * 5);
	displayLastScreen();
}
void flashScreenStyle(MHLCDScreenStyle screenStyle){
	MHLCDScreen newScreen;
	screenForScreenStyle(screenStyle, &newScreen);
	flashScreen(newScreen);
}
