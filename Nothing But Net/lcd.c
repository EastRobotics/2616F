//Make sure this file is only ever #included once
#ifndef __LCD_C__
#define __LCD_C__
//Silence any unnecessary warnings
#pragma systemFile
//Require our header
#include "lcd.h"

///////////////////////////////////////////////////////////////////////////////
//MARK: - Whole Screen Functions
///////////////////////////////////////////////////////////////////////////////

//Put the screen in a good state for when no one is looking
void idleScreen(){
  //Turn off the screen backlight
  bLCDBacklight = false;
  //Display some advertisement on each line
  print("2616F", "");
}

///////////////////////////////////////////////////////////////////////////////
//MARK: - Single Line-Based Functions
///////////////////////////////////////////////////////////////////////////////

//Easily display something on both lines
void print(string top, string bottom){
  //Print the specified text on the top line
  displayLCDCenteredString(MHLCDLineTop, top);
  //Print the specified text on the bottom line
  displayLCDCenteredString(MHLCDLineBottom, bottom);
}
#endif