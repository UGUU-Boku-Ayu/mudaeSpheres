#include "oc.h"
#include "oq.h"
#include "oCommon.h"
#include <io.h>
#include <fcntl.h>
#include <wchar.h>
#ifdef _WIN32
#include <conio.h>
#endif
void oh(void)
{
	clearScreen();
	wprintf(L"Click randomly, there is only luck in oh. \nPress any key to return.");
	_getch();
}

int main(void)
{
	hideCursor();
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
