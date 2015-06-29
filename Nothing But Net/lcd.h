//Prevent any extraneous warnings
#pragma systemFile
//Make sure there are never any collisions
#ifndef __LCD_H__
#define __LCD_H__
//MARK: - Constant Definitions

//Enumeration to define lines on the LCD
typedef enum _MHLCDLine{
  //Represents the top line on a VEX LCD screen
  MHLCDLineTop = 0,
  //Represents the bottom line of a VEX LCD
  MHLCDLineBottom = 1
}MHLCDLine;

//MARK: - Function Prototype Declarations

//Puts the screen in an idle state, suitable for when it's not being used
void idleScreen();
//Shorthand to display something on both lines of the LCD
void print(string top, string bottom);

//MARK: - Function Definitions

//Put the screen in a good state for when no one is looking
void idleScreen(){
  bLCDBacklight = false;
  print("2616F", "Frightening Lightning");
}
//Easily display something on both lines
void print(string top, string bottom){
  displayLCDCenteredString(MHLCDLineTop, top);
  displayLCDCenteredString(MHLCDLineBottom, bottom);
}
#endif