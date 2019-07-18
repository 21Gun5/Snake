#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "setting.h"

int dir[4][2] = { { 0,1 },{ 0,-1 },{ 1,0 },{ -1,0 } };
int g_speed = 100;//结合sleep使用，越大越慢

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

void CSetting::GameInit()
{
	//设置游戏窗口大小here
	char buffer[32];
	sprintf_s(buffer, "mode con cols=%d lines=%d", window_width, window_height);
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