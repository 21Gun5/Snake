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
using namespace std;

/*
蛇如何移动？
1. 初始化：3节蛇（包括头
2. 清除蛇尾：将蛇尾打印空（暂时清空而已
3. 是否吃到：吃到不变，未吃到，彻底删除蛇尾
4. 让蛇跑：新加蛇头（尾巴去掉，中间不变，新加蛇头；尾替代头，中间不变，而非后者替代前者，牵涉所有蛇体
5. 画蛇
*/

/*
读档时的蛇如何？
1. 存档时是在movesnake函数中
2. 之前就经历过了iseat函数，蛇尾被去掉了
3. 因此保存的蛇是少一节蛇尾的
4. 而在读取蛇后，还有经历一此iseat函数，还要再去一节蛇尾，这样就少了两节，必然不可
5. 因此，在还未保存蛇时，经历的第一次iseat时，即第一次去蛇尾时，将蛇尾保存为成员变量
6. 保存文件时，将蛇尾也保存，这样在读取时也取出来，将其pushback进蛇身，弥补之
7. 此外，将障碍数及蛇节数，作为全局变量，也写入并读取，因为二类都有vector成员，需要通过其来遍历读入
*/

int main()
{
	//0. 定义各对象指针，后续在if中赋值，突破局部变量的局限
	CSnake* psnake = NULL;//初始化是个好习惯，高老师如是说道
	CBarrier* pbarrier = NULL;
	CFood* pfood = NULL;

	// 1. 初始化及欢迎界面
	GameInit();
	DrawWelcome();

	// 2. 用户想干嘛？
	int op = HandleSelect();
	//2.1 若开启新游戏，则各对象有参实例化
	if (op == 1)
	{
		psnake = new CSnake(UP);//方向为UP
		int oop = HandleSelectMap();
		if (oop == 1)//若是选择自定义的地图
		{
			pbarrier = new CBarrier;
			LoadMap(*pbarrier);
		}
		else//系统默认地图，可选择难度
		{
			HandleSelectLevel();
			pbarrier = new CBarrier(psnake->m_SnakeBody, g_LevelBarrsize);//默认为20个，也可自定义
		}
		pfood = new CFood(psnake->m_SnakeBody, pbarrier->m_BarrArr);
	}
	//2.2 若读档，从文件读取，则各对象无参实例化，以接受数据
	else if (op == 2)
	{
		psnake = new CSnake;
		pbarrier = new CBarrier;
		pfood = new CFood;
		LoadGame(*psnake, *pbarrier, *pfood);
	}
	else if (op == 3)
	{
		SaveMap();
		//DrawMouse();
	}
	// 2.3 退出游戏
	else if (op == 0)
	{
		return 0;
	}

	// 3. 打印地图及帮助
	DrawMap();
	DrawGameHelp();

	// 4. 游戏主循环
	while (g_isRunning)
	{
		// 4.1 打印游戏信息、食物、障碍物
		DrawGameInfo(psnake->GetSnakeSize(), pbarrier->GetBarrSize());	//打印分数等信息
		pfood->DrawFood();					//打印食物
		pbarrier->DrawBarr();//打印障碍物

		// 4.2 让蛇移动并将其打印
		psnake->ClearSnake();					//清理蛇尾
		psnake->IsEatenFood(*pfood, pbarrier->m_BarrArr);			//是否吃到食物
		psnake->MoveSnake(*psnake,*pbarrier,*pfood);					//让蛇跑起来
		psnake->DrawSanke();					//画蛇

		// 4.3 判断是否存活
		if (!psnake->IsAlive(pbarrier->m_BarrArr))				//是否活着
		{
			GameOver(psnake->GetSnakeSize());
			break;
		}
		// 4.4 控制游戏速度
		Sleep(g_SleepTime);
	}

	//5. 消耗多余字符，用户按键后才会显示系统信息
	cin.get();
	cin.get();

	return 0;
}