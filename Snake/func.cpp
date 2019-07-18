#include <iostream>
#include <windows.h>
#include <time.h>
#include "data.h"
#include "func.h"
using namespace std;

//欢迎界面
void DrawWelcome()
{
	cout << "Welcome!";
}

//打印地图边界
void DrawMap()
{
	system("cls");
	int i, j;
	for (i = 0; i < g_window_width; i++)
		cout << "#";
	cout << endl;
	for (i = 0; i < g_window_height - 2; i++)
	{
		for (j = 0; j < g_window_width; j++)
		{
			if (i == 13 && j >= g_window_width - 29)
			{
				cout << "#";
				continue;
			}

			if (j == 0 || j == g_window_width - 29 || j == g_window_width - 1)
			{
				cout << "#";
			}
			else
				cout << " ";

		}
		cout << endl;
	}
	for (i = 0; i < g_window_width; i++)
		cout << "#";

}

//游戏结束
void GameOver(int score)
{
	setColor(12, 0);
	gotoxy(g_window_width / 2 - 20, g_window_height / 2 - 5);
	cout << "GAME OVER! " << endl;;
	gotoxy(g_window_width / 2 - 20, g_window_height / 2 - 3);
	cout << "Scores: " << score << endl;
}

//打印分数
void DrawScore(int score)
{
	gotoxy(g_window_width - 22 + 14, 6);
	cout << "  ";
	gotoxy(g_window_width - 22 + 14, 4);
	cout << "  ";

	gotoxy(g_window_width - 22, 6);
	cout << "当前分数: " << score << endl;

}

//打印操作说明
void DrawGameInfo()
{
	gotoxy(g_window_width - 22, 18);
	cout << "操作说明：" << endl;
	gotoxy(g_window_width - 22, 20);
	cout << "W: 上    S: 下" << endl;
	gotoxy(g_window_width - 22, 22);
	cout << "A: 左    D: 右" << endl;
}

void GameInit()
{
	//设置游戏窗口大小here
	char buffer[32];
	sprintf_s(buffer, "mode con cols=%d lines=%d", g_window_width, g_window_height);
	system(buffer);
	//system("mode con cols = 80 lines = 40");

	//隐藏光标here
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态

	//初始化随机数种子
	srand((unsigned int)time(0));
}

//移动光标到指定位置
void gotoxy(int x, int y)
{
	COORD cur;//系统提供的坐标结构体
	cur.X = x;
	cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}

//设置颜色
void setColor(unsigned short ForeColor, unsigned short BackGroundColor)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//获取当前窗口句柄
	SetConsoleTextAttribute(handle, ForeColor + BackGroundColor * 0x10);//设置颜色
}