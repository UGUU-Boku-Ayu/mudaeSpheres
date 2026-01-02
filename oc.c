
#include <fcntl.h>
#include <wchar.h>
#ifdef _WIN32
#include <conio.h>
#include <io.h>
#elif defined(__linux__)
#define _XOPEN_SOURCE_EXTENDED 1
#include <ncursesw/curses.h>
#endif
#include "oCommon.h"



static void drawBoard(char spheres[5][5], char sphereprediction[5][5], int selRow, int selCol)
{
#ifdef _WIN32
	wprintf(L"       a      b      c      d      e        Info:\n");
	wprintf(L"  ┌────────────────────────────────────┐\n");
#elif defined(__linux__)
	mvaddwstr(0, 0, L"       a      b      c      d      e        Info:");
	mvaddwstr(1, 0, L"  ┌────────────────────────────────────┐");
#endif
	for (int i = 0; i < 5; i++) {
#ifdef _WIN32
		wprintf(L"  │ ");
#elif defined(__linux__)
		mvaddwstr(2 + (3 * i), 0, L"  │ ");
#endif
		for (int j = 0; j < 5; j++)
		{
#ifdef _WIN32
			if (i == selRow && j == selCol)
				setColour(getBackgroundColourForValue('w'));
			else
				setColour(getBackgroundColourForValue(spheres[i][j]));
			wprintf(L"┌────┐ ");
			setColour(7);
#elif defined(__linux__)
			if (i == selRow && j == selCol)
			{
				setColour(getBackgroundColourForValue('w'));
				addwstr(L"┌────┐ ");
				removeColour(getBackgroundColourForValue('w'));
			}
				
			else
			{
				setColour(getBackgroundColourForValue(spheres[i][j]));
				addwstr(L"┌────┐ ");
				removeColour(getBackgroundColourForValue(spheres[i][j]));
			}
				
			
#endif
		}
		switch (i)
		{
#ifdef _WIN32
		case(0):
			wprintf(L"│    Fill the squares with your selections in the $oc sphere minigame.");
			break;
		case(1):
			wprintf(L"│");
			break;
		case(2):
			wprintf(L"│    ← - Left   ↑ - Up   → - Right   ↓ - Down");
			break;
		case(3):
			wprintf(L"│");
			break;
		case(4):
			wprintf(L"│    esc - Return");
			break;
			//case(4):
			//	wprintf(L"│");
#elif defined(__linux__)
		case(0):
			addwstr(L"│    Fill the squares with your selections in the $oc sphere minigame.");
			break;
		case(1):
			addwstr(L"│");
			break;
		case(2):
			addwstr(L"│    ← - Left   ↑ - Up   → - Right   ↓ - Down");
			break;
		case(3):
			addwstr(L"│");
			break;
		case(4):
			addwstr(L"│    esc - Return");
			break;
#endif
		}
#ifdef _WIN32
		wprintf(L"\n %d│ ", i + 1);
#elif defined(__linux__)
		wchar_t buf[256];
		swprintf(buf, 256, L" %d│ ", i + 1);
		mvaddwstr(3 + (3 * i), 0, buf);

#endif
		for (int j = 0; j < 5; j++)
		{
#ifdef _WIN32
			if (i == selRow && j == selCol)
				setColour(getBackgroundColourForValue('w'));
			else
				setColour(getBackgroundColourForValue(spheres[i][j]));

			if (spheres[i][j] != ' ')
				wprintf(L"│  %c │ ", spheres[i][j]);
			else
				wprintf(L"│  %c │ ", sphereprediction[i][j]);
			setColour(7);
#elif defined(__linux__)
			if (spheres[i][j] != ' ')
				swprintf(buf, 256, L"│  %c │ ", spheres[i][j]);
			else
				swprintf(buf, 256, L"│  %c │ ", sphereprediction[i][j]);
			if (i == selRow && j == selCol)
			{
				setColour(getBackgroundColourForValue('w'));
				addwstr(buf);
				removeColour(getBackgroundColourForValue('w'));
			}
			else
			{
				setColour(getBackgroundColourForValue(spheres[i][j]));
				addwstr(buf);
				removeColour(getBackgroundColourForValue(spheres[i][j]));
			}
#endif
		}

		switch (i)
		{
#ifdef _WIN32
		case(0):
			wprintf(L"│    The squares containing 'x' have a chance to contain the red sphere.");
			break;
		case(1):
			wprintf(L"│    Controls:");
			break;
		case(2):
			wprintf(L"│");
			break;
		case(3):
			wprintf(L"│    backspace/del - Clear");
			break;
		case(4):
			wprintf(L"│");
			break;
#elif defined(__linux__)
		case(0):
			addwstr(L"│    The squares containing 'x' have a chance to contain the red sphere.");
			break;
		case(1):
			addwstr(L"│    Controls:");
			break;
		case(2):
			addwstr(L"│");
			break;
		case(3):
			addwstr(L"│    backspace/del - Clear");
			break;
		case(4):
			addwstr(L"│");
			break;
#endif
		}
#ifdef _WIN32
		wprintf(L"\n  │ ");
#elif defined(__linux__)
		mvaddwstr(4 + (3 * i), 0, L"  │ ");
#endif
		for (int j = 0; j < 5; j++)
		{
#ifdef _WIN32
			if (i == selRow && j == selCol)
				setColour(getBackgroundColourForValue('w'));
			else
				setColour(getBackgroundColourForValue(spheres[i][j]));

			wprintf(L"└────┘ ");
			setColour(7);
#elif defined(__linux__)
			if (i == selRow && j == selCol)
			{
				setColour(getBackgroundColourForValue('w'));
				addwstr(L"└────┘ ");
				removeColour(getBackgroundColourForValue('w'));
			}
			else
			{
				setColour(getBackgroundColourForValue(spheres[i][j]));
				addwstr(L"└────┘ ");
				removeColour(getBackgroundColourForValue(spheres[i][j]));
			}
#endif
		}
		switch (i)
		{
#ifdef _WIN32
		case(0):
			wprintf(L"│    Choose the spaces that eliminate the most possibilities.");
			break;
		case(1):
			wprintf(L"│");
			break;
		case(2):
			wprintf(L"│    b - Blue   t - Teal   g - Green   y - Yellow   o - Orange   r - Red");
			break;
		case(3):
			wprintf(L"│");
			break;
		case(4):
			wprintf(L"│");
			break;
		}
		if (i == 4)
			wprintf(L"\n  └────────────────────────────────────┘\n");
		else
			wprintf(L"\n");
#elif defined(__linux__)
			case(0):
				addwstr(L"│    Choose the spaces that eliminate the most possibilities.");
				break;
			case(1):
				addwstr(L"│");
				break;
			case(2):
				addwstr(L"│    b - Blue   t - Teal   g - Green   y - Yellow   o - Orange   r - Red");
				break;
			case(3):
				addwstr(L"│");
				break;
			case(4):
				addwstr(L"│");
				break;
		}
		if (i == 4)
			mvaddwstr(5 + (3 * i), 0, L"  └────────────────────────────────────┘");
		refresh();
#endif
	}


}
static int teal(char spheres[5][5], int x, int y)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (spheres[i][j] == 't')
			{
				if (!(i == x || j == y || i - j == x - y || i + j == x + y))
				{
					return 0;
				}
			}
		}
	}
	return 1;
}
static int yellow(char spheres[5][5], int x, int y)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (spheres[i][j] == 'y')
			{
				if (!(i - j == x - y || i + j == x + y))
				{
					return 0;
				}
			}
		}
	}
	return 1;
}
static int orange(char spheres[5][5], int x, int y)
{
	int hasOrange = 0;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (spheres[i][j] == 'o')
			{
				hasOrange = 1;
				int adjacent = 0;
				if (i > 0 && i - 1 == x && j == y) adjacent = 1; 
				if (i < 4 && i + 1 == x && j == y) adjacent = 1;  
				if (j > 0 && i == x && j - 1 == y) adjacent = 1;  
				if (j < 4 && i == x && j + 1 == y) adjacent = 1;  

				if (!adjacent)
					return 0;
			}
		}
	}

	return 1;
}



static int green(char spheres[5][5], int x, int y)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (spheres[i][j] == 'g')
			{
				if (!(i == x || j == y))
				{
					return 0;
				}
			}
		}
	}
	return 1;
}
static int blue(char spheres[5][5], int x, int y)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (i == x || j == y || i - j == x - y || i + j == x + y)
			{
				if (spheres[i][j] == 'b') return 1;
			}
		}
	}
	return 0;
}
static int red(char spheres[5][5], int x, int y)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (spheres[i][j] == 'r')
			{
				if (!(i == x && j == y))
				{
					return 0;
				}
				return 1;
			}
		}
	}
	return 1;
}
static int orangePossible(char spheres[5][5], int x, int y)
{
	int orangeSpawnPlaceCount = 0;
	if (x > 0)
		if (spheres[x - 1][y] == 'o' || spheres[x - 1][y] == ' ') orangeSpawnPlaceCount += 1;
	if (y > 0)
		if (spheres[x][y - 1] == 'o' || spheres[x][y - 1] == ' ') orangeSpawnPlaceCount += 1;
	if (x < 4)
		if (spheres[x + 1][y] == 'o' || spheres[x + 1][y] == ' ') orangeSpawnPlaceCount += 1;
	if (y < 4)
		if (spheres[x][y + 1] == 'o' || spheres[x][y + 1] == ' ') orangeSpawnPlaceCount += 1;

	return (orangeSpawnPlaceCount >= 2);
}
static int predictSpheres(char spheres[5][5], char sphereprediction[5][5])
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			sphereprediction[i][j] = 'x';
			if (!teal(spheres, i, j)) sphereprediction[i][j] = ' ';
			if (!green(spheres, i, j)) sphereprediction[i][j] = ' ';
			if (!yellow(spheres, i, j)) sphereprediction[i][j] = ' ';
			if (!orange(spheres, i, j)) sphereprediction[i][j] = ' ';
			if (!red(spheres, i, j)) sphereprediction[i][j] = ' ';
			if (blue(spheres, i, j)) sphereprediction[i][j] = ' ';
			if (!orangePossible(spheres, i, j)) sphereprediction[i][j] = ' ';
			if (i == 2 && j == 2) sphereprediction[i][j] = ' ';
		}
	}
	return 0;
}

int oc(void)
{
	char spheres[5][5];
	char sphereprediction[5][5] = { 0 };
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			spheres[i][j] = ' ';
			sphereprediction[i][j] = 'x';
		}


	//int originalMode = _setmode(_fileno(stdout), _O_WTEXT);

	int row = 0, col = 0;
	predictSpheres(spheres, sphereprediction);
#ifdef _WIN32
	while (1)
	{
		resetCursor();
		drawBoard(spheres, sphereprediction, row, col);

		int ch = _getch();
		if (ch == 27) break; // ESC
		if (ch == 'b' || ch == 'y' || ch == 'r' ||
			ch == 'g' || ch == 'o' || ch == 't')
		{
			spheres[row][col] = ch;
			predictSpheres(spheres, sphereprediction);
		}
		if (ch == 8)
		{
			spheres[row][col] = ' ';
			predictSpheres(spheres, sphereprediction);
		}
		if (ch == 224) {
			ch = _getch();
			if (ch == 72 && row > 0) row--; // up
			if (ch == 80 && row < 4) row++; // down
			if (ch == 75 && col > 0) col--; // left
			if (ch == 77 && col < 4) col++; // right
			if (ch == 0x53)
			{
				spheres[row][col] = ' ';
				predictSpheres(spheres, sphereprediction);
			}
		}
	}
#elif defined(__linux__)


	initscr();
	cbreak();
	noecho(); 
	keypad(stdscr, TRUE);
	nodelay(stdscr, FALSE);

	while (1) 
	{
		resetCursor();
		drawBoard(spheres, sphereprediction, row, col);

		int ch = getch();

		if (ch == 27) break; // ESC
		if (ch == KEY_UP && row > 0) row--;
		if (ch == KEY_DOWN && row < 4) row++;
		if (ch == KEY_LEFT && col > 0) col--;
		if (ch == KEY_RIGHT && col < 4) col++;

		if (ch == 'b' || ch == 'y' || ch == 'r' ||
			ch == 'g' || ch == 'o' || ch == 't')
		{
			spheres[row][col] = ch;
			predictSpheres(spheres, sphereprediction);
		}

		if (ch == KEY_BACKSPACE || ch == 127) {
			spheres[row][col] = ' ';
			predictSpheres(spheres, sphereprediction);
		}
	}

	endwin();
#endif

	//_setmode(_fileno(stdout), originalMode);
	return 0;
}
