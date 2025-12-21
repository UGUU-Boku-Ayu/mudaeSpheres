#include "oc.h"
#include "oq.h"
#include "oCommon.h"
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <wchar.h>
#include <conio.h>
#include <windows.h>

HANDLE hOut;
static void hideCursor(void)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}
static void showCursor(void)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = TRUE;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}
static void clearScreen(void) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count, cellCount;
	COORD home = { 0, 0 };

	GetConsoleScreenBufferInfo(hOut, &csbi);
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	FillConsoleOutputCharacter(hOut, ' ', cellCount, home, &count);
	FillConsoleOutputAttribute(hOut, csbi.wAttributes, cellCount, home, &count);
	SetConsoleCursorPosition(hOut, home);
}
void oh(void)
{
	clearScreen();
	wprintf(L"Click randomly, there is only luck in oh. \nPress any key to return.");
	_getch();
}

int main(void)
{
	hideCursor();
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	int originalMode = _setmode(_fileno(stdout), _O_WTEXT);
	wprintf(L"  Options:\n    1. $oh Solver\n    2. $oc Solver\n    3. $oq Solver\n    ESC. Exit");
	while (1)
	{
		int ch = _getch();
		if (ch == 27) break;
		if (ch == '1') oh();
		if (ch == '2') oc();
		if (ch == '3') oq();
		if (ch < '4' && ch >= '1')
		{
			clearScreen();
			wprintf(L"  Options:\n    1. $oh Solver\n    2. $oc Solver\n    3. $oq Solver\n    ESC. Exit");
		}
	}
	showCursor();
	_setmode(_fileno(stdout), originalMode);
}
