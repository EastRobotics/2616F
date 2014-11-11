/********************************************************/
/*                   lcd_menu_blank.h                   */
/*                        v0.9                          */
/*                                                      */
/* This file was originally developed by:               */
/* Kristaps Berzinch                                    */
/* Programmer for Team 2105A                            */
/* Ware County High School                              */
/* Waycross, Georgia, USA                               */
/*                                                      */
/* Please drop me a line with questions or comments!    */
/* kberzinch@live.com                                   */
/* or on the VEX Forums: WCHS Programmer                */
/*                                                      */
/* You can do whatever you want with these files, but   */
/* please leave this and other credits sections intact. */
/*                                                      */
/* Neither I nor Ware County High School is responsible */
/* for any consequences.                                */
/********************************************************/

const char LCD_SizeOfMenu = 1; // MUST be at least 1 to prevent crash.

#undef LCD_NotUsing_Menu       // Clear any statements against compiling LCD_Menu.

#include "lcd.h";

typedef struct {
  char Mode;
  bool Alliance;
  bool StartPoint;
  char Autonomous;
} _Competition;

_Competition Competition;

void LCD_Menu_Define()
{
  char i;
  for (i = 0; i < LCD_SizeOfMenu; i++)
  {
    LCD.Menu[i].Title = "";
    LCD.Menu[i].Text = "";
    LCD.Menu[i].PrevIndex = i - 1;
    LCD.Menu[i].SelectIndex = 0;
    LCD.Menu[i].NextIndex = i + 1;
  }
  LCD.Menu[0].Title = "Blank Menu";
  LCD.Menu[0].Text = "";
  LCD.Menu[0].PrevIndex = 0;
  LCD.Menu[0].SelectIndex = -1;
  LCD.Menu[0].NextIndex = 0;
};

bool LCD_Menu_Execute()
{
  switch(LCD.Index)
  {
  case 0:
    {
      // What to do when LCD.Menu[0] is selected? Continue adding case statements like this.
      // Note that menu jumps and exits are handled by the code below the switch block and by the LCD_Menu master function
      break;
    };
  };
  if (LCD.Menu[LCD.Index].SelectIndex == -1)
  {
    return true;
    } else {
    LCD.Index = LCD.Menu[LCD.Index].SelectIndex;
    return false;
  };
};
