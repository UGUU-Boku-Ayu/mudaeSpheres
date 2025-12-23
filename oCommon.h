#pragma once
#ifndef MUDAE_OCOMMON
#define MUDAE_OCOMMON
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
WORD getBackgroundColourForValue(char value);
WORD getForegroundColourForValue(char value);
void setColour(WORD colour);
void resetCursor(void);
void hideCursor(void);
void showCursor(void);
void clearScreen(void);
#endif