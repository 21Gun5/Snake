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
	// 1.定义各对象指针
	CSnake* psnake = NULL;
	CBarrier* pbarrier = NULL;
	CFood* pfood = NULL;

	// 2.初始化及欢迎界面
	GameInit();
	DrawWelcome();

	// 3.用户选择
	int action = SelectAction();
	if (action == 新游戏)
	{
		psnake = new CSnake(UP);
		// 01-选谁的地图
		int whoMap = SelectWhoMap();
		// 1.1-系统默认地图
		if (whoMap == 系统默认)
		{
			SelectLevel();		//设置难度等级
			pbarrier = new CBarrier(psnake->m_SnakeBody, g_LevelBarrsize);//默认为20个，也可自定义
		}
		// 1.2-用户自定义地图
		else if(whoMap == 自定义)
		{
			// 02-选何时的地图
			int whenMap = SelectWhenMap();
			// 2.1-新建地图
			if (whenMap == 新建地图)
			{
				string str=SetMap();
				pbarrier = new CBarrier;//空对象以接收数据
				//string str = "map.i";
				LoadMap(*pbarrier,str);
			}
			// 2.2-之前建的旧地图
			else if(whenMap == 已有地图)//here
			{
				string str = ShowMaps();
				pbarrier = new CBarrier;
				LoadMap(*pbarrier,str);

				//pbarrier = new CBarrier;
				//LoadMap(*pbarrier);
			}
		}
		pfood = new CFood(psnake->m_SnakeBody, pbarrier->m_BarrArr);
	}
	else if (action == 读取游戏)
	{
		string str = ShowGames();

		//创建空对象，以接受文件数据
		psnake = new CSnake;
		pbarrier = new CBarrier;
		pfood = new CFood;
		LoadGame(*psnake, *pbarrier, *pfood,str);
	}
	else if (action == 退出游戏)
	{
		return 0;
	}

	// 4.边界及帮助
	DrawMapBorder();
	DrawGameHelp();

	// 5.主循环
	while (g_isRunning)
	{
		//游戏信息、食物、障碍物
		DrawGameInfo(psnake->GetSnakeSize(), pbarrier->GetBarrSize(),psnake->m_Blood);
		pfood->DrawFood();
		pbarrier->DrawBarr();

		//蛇移动及显示
		psnake->ClearSnakeTail();
		psnake->IsEatenFood(*pfood, pbarrier->m_BarrArr);
		psnake->MoveSnake(*psnake, *pbarrier, *pfood);
		psnake->DrawSanke();

		//是否存活
		if (!psnake->IsAlive(pbarrier->m_BarrArr))
		{
			GameOver(psnake->GetSnakeSize());
			break;
		}

		//控制速度
		Sleep(g_SleepTime);
	}

	// 6.消耗多余字符
	cin.get();
	cin.get();

	return 0;
}