
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


static void drawBoard(char spheres[5][5], int sphereprediction[5][5], int selRow, int selCol)
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
#ifdef WIN32
		case(0):
			wprintf(L"│    Fill the squares with your selections in the $oq sphere minigame.");
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
#elif defined(__linux__)
		case(0):
			addwstr(L"│    Fill the squares with your selections in the $oq sphere minigame.");
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
#ifdef WIN32
			if (i == selRow && j == selCol)
				setColour(getBackgroundColourForValue('w'));
			else
				setColour(getBackgroundColourForValue(spheres[i][j]));

			if(spheres[i][j] != ' ')
				wprintf(L"│  %c │ ", spheres[i][j]);
			else if (sphereprediction[i][j] > 0)
				wprintf(L"│  %d │ ", sphereprediction[i][j]);
			else if (sphereprediction[i][j] == 0)
				wprintf(L"│  ? │ ");
			else if (sphereprediction[i][j] == -1)
				wprintf(L"│  0 │ ");
			else
				wprintf(L"│ %d │ ", sphereprediction[i][j]);
			setColour(7);
#elif defined(__linux__)
			if (spheres[i][j] != ' ')
				swprintf(buf, 256, L"│  %c │ ", spheres[i][j]);
			else if (sphereprediction[i][j] > 0)
				swprintf(buf, 256, L"│  %d │ ", sphereprediction[i][j]);
			else if (sphereprediction[i][j] == 0)
				swprintf(buf, 256, L"│  ? │ ");
			else if (sphereprediction[i][j] == -1)
				swprintf(buf, 256, L"│  0 │ ");
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
#ifdef WIN32
		case(0):
			wprintf(L"│    The higher the value of the surrounding squares, the higher the chance");
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
			addwstr(L"│    The higher the value of the surrounding squares, the higher the chance");
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
#ifdef WIN32
		wprintf(L"\n  │ ");
#elif defined(__linux__)
		mvaddwstr(4 + (3 * i), 0, L"  │ ");
#endif
		for (int j = 0; j < 5; j++)
		{
#ifdef WIN32
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
#ifdef WIN32
		case(0):
			wprintf(L"│    you will encounter a purple.");
			break;
		case(1):
			wprintf(L"│");
			break;
		case(2):
			wprintf(L"│    p - Purple   b - Blue   t - Teal   g - Green   y - Yellow   o - Orange");
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
				addwstr(L"│    you will encounter a purple.");
				break;
			case(1):
				addwstr(L"│");
				break;
			case(2):
				addwstr(L"│    p - Purple   b - Blue   t - Teal   g - Green   y - Yellow   o - Orange");
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


int countAdjacentPurple(char spheres[5][5], int x, int y)
{
	int score = 0;

	int dx[8] = { -1, -1, -1,  0, 0, 1, 1, 1 };
	int dy[8] = { -1,  0,  1, -1, 1,-1, 0, 1 };

	for (int i = 0; i < 8; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx >= 0 && nx < 5 && ny >= 0 && ny < 5)
		{
			if (spheres[nx][ny] == 'p') score += 1;
		}
	}

	return score;
}

int sphereScore(char spheres[5][5], int x, int y)
{
	int total = 0;
	switch (spheres[x][y])
	{
	case 't': 
		total = (1 - countAdjacentPurple(spheres, x, y));
		if (total > 0) return total;
		goto purpleFound;
	case 'g': 
		total = (2 - countAdjacentPurple(spheres, x, y));
		if (total > 0) return total;
		goto purpleFound;
	case 'y': 
		total = (3 - countAdjacentPurple(spheres, x, y));
		if (total > 0) return total;
		goto purpleFound;
	case 'o': 
		total = (4 - countAdjacentPurple(spheres, x, y));
		if (total > 0) return total;
		goto purpleFound;
	case 'b': 
	purpleFound:
		return -1;
	case 'p': 

		return -2;
	default:  
		return 0;
	}
}

int countAdjacent(char spheres[5][5], int x, int y)
{
	int score = 0;
	//int adjacentNonEmptyOrPurple = 0;
	int dx[8] = { -1, -1, -1,  0, 0, 1, 1, 1 };
	int dy[8] = { -1,  0,  1, -1, 1,-1, 0, 1 };

	for (int i = 0; i < 8; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx >= 0 && nx < 5 && ny >= 0 && ny < 5)
		{
			int s = sphereScore(spheres, nx, ny);
			if (s >= 1) score++;

		}
	}
	return score;
}

int scoreAdjacent(char spheres[5][5], int x, int y)
{
	int score = 0;
	int adjacentNonEmptyOrPurple = 0;
	int dx[8] = { -1, -1, -1,  0, 0, 1, 1, 1 };
	int dy[8] = { -1,  0,  1, -1, 1,-1, 0, 1 };

	for (int i = 0; i < 8; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx >= 0 && nx < 5 && ny >= 0 && ny < 5)
		{
			int s = sphereScore(spheres, nx, ny);

			if (s == -1)
				return -1;
			if (s != -2)
				score += s;
			if (spheres[nx][ny] != ' ' && spheres[nx][ny] != 'p') {
				adjacentNonEmptyOrPurple = 1;
			}

		}
	}
	if (score == 0 && adjacentNonEmptyOrPurple)
	{
		return -1;
	}
	return score;
}


void removeImpossibleSpaces(char spheres[5][5], int sphereprediction[5][5], int purpleCount)
{
	int adjacentCount = 0;
	for (int i = 1; i < 4; i += 2)
	{
		for (int j = 1; j < 4; j += 2)
		{
			if (spheres[i][j] == 't') adjacentCount += 1;
			if (spheres[i][j] == 'g') adjacentCount += 2;
			if (spheres[i][j] == 'y') adjacentCount += 3;
			if (spheres[i][j] == 'o') adjacentCount += 4;
			if (spheres[i][j] == 'p') return; //Causes impossible situations, need more testing=
			adjacentCount -= countAdjacentPurple(spheres, i, j);
		}
	}
	if (adjacentCount <= 7) sphereprediction[2][2] = -1;
	if (adjacentCount <= (4 - purpleCount))
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (countAdjacent(spheres, i, j) >= 2) sphereprediction[i][j] = -1;
			}
		}
	}
}

void predictSpheres(char spheres[5][5], int sphereprediction[5][5])
{
	int purpleCount = 0;
	int adjacentToSelectedSphere = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (spheres[i][j] == 'p') purpleCount++;
			sphereprediction[i][j] = scoreAdjacent(spheres, i, j);
			if (sphereprediction[i][j] != 0) adjacentToSelectedSphere++;
		}
	}
	if (adjacentToSelectedSphere >= 21)
	{
		if (spheres[1][1] != ' ' && spheres[1][3] != ' ' && spheres[3][1] != ' ' && spheres[3][3] != ' ')
		{
			removeImpossibleSpaces(spheres, sphereprediction, purpleCount);
		}
	}
}

int oq(void)
{
	//int originalMode = _setmode(_fileno(stdout), _O_WTEXT);
	char spheres[5][5];
	int sphereprediction[5][5] = { 0 };
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			spheres[i][j] = ' ';
		}
	int row = 0, col = 0;
	clearScreen();
#ifdef WIN32
	while (1) {
		resetCursor();
		drawBoard(spheres, sphereprediction, row, col);

		int ch = _getch();
		if (ch == 27) break;
		if (ch == 'b' || ch == 'y' || ch == 'p' ||
			ch == 'g' || ch == 'o' || ch == 't'
			)
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
			if (ch == 72 && row > 0) row--;
			if (ch == 80 && row < 4) row++;
			if (ch == 75 && col > 0) col--;
			if (ch == 77 && col < 4) col++;
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

		if (ch == 27) break; 
		if (ch == KEY_UP && row > 0) row--;
		if (ch == KEY_DOWN && row < 4) row++;
		if (ch == KEY_LEFT && col > 0) col--;
		if (ch == KEY_RIGHT && col < 4) col++;

		if (ch == 'b' || ch == 'y' || ch == 'p' ||
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

	endwin(); // restore terminal
#endif
	//_setmode(_fileno(stdout), originalMode);
	return 0;
}