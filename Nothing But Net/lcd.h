//Prevent any extraneous warnings
#pragma systemFile
//Make sure there are never any collisions
#ifndef __LCD_H__
#define __LCD_H__

///////////////////////////////////////////////////////////////////////////////
//MARK: - Constant Definitions
///////////////////////////////////////////////////////////////////////////////

//Enumeration to define lines on the LCD
typedef enum _MHLCDLine{
  //Represents the top line on a VEX LCD screen
  MHLCDLineTop = 0,
  //Represents the bottom line of a VEX LCD
  MHLCDLineBottom = 1
}MHLCDLine;

///////////////////////////////////////////////////////////////////////////////
//MARK: - Whole Screen Functions
///////////////////////////////////////////////////////////////////////////////

/* Puts the screen in an idle state, suitable for when it's not being used

This function takes no parameters

This function does not return anything

Called like: idleScreen();
 */
void idleScreen();

///////////////////////////////////////////////////////////////////////////////
//MARK: - Single Line-Based Functions
///////////////////////////////////////////////////////////////////////////////

/* Displays a string on each line of the LCD

string top: Text to display on the top line of the LCD
string bottom: Text to display on the bottom line of the LCD

This function does not return anything

Called like: print("Top Line", "Bottom Line"); */
void print(const string top, const string bottom);

//Define everything declared above
#include "lcd.c"
#endif
