#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>
#include <time.h>
#pragma warning(disable:4996)

#define CON 100
#define LINE 25


typedef struct Player {
	int x;
	int y;
}P;

typedef struct Star {
	int x;
	int y;
}S;

P pxy = { 0, };
S sxy = { 0, };

int score_g = 0;


void Setting();

bool Key(int Key);

void Go(int x, int y);

void Main_Loop();


int main()
{
	Setting();

	sxy.x = rand() % CON;
	sxy.y = rand() % LINE;

	Main_Loop();

	return 0;
}


void Main_Loop()
{
	for (;;)
	{
		if (Key(VK_DOWN))
		{
			pxy.y++;
			if (pxy.y > LINE - 1)
				pxy.y--;
		}
		if (Key(VK_UP))
		{
			pxy.y--;
			if (pxy.y < 0)
				pxy.y++;
		}
		if (Key(VK_LEFT))
		{
			pxy.x--;
			if (pxy.x < 0)
				pxy.x++;
		}
		if (Key(VK_RIGHT))
		{
			pxy.x++;
			if (pxy.x > CON - 1)
				pxy.x--;
		}

		if (pxy.x == sxy.x && pxy.y == sxy.y)
		{
			score_g++;
			main();
		}

		Go(pxy.x, pxy.y);
		printf("o");
		Go(sxy.x, sxy.y);
		printf("@");
		Go(0, LINE);
		printf("Á¡¼ö : %d", score_g);
		Sleep(25);
		system("cls");
	}
}

void Go(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

bool Key(int Key)
{
	return ((GetAsyncKeyState(Key) & 0x8000) != 0);
}

void Setting()
{
	CONSOLE_CURSOR_INFO Cursor;
	Cursor.dwSize = 1;
	Cursor.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Cursor);

	system("title Maze");
	char command[50];
	sprintf(command, "mode con cols=%d lines=%d", CON, LINE + 1);
	system(command);

	srand((unsigned int)time(NULL));
}