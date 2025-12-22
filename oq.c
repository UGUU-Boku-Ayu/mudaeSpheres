#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <wchar.h>
#include <conio.h>
#include <windows.h>
#include "oCommon.h"



static void drawBoard(char spheres[5][5], int sphereprediction[5][5], int selRow, int selCol)
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
				setColour(getBackgroundColourForValue(spheres[i][j]));

			wprintf(L"┌────┐ ");
			setColour(7);
		}
		switch (i)
		{
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
		}
		wprintf(L"\n %d│ ", i + 1);
		for (int j = 0; j < 5; j++)
		{
			if (i == selRow && j == selCol)
				setColour(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
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
		}
		switch (i)
		{
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
		}
		wprintf(L"\n  │ ");
		for (int j = 0; j < 5; j++)
		{
			if (i == selRow && j == selCol)
				setColour(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
			else
				setColour(getBackgroundColourForValue(spheres[i][j]));

			wprintf(L"└────┘ ");
			setColour(7);
		}
		switch (i)
		{
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
	}


}


countAdjacentPurple(char spheres[5][5], int x, int y)
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


void predictSpheres(char spheres[5][5], int sphereprediction[5][5])
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			sphereprediction[i][j] = countAdjacent(spheres, i, j);
			if (i == 2 && j == 2)
			{
				
			}
		}
	}
	if (spheres[1][1] == 't' && spheres[1][3] == 't' && spheres[3][1] == 't' && spheres[3][3] == 't')
	{
		for (int i = 0; i < 5; i++)
		{
			sphereprediction[i][2] = -1;
			sphereprediction[2][i] = -1;
		}
	}
}

int oq(void)
{
	char spheres[5][5];
	int sphereprediction[5][5] = { 0 };
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			spheres[i][j] = ' ';
		}
	int row = 0, col = 0;
	clearScreen();
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
}