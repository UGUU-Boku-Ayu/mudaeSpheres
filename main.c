#include <stdio.h>
#include "oc.h"
#include "oq.h"
#include "oCommon.h"
#include <fcntl.h>
#include <wchar.h>
#ifdef _WIN32
#include <conio.h>
#include <io.h>
#elif defined(__linux__)
#include <locale.h>
#define _XOPEN_SOURCE_EXTENDED 1
#include <ncursesw/curses.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void cleanup(void) {
	endwin();
}
#endif


void oh(void)
{
#ifdef _WIN32
	clearScreen();
	wprintf(L"Click randomly, there is only luck in oh. \nPress any key to return.");
	_getch();
#elif defined(__linux__)
	erase();
	mvaddwstr(0,0, L"Click randomly, there is only luck in oh. ");
	mvaddwstr(1,0, L"Press any key to return.");
	refresh();
	getch();
#endif
}
#ifdef __linux__
void sigint_handler(int signo) {
	endwin();  // restore terminal
	_exit(1);  // exit immediately
}
#endif
int main(void)
{

#ifdef _WIN32
	int originalMode = _setmode(_fileno(stdout), _O_WTEXT);
#elif defined(__linux__)
	setlocale(LC_ALL, "");
	initscr();

	if (!has_colors()) {
		endwin();
		fprintf(stderr, "No colour support\n");
		return 1;
	}

	start_color();
	use_default_colors();

	init_pair(1, COLOR_RED, -1);
	init_pair(2, COLOR_YELLOW, -1);
	init_pair(3, COLOR_BLUE, -1);
	init_pair(4, COLOR_GREEN, -1);
	init_pair(5, COLOR_MAGENTA, -1);
	init_pair(6, COLOR_CYAN, -1);
	init_pair(7, COLOR_WHITE, -1);
	atexit(cleanup);
	signal(SIGINT, sigint_handler);
#endif
#ifdef _WIN32
	hideCursor();
	wprintf(L"  Options:\n    1. $oh Solver\n    2. $oc Solver\n    3. $oq Solver  (Very WIP, triple check results before trusting them)\n    ESC. Exit");
#elif defined(__linux__)
	erase();
	mvaddwstr(0, 0, L"  Options:");
	mvaddwstr(1, 0, L"    1. $oh Solver");
	mvaddwstr(2, 0, L"    2. $oc Solver");
	mvaddwstr(3, 0, L"    3. $oq Solver (Very WIP, triple check results before trusting them)");
	mvaddwstr(4, 0, L"    ESC. Exit");
	refresh();
#endif
	while (1)
	{
		int ch = _getch();
		if (ch == 27) break;
		if (ch == '1') oh();
		if (ch == '2') oc();
		if (ch == '3') oq();
		if (ch < '4' && ch >= '1')
		{
#ifdef _WIN32
			clearScreen();
			wprintf(L"  Options:\n    1. $oh Solver\n    2. $oc Solver\n    3. $oq Solver  (Very WIP, triple check results before trusting them)\n    ESC. Exit");
#elif defined(__linux__)
			erase();
			mvaddwstr(0, 0, L"  Options:");
			mvaddwstr(1, 0, L"    1. $oh Solver");
			mvaddwstr(2, 0, L"    2. $oc Solver");
			mvaddwstr(3, 0, L"    3. $oq Solver  (Very WIP, triple check results before trusting them)");
			mvaddwstr(4, 0, L"    ESC. Exit");
			refresh();
#endif
		}
	}
#ifdef __linux__
	endwin();
#endif
#ifdef _WIN32
	showCursor();
	_setmode(_fileno(stdout), originalMode);
#endif
}
