#include "oCommon.h"


WORD getBackgroundColourForValue(char value) {
	switch (value) {
	case 'b': return BACKGROUND_BLUE | BACKGROUND_INTENSITY;       // Blue
	case 'y': return BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY; // Yellow
	case 'r': return BACKGROUND_RED | BACKGROUND_INTENSITY;        // Red
	case 'g': return BACKGROUND_GREEN | BACKGROUND_INTENSITY;        // Green
	case 'o': return BACKGROUND_RED | BACKGROUND_GREEN;            // Orange
	case 't': return BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY; // Teal
	case 'p': return BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY; // Purple
	default:  return 7;
	}
}
WORD getForegroundColourForValue(char value) {
	switch (value) {
	case 'b': return FOREGROUND_BLUE | FOREGROUND_INTENSITY;       // Blue
	case 'y': return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY; // Yellow
	case 'r': return FOREGROUND_RED | FOREGROUND_INTENSITY;        // Red
	case 'g': return FOREGROUND_GREEN | FOREGROUND_INTENSITY;        // Green
	case 'o': return FOREGROUND_RED | FOREGROUND_GREEN;            // Orange
	case 't': return FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY; // Teal
	case 'p': return FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY; // Purple
	default:  return 7;
	}
}

void setColour(WORD colour) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
}

void resetCursor(void) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count, cellCount;
	COORD home = { 0, 0 };

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), home);
}
void hideCursor(void)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}
void showCursor(void)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = TRUE;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void clearScreen(void) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count, cellCount;
	COORD home = { 0, 0 };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hOut, &csbi);
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	FillConsoleOutputCharacter(hOut, ' ', cellCount, home, &count);
	FillConsoleOutputAttribute(hOut, csbi.wAttributes, cellCount, home, &count);
	SetConsoleCursorPosition(hOut, home);
}