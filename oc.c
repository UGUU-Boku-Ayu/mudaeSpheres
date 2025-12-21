#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <wchar.h>
#include <conio.h>
#include <windows.h>
#include "oCommon.h"



static void drawBoard(char sphere[5][5], char sphereprediction[5][5], int selRow, int selCol)
{
	wprintf(L"       a      b      c      d      e        Info:\n");
	wprintf(L"  ┌────────────────────────────────────┐\n");
	for (int i = 0; i < 5; i++) {
		wprintf(L"  │ ");
		for (int j = 0; j < 5; j++)
		{
			if (i == selRow && j == selCol)
				setColour(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
			else
				setColour(getBackgroundColourForValue(sphere[i][j]));

			wprintf(L"┌────┐ ");
			setColour(7);
		}
		switch (i)
		{
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
		}
		wprintf(L"\n %d│ ", i + 1);
		for (int j = 0; j < 5; j++)
		{
			if (i == selRow && j == selCol)
				setColour(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
			else
				setColour(getBackgroundColourForValue(sphere[i][j]));

			if (sphere[i][j] != ' ')
				wprintf(L"│  %c │ ", sphere[i][j]);
			else
				wprintf(L"│  %c │ ", sphereprediction[i][j]);
			setColour(7);
		}
		switch (i)
		{
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
		}
		wprintf(L"\n  │ ");
		for (int j = 0; j < 5; j++)
		{
			if (i == selRow && j == selCol)
				setColour(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
			else
				setColour(getBackgroundColourForValue(sphere[i][j]));

			wprintf(L"└────┘ ");
			setColour(7);
		}
		switch (i)
		{
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
	}


}
static int teal(char sphere[5][5], int x, int y)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (sphere[i][j] == 't')
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
static int yellow(char sphere[5][5], int x, int y)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (sphere[i][j] == 'y')
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
static int orange(char sphere[5][5], int x, int y)
{
	int hasOrange = 0;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (sphere[i][j] == 'o')
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



static int green(char sphere[5][5], int x, int y)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (sphere[i][j] == 'g')
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
static int blue(char sphere[5][5], int x, int y)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (i == x || j == y || i - j == x - y || i + j == x + y)
			{
				if (sphere[i][j] == 'b') return 1;
			}
		}
	}
	return 0;
}
static int red(char sphere[5][5], int x, int y)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (sphere[i][j] == 'r')
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
static int orangePossible(char sphere[5][5], int x, int y)
{
	int orangeSpawnPlaceCount = 0;
	if (x > 0)
		if (sphere[x - 1][y] == 'o' || sphere[x - 1][y] == ' ') orangeSpawnPlaceCount += 1;
	if (y > 0)
		if (sphere[x][y - 1] == 'o' || sphere[x][y - 1] == ' ') orangeSpawnPlaceCount += 1;
	if (x < 4)
		if (sphere[x + 1][y] == 'o' || sphere[x + 1][y] == ' ') orangeSpawnPlaceCount += 1;
	if (y < 4)
		if (sphere[x][y + 1] == 'o' || sphere[x][y + 1] == ' ') orangeSpawnPlaceCount += 1;

	return (orangeSpawnPlaceCount >= 2);
}
static int predictSphere(char sphere[5][5], char sphereprediction[5][5])
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			sphereprediction[i][j] = 'x';
			if (!teal(sphere, i, j)) sphereprediction[i][j] = ' ';
			if (!green(sphere, i, j)) sphereprediction[i][j] = ' ';
			if (!yellow(sphere, i, j)) sphereprediction[i][j] = ' ';
			if (!orange(sphere, i, j)) sphereprediction[i][j] = ' ';
			if (!red(sphere, i, j)) sphereprediction[i][j] = ' ';
			if (blue(sphere, i, j)) sphereprediction[i][j] = ' ';
			if (!orangePossible(sphere, i, j)) sphereprediction[i][j] = ' ';
			if (i == 2 && j == 2) sphereprediction[i][j] = ' ';
		}
	}
	return 0;
}

int oc(void)
{
	char sphere[5][5];
	char sphereprediction[5][5] = { 0 };
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			sphere[i][j] = ' ';
			sphereprediction[i][j] = 'x';
		}
			

	int originalMode = _setmode(_fileno(stdout), _O_WTEXT);

	int row = 0, col = 0;
	predictSphere(sphere, sphereprediction);
	while (1) {
		resetCursor();
		drawBoard(sphere, sphereprediction, row, col);

		int ch = _getch();
		if (ch == 27) break; // ESC
		if (ch == 'b' || ch == 'y' || ch == 'r' ||
			ch == 'g' || ch == 'o' || ch == 't')
		{
			sphere[row][col] = ch;
			predictSphere(sphere, sphereprediction);
		}
		if (ch == 8)
		{
			sphere[row][col] = ' ';
			predictSphere(sphere, sphereprediction);
		}
		if (ch == 224) {
			ch = _getch();
			if (ch == 72 && row > 0) row--; // up
			if (ch == 80 && row < 4) row++; // down
			if (ch == 75 && col > 0) col--; // left
			if (ch == 77 && col < 4) col++; // right
			if (ch == 0x53)
			{
				sphere[row][col] = ' ';
				predictSphere(sphere, sphereprediction);
			}
		}
		
	}

	_setmode(_fileno(stdout), originalMode);
	return 0;
}
