#pragma once
#ifndef MUDAE_OCOMMON
#define MUDAE_OCOMMON
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
WORD getBackgroundColourForValue(char value);
WORD getForegroundColourForValue(char value);
void setColour(WORD colour);
#elif defined(__linux__)
int getBackgroundColourForValue(char value);
int getForegroundColourForValue(char value);
void setColour(int colour);
void removeColour(int colour);
int _getch(void);
#endif
void resetCursor(void);
void hideCursor(void);
void showCursor(void);
void clearScreen(void);
#endif