#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include "data.h"
#include "func.h"
#include "food.h"
#include "snake.h"
#include "barrier.h"
#pragma comment(lib,"winmm.lib")//播放BGM
using namespace std;

int main()
{
	/*
	蛇如何移动？
	1. 初始化：3节蛇（包括头
	2. 清除蛇尾：将蛇尾打印空（暂时清空而已
	3. 是否吃到：吃到不变，未吃到，彻底删除蛇尾
	4. 让蛇跑：新加蛇头（尾巴去掉，中间不变，新加蛇头；尾替代头，中间不变，而非后者替代前者，牵涉所有蛇体
	5. 画蛇
	*/

	//各对象实例化
	
	CSnake snake;
	CBarrier barrier(15);//默认为20个，也可自定义
	CFood food(snake.m_SnakeBody, barrier.m_BarrArr);
	
	bool isRunning = 0;
	//bool isRunning = 1;//恒为1，测试用

	GameInit();				//初始化

	DrawWelcome();			//欢迎界面

	char ch = _getch();
	switch (ch)
	{
	case '1':
		isRunning = true;
		break;
	case '2':
		gotoxy(MAP_X / 2 - 10, MAP_Y / 2 + 3);
		cout << "Bye！" << endl;
		//cin.get();
		return 0;
	default:
		gotoxy(MAP_X / 2 - 10, MAP_Y / 2 + 3);
		cout << "输入错误";
		return 0;
	}

	//system("pause");		//提示按键到下一界面
	DrawMap();				//打印地图边框
	DrawGameHelp();			//打印相关信息

	while (true && isRunning)
	{
		DrawGameInfo(snake.GetSnakeSize(),barrier.GetBarrSize());	//打印分数等信息
		food.DrawFood();					//打印食物
		barrier.DrawBarr();//打印障碍物
		snake.ClearSnake();					//清理蛇尾
		snake.IsEatenFood(food, barrier.m_BarrArr);			//是否吃到食物
		snake.MoveSnake();					//让蛇跑起来
		snake.DrawSanke();					//画蛇

		if (!snake.IsAlive(barrier.m_BarrArr))				//是否活着
		{
			GameOver(snake.GetSnakeSize());
			break;
		}
		Sleep(g_speed);						//控制游戏速度
	}

	//消耗多余字符，避免打印系统提示
	cin.get();
	//cin.get();

	return 0;
}