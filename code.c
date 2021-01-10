#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>
#include <time.h>
#pragma warning(disable:4996) //비주얼 스튜디오 기준, 에러 방지

#define CON 100 //콘솔 가로
#define LINE 25 //콘솔 세로

// 플레이어 좌표 구조체
typedef struct Player {
	int x;
	int y;
}P;
// 별 좌표 구조체
typedef struct Star {
	int x;
	int y;
}S;

P pxy = { 0, };
S sxy = { 0, };

int score_g = 0; //점수


void Setting();

bool Key(int Key);

void Go(int x, int y);

void Main_Loop();


int main()
{
	Setting(); //기본 설정. 콘솔 크기, 커서 크기 등등

	sxy.x = rand() % CON; //별 x축 좌표 0 ~ CON - 1 사이 랜덤 값 대입
	sxy.y = rand() % LINE; //별 y축 좌표 0 ~ LINE - 1 사이 랜덤 값 대입

	Main_Loop(); //메인 반복문

	return 0;
}


void Main_Loop()
{
	for (;;)
	{
		if (Key(VK_DOWN)) //↑키가 입력됐다면
		{
			pxy.y++;
			if (pxy.y > LINE - 1) //콘솔을 벗어나면
				pxy.y--;
		}
		if (Key(VK_UP)) //↓키가 입력됐다면
		{
			pxy.y--;
			if (pxy.y < 0) //콘솔을 벗어나면
				pxy.y++;
		}
		if (Key(VK_LEFT)) //←키가 입력됐다면
		{
			pxy.x--;
			if (pxy.x < 0) //콘솔을 벗어나면
				pxy.x++;
		}
		if (Key(VK_RIGHT)) //→키가 입력됐다면
		{
			pxy.x++;
			if (pxy.x > CON - 1) //콘솔을 벗어나면
				pxy.x--;
		}

		if (pxy.x == sxy.x && pxy.y == sxy.y) //플레이어가 별에 닿으면
		{
			score_g++; //점수 증가
			main(); //점수가 증가한 score_g 변수를 사용하는 main 함수
		}

		Go(pxy.x, pxy.y);
		printf("o"); //플레이어 표시
		Go(sxy.x, sxy.y);
		printf("@"); //별 표시
		Go(0, LINE);
		printf("점수 : %d", score_g); //좌측 하단에 점수 표시
		Sleep(25); //0.025초 만큼 정지. 1000이 1초
		system("cls"); //화면 지우기. 잔상현상 방지
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
    //↑커서 가리는 코드
	system("title Maze");
	char command[50];
	sprintf(command, "mode con cols=%d lines=%d", CON, LINE + 1);
	system(command);
    //↑콘솔 크기 지정
	srand((unsigned int)time(NULL)); //rand()를 사용하기 위한 작업
}
