#include "oCommon.h"
#include <stdio.h>
#include <wchar.h>
#ifdef __linux__
#include <ncursesw/curses.h>
#endif
#ifdef _WIN32
WORD getBackgroundColourForValue(char value) {
	switch (value) {
	case 'b': return BACKGROUND_BLUE | BACKGROUND_INTENSITY;       // Blue
	case 'y': return BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY; // Yellow
	case 'r': return BACKGROUND_RED | BACKGROUND_INTENSITY;        // Red
	case 'g': return BACKGROUND_GREEN | BACKGROUND_INTENSITY;        // Green
	case 'o': return BACKGROUND_RED | BACKGROUND_GREEN;            // Orange
	case 't': return BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY; // Teal
	case 'p': return BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY; // Purple
	case 'w': return BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY; // White
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


#elif defined(__linux__)
int getForegroundColourForValue(char value) {
	switch (value) {
	case 'b': return 34; // Blue
	case 'y': return 33; // Yellow
	case 'r': return 31; // Red
	case 'g': return 32; // Green
	case 'o': return 33; // Orange ≈ Yellow
	case 't': return 36; // Teal (Cyan)
	case 'p': return 35; // Purple
	default:  return 37; // White
	}
}

int getBackgroundColourForValue(char value)
{
	switch (value)
	{
	case 'r': return 1; // red
	case 'o': return 2; // yellow
	case 'b': return 3; // blue
	case 'g': return 4; // green
	case 'p': return 5; // magenta
	case 't': return 6; // teal
	case 'w': return 7; // white
	case 'y': return 8; // orange
	default:  return 0;
	}
}

void setColour(int colour)
{
	if (colour == 8)
		attron(COLOR_PAIR(2) | A_BOLD);
	else
		attron(COLOR_PAIR(colour));
}

void removeColour(int colour)
{
	if (colour == 8)
		attroff(COLOR_PAIR(2) | A_BOLD);
	else
		attroff(COLOR_PAIR(colour));
}

#endif

void resetCursor(void) {
#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD cellCount;
	COORD home = { 0, 0 };

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), home);
#elif defined(__linux__)
	wprintf(L"\033[H");
	fflush(stdout);
#endif
}
void hideCursor(void)
{
#ifdef _WIN32
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
#elif defined(__linux__)
	wprintf(L"\033[?25l");
	fflush(stdout);
#endif
}
void showCursor(void)
{
#ifdef _WIN32
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = TRUE;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
#elif defined(__linux__)
	wprintf(L"\033[?25h");
	fflush(stdout);
#endif
}

void clearScreen(void) 
{
#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count, cellCount;
	COORD home = { 0, 0 };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hOut, &csbi);
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	FillConsoleOutputCharacter(hOut, ' ', cellCount, home, &count);
	FillConsoleOutputAttribute(hOut, csbi.wAttributes, cellCount, home, &count);
	SetConsoleCursorPosition(hOut, home);
#elif defined(__linux__)
	wprintf(L"\033[3J\033[2J\033[H");
	fflush(stdout);
#endif
}
#ifdef __linux__
int _getch(void) {
#include <termios.h>
#include <unistd.h>

	struct termios oldt, newt;
	int ch;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;

	/* Disable canonical mode and echo */
	newt.c_lflag &= ~(ICANON | ECHO);

	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	return ch;

}
#endif
