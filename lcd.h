#pragma systemFile
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
	MHLCDButtonAll = 7
}MHLCDButton;
typedef struct MHLCDScreen{
	MHLCDScreenStyle style;
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
//This makes the passed screen go live on the VEX LCD
void displayScreen(MHLCDScreen screen);
//If it has a configuration, this makes the screen stored in nextScreen go live on the VEX LCD
void displayNextScreen();
//This edits a string that is passed so that it will be centered when displayed on the VEX LCD
void centerString(string *original);
void stringWithPadding(int padding, string *text);
void centerString(string *original){
	int space = 16 - strlen(*original);
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
	screen.style = style;
	switch(style){
		case MHLCDScreenStyleMain:
			screen.backlight = true;
			string header = "2616F";
			screen.header = header;
			centerString(&header);
			screen.topLine = header;
			screen.rightOption = "Red";
			screen.middleOption = "None";
			screen.leftOption = "Blue";
			screen.bottomLine = "Red   None  Blue";
			screen.nextScreen = MHLCDScreenStylePointSelection;
			if(liveScreen){
				screen.lastScreen = liveScreen;
			}
			break;
		case MHLCDScreenStylePointSelection:
			screen.backlight = true;
			screen.lastScreen = MHLCDScreenStyleMain;
			string header = "Points";
			screen.header = header;
			centerString(&header);
			screen.topLine = header;
			screen.leftOption = "3";
			screen.middleOption = "Back"
			screen.rightOption = "5";
			screen.bottomLine = "3     Back     5";
			screen.nextScreen = MHLCDScreenStyleVoltage;
			break;
		case MHLCDScreenStyleVoltage:
			screen.backlight = false;}}}
