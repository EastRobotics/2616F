/********************************************************/
/*                        lcd.h                         */
/*                         v0.9                         */
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

/********************************************************/
/*                     TWEAKER NOTES                    */
/*                                                      */
/* All of this code is completely safe. If you're       */
/* curious as to why a piece of code is written that    */
/* way, change it! If you still can't figure it out,    */
/* e-mail me. It may very well be a bug (or just my     */
/* personal preference).                                */
/*                                                      */
/* I do plan to put out a second version of this        */
/* header, so report anything you find and I'll give    */
/* you a mention. Again, this code is not competition-  */
/* tested. In fact, I wrote it almost entirely with the */
/* emulator. Use at your own risk.                      */
/*                                                      */
/* I make heavy use of compile-time logic to remove     */
/* unwanted features. It is suggested to leave any #    */
/* statements alone. Read Documentation.txt for         */
/* details.                                             */
/********************************************************/
#ifdef lcd.h
#warning ("Attempted to include lcd.h more than once. Only the first #include has taken effect.")
#else
#define lcd.h
#ifdef LCD_NotUsing_Menu
#warning ("LCD_Menu() and related functions and variables have been excluded from this compilation.")
#endif
#ifdef LCD_NotUsing_Prompt
#warning ("LCD_Prompt(...) and related functions and variables have been excluded from this compilation.")
#endif
#ifdef LCD_NotUsing_Display
#warning ("LCD_Display and related functions and variables have been excluded from this compilation.")
#endif

#pragma systemFile

#ifndef LCD_NotUsing_Display
typedef struct {
  bool Paused;
  bool BattA;
  tSensors BattB;
  bool Backup;
} _LCD_Display;
#endif

#ifndef LCD_NotUsing_Menu
typedef struct {
  string Title;
  string Text;
  int PrevIndex;
  int SelectIndex;
  int NextIndex;
} _LCD_Menu;
#endif

typedef struct {
#ifndef LCD_NotUsing_Menu
  bool IsFirstLoop;
  int Index;
  _LCD_Menu Menu[LCD_SizeOfMenu];
#endif
#ifndef LCD_NotUsing_Display
  _LCD_Display Display;
#endif
#ifndef LCD_NotUsing_Prompt && LCD_NotUsing_Display
  float Timer[4];
#endif
} _LCD;

_LCD LCD;

#ifndef LCD_NotUsing_Menu
void LCD_Menu_Define();
bool LCD_Menu_Execute();

void LCD_Menu_Display()
{
  displayLCDCenteredString(0,LCD.Menu[LCD.Index].Title);
  displayLCDCenteredString(1,LCD.Menu[LCD.Index].Text);
  if(LCD.Menu[LCD.Index].PrevIndex != LCD.Index) {displayLCDChar(1, 0, 247);};
  if(LCD.Menu[LCD.Index].NextIndex != LCD.Index) {displayLCDChar(1, 15, 246);};
};

void LCD_Menu_Increment(char Direction)
{
  switch(Direction)
  {
  case -1:
    {
      LCD.Index = LCD.Menu[LCD.Index].PrevIndex;
      break;
    };
  case +1:
    {
      LCD.Index = LCD.Menu[LCD.Index].NextIndex;
      break;
    };
  };
};

void LCD_Menu()
{
  LCD_Menu_Define();
  LCD.IsFirstLoop = true;
  LCD.Index = 0;
  LCD.Display.Paused = true;
  clearLCDLine(0);
  clearLCDLine(0);
  bLCDBacklight = true;
  while(true)
  {
    if(nLCDButtons != 0 || LCD.IsFirstLoop == true)
    {
      LCD.IsFirstLoop = false;
      if(nLCDButtons == 1) {LCD_Menu_Increment(-1);};
      if(nLCDButtons == 2) {
        if (LCD_Menu_Execute())
        {
          LCD.Display.Paused = false;
          return;
        };
      };
      if(nLCDButtons == 4) {LCD_Menu_Increment(+1);};
      LCD_Menu_Display();
      while (nLCDButtons != kButtonNone) {};
    };
  };
};
#endif

#ifndef LCD_NotUsing_Prompt && LCD_NotUsing_Display
void LCD_Timer_Set(const char Timer, const float Value = 0)
{
  LCD.Timer[Timer] = nSysTime - Value;
};

float LCD_Timer_Hours(const char Timer)
{
  return (nSysTime - LCD.Timer[Timer]) / 3600000;
};

float LCD_Timer_Mins(const char Timer, const bool SubtractHigherUnit = false)
{
  const float Time = (nSysTime - LCD.Timer[Timer]) / 1000;
  if (SubtractHigherUnit)
  {
    return (Time - (floor(LCD_Timer_Hours(Timer)) * 3600)) / 60;
    } else {
    return Time / 60;
  };
};

float LCD_Timer_Secs(const char Timer, const bool SubtractHigherUnit = false)
{
  const float Time = (nSysTime - LCD.Timer[Timer]) / 1000;
  if (SubtractHigherUnit)
  {
    return Time - (floor(LCD_Timer_Mins(Timer)) * 60);
    } else {
    return Time;
  };
};

float LCD_Timer_Msecs(const char Timer, const bool SubtractHigherUnit = false)
{
  const float Time = (nSysTime - LCD.Timer[Timer]);
  if (SubtractHigherUnit)
  {
    return Time - (floor(LCD_Timer_Secs(Timer)) * 1000);
    } else {
    return Time;
  };
};

void LCD_Timer_WaitUntil(const char Timer, const float Value)
{
  while (LCD_Timer_Msecs(Timer) < Value)
  {
    wait1Msec(1);
  };
};
#endif

#ifndef LCD_NotUsing_Display
task LCD_Display
{
  LCD_Timer_Set(0,0);
  LCD.Display.Paused = false;
  char Char;
  char Index;
  char i;
  char j;
  string Text[3];
  Text[0] = "                   ";
  Text[1] = "                   ";
  Text[2] = "                   ";
  char LastProcessedStatus;
  char CurrentStatus;
  clearLCDLine(0);
  clearLCDLine(1);
  bLCDBacklight = true;
  while (true)
  {
    for (i = 0; i < (strlen(Text[0]) + strlen(Text[1]) + strlen(Text[2])); i++)
    {
      setLCDPosition(1, 0);
      for (j = 0; j < 16; j++)
      {
        if (LCD.Display.BattA)
        {
          sprintf(Text[0], "Batt A: %1.2fv  ", nImmediateBatteryLevel / 1000);
          } else {
          Text[0] = "";
        };
        if (LCD.Display.BattB != 0) {
          sprintf(Text[1], "Batt B: %1.2fv  ", SensorValue[LCD.Display.BattB] / 1000);
          } else {
          Text[1] = "";
        };
        if (LCD.Display.Backup) {
          sprintf(Text[2], "Backup: %1.2fv  ", BackupBatteryLevel / 1000);
          } else {
          Text[2] = "";
        };
        if (!LCD.Display.BattA && LCD.Display.BattB == 0 && !LCD.Display.Backup)
        {
          Text[0] = "Must define LCD.Dis";
          Text[1] = "play.BattA, BattB, ";
          Text[2] = "and/or Backup. ";
        };
        Char = i + j;
        if ((strlen(Text[0])) > Char) {
          Index = 0;
          } else if((strlen(Text[0]) + strlen(Text[1])) > Char) {
          Index = 1;
          Char -= strlen(Text[0]);
          } else if((strlen(Text[0]) + strlen(Text[1]) + strlen(Text[2])) > Char) {
          Index = 2;
          Char -= strlen(Text[0]) + strlen(Text[1]);
          } else if((strlen(Text[0]) + strlen(Text[1]) + strlen(Text[2]) - 1) < Char) {
          Index = 0;
          Char -= strlen(Text[0]) + strlen(Text[1]) + strlen(Text[2]);
        };
        while(LCD.Display.Paused) {};
        displayNextLCDChar(StringGetChar(Text[Index], Char));
      }
      clearLCDLine(0);
      if (bIfiRobotDisabled)
      {
        displayLCDString(0, 0, "Disabled");
        CurrentStatus = 0;
        }	else {
        if (bIfiAutonomousMode)
        {
          displayLCDString(0, 0, "Autonomous");
          CurrentStatus = 1;
          } else {
          displayLCDString(0, 0, "Driver");
          CurrentStatus = 2;
        };
      };
      if(LastProcessedStatus != CurrentStatus)
      {
        LCD_Timer_Set(0,0);
        } else {
        displayLCDNumber(0, 12, LCD_Timer_Mins(0), -1);
        displayLCDChar(0, 13, 58);
        displayLCDNumber(0, 14, LCD_Timer_Secs(0,true), -2);
      };
      LastProcessedStatus = CurrentStatus;
      while (nLCDButtons != 0) {
        wait10Msec(100);
      };
      wait10Msec(25);
    }
  }
};
#endif

#ifndef LCD_NotUsing_Prompt
void LCD_Prompt_Blink(bool Blink, string Choice1, string Choice2, string Choice3, char DefaultChoice)
{
  switch (Blink)
  {
  case true:
    switch (DefaultChoice)
    {
    case 1:
      displayLCDString(1, 0, Choice1);
      break;
    case 2:
      displayLCDCenteredString(1, Choice2);
      displayLCDString(1, 0, Choice1);
      displayLCDString(1, 12, Choice3);
      break;
    case 3:
      displayLCDString(1, 12, Choice3);
      break;
    };
    break;
  case false:
    switch (DefaultChoice)
    {
    case 1:
      displayLCDString(1, 0, "    ");
      break;
    case 2:
      clearLCDLine(1);
      displayLCDString(1, 0, Choice1);
      displayLCDString(1, 12, Choice3);
      break;
    case 3:
      displayLCDString(1, 12, "    ");
      break;
    };
    break;
  };
};

char LCD_Prompt(string Prompt1, string Prompt2 = "", string Choice1 = "", string Choice2 = "OK", string Choice3 = "", char DefaultChoice = 0, char DefaultTimeOut = 0)
{
  if (DefaultTimeOut !=0 && DefaultChoice != 0)
  {
    LCD_Timer_Set(1);
    LCD_Timer_Set(2);
  };
  LCD.Display.Paused = true;
  bool Blink;
  clearLCDLine(0);
  clearLCDLine(1);
  displayLCDCenteredString(1, Choice2);
  displayLCDString(1, 0, Choice1);
  displayLCDString(1, 12, Choice3);
  if (strlen(Prompt1) <= 16)
  {
    displayLCDString(0, 0, Prompt1);
    while (true)
    {
      if (DefaultTimeOut !=0 && DefaultChoice != 0)
      {
        if (LCD_Timer_Secs(1) >= DefaultTimeOut) {LCD.Display.Paused = false;return DefaultChoice;};
        if (LCD_Timer_Secs(2) >= 1)
        {
          LCD_Timer_Set(2);
          Blink = !Blink;
          LCD_Prompt_Blink(Blink, Choice1, Choice2, Choice3, DefaultChoice);
        };
      };
      while (LCD_Timer_Secs(3) <= 1)
      {
        if (nLCDButtons == 1 && Choice1 != "") {LCD.Display.Paused = false;return 1;};
        if (nLCDButtons == 2 && Choice2 != "") {LCD.Display.Paused = false;return 2;};
        if (nLCDButtons == 4 && Choice3 != "") {LCD.Display.Paused = false;return 3;};
      };
      LCD_Timer_Set(3);
    };
    } else {
    char i;
    char j;
    char Char;
    char Pnum;
    while (true)
    {
      for (i = 0; i < (strlen(Prompt1) + strlen(Prompt2)); i++)
      {
        setLCDPosition(0, 0);
        for (j = 0; j < 16; j++)
        {
          Char = i + j;
          if ((strlen(Prompt1)) > Char) {
            Pnum = 0;
            } else if((strlen(Prompt1) + strlen(Prompt2)) > Char) {
            Pnum = 1;
            Char -= strlen(Prompt1);
            } else if((strlen(Prompt1) + strlen(Prompt2) - 1) < Char) {
            Pnum = 0;
            Char -= strlen(Prompt1) + strlen(Prompt2);
          };
          switch (Pnum)
          {
          case 0:
            displayNextLCDChar(StringGetChar(Prompt1, Char));
            break;
          case 1:
            displayNextLCDChar(StringGetChar(Prompt2, Char));
            break;
          };
        };
        while (LCD_Timer_Msecs(3) <= 250)
        {
          if (nLCDButtons == 1 && Choice1 != "") {LCD.Display.Paused = false;return 1;};
          if (nLCDButtons == 2 && Choice2 != "") {LCD.Display.Paused = false;return 2;};
          if (nLCDButtons == 4 && Choice3 != "") {LCD.Display.Paused = false;return 3;};
        };
        LCD_Timer_Set(3);
        Blink = !Blink;
        LCD_Prompt_Blink(Blink, Choice1, Choice2, Choice3, DefaultChoice);
        if (DefaultTimeOut !=0 && DefaultChoice != 0)
        {
          if (LCD_Timer_Secs(1) >= DefaultTimeOut) {LCD.Display.Paused = false;return DefaultChoice;};
        };
      };
    };
  };
};
#endif
#endif
