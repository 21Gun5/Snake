﻿#include <iostream>
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
using namespace std;

/*
蛇如何移动？
1. 初始化：3节蛇（包括头
2. 清除蛇尾：将蛇尾打印空（暂时清空而已
3. 是否吃到：吃到不变，未吃到，彻底删除蛇尾
4. 让蛇跑：新加蛇头（尾巴去掉，中间不变，新加蛇头；尾替代头，中间不变，而非后者替代前者，牵涉所有蛇体
5. 画蛇
*/

int main()
{
	// 1. 初始化及欢迎界面
	GameInit();
	DrawWelcome();

	// 2. 用户想干嘛？
	int op = HandleSelect();

	//2.1 若开启新游戏，则各对象有参实例化
	if (op == 1)
	{
		static CSnake snake(UP);//方向为UP
		static CBarrier barrier(snake.m_SnakeBody, 15);//默认为20个，也可自定义
		static CFood food(snake.m_SnakeBody, barrier.m_BarrArr);
	}
	//2.2 若读档，从文件读取，则各对象无参实例化，以接受数据
	else if (op == 2)
	{
		static CSnake snake;
		static CBarrier barrier;
		static CFood food;
		LoadGame();
	}
	// 2.3 退出游戏
	else if (op == 0)
	{
		return 0;
	}

	//CSnake snake(UP);//方向为UP
	//CBarrier barrier(snake.m_SnakeBody, 15);//默认为20个，也可自定义
	//CFood food(snake.m_SnakeBody, barrier.m_BarrArr);

	// 3. 打印地图及帮助
	DrawMap();
	DrawGameHelp();

	// 4. 游戏主循环
	while (g_isRunning)
	{
		// 4.1 打印游戏信息、食物、障碍物
		DrawGameInfo(snake.GetSnakeSize(), barrier.GetBarrSize());	//打印分数等信息
		food.DrawFood();					//打印食物
		barrier.DrawBarr();//打印障碍物

		// 4.2 让蛇移动并将其打印
		snake.ClearSnake();					//清理蛇尾
		snake.IsEatenFood(food, barrier.m_BarrArr);			//是否吃到食物
		snake.MoveSnake();					//让蛇跑起来
		snake.DrawSanke();					//画蛇

		// 4.3 判断是否存活
		if (!snake.IsAlive(barrier.m_BarrArr))				//是否活着
		{
			GameOver(snake.GetSnakeSize());
			break;
		}

		// 4.4 控制游戏速度
		Sleep(g_speed);
	}

	//5. 消耗多余字符，用户按键后才会显示系统信息
	cin.get();
	cin.get();

	return 0;
}