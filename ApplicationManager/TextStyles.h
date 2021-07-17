#pragma once

#include "windows.h"

//#define backgroundClr 16 * 0

#define CLR(clr) { clr + 16 * 0 }

#define defaultClr CLR(7)
#define errorClr   CLR(12)
#define successClr CLR(10)
#define listClr    CLR(11)

#define CLROUT(clr, action) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr); action; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), defaultClr); }
#define DEFCLRB(action) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), defaultClr); action; }
#define DEFCLRA(action) { action; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), defaultClr); }

//HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);