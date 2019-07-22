#include <iostream>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <vector>
#include "data.h"
#include "snake.h"
#include "func.h"
using namespace std;

//无参构造，读取文件时，对象接收者为空
CSnake::CSnake(){}

//有参构造
CSnake::CSnake(int dir) :m_Dir(dir), m_IsAlive(true)
{
	COORD snakeHead;
	//snakeHead.X = MAP_X / 2 - 15;
	snakeHead.X = MAP_X_WALL / 4;//因为x1B，y2B，故x/4，而y/2
	snakeHead.Y = MAP_Y / 2;

	m_SnakeBody.push_back(snakeHead);
	snakeHead.Y++;
	m_SnakeBody.push_back(snakeHead);
	snakeHead.Y++;
	m_SnakeBody.push_back(snakeHead); //初始蛇身长度三节
}

//监听键盘
void CSnake::ListenKeyBoard()
{
	char ch = 0;

	if (_kbhit())				//kbhit非阻塞函数 
	{
		ch = _getch();			//使用 getch 函数获取键盘输入
		//PlaySoundA("conf\\click.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		switch (ch)
		{
		case 'w':
		case 'W':
			if (this->m_Dir == DOWN)
				break;
			this->m_Dir = UP;
			break;
		case 's':
		case 'S':
			if (this->m_Dir == UP)
				break;
			this->m_Dir = DOWN;
			break;
		case 'a':
		case 'A':
			if (this->m_Dir == RIGHT)
				break;
			this->m_Dir = LEFT;
			break;
		case 'd':
		case 'D':
			if (this->m_Dir == LEFT)
				break;
			this->m_Dir = RIGHT;
			break;
			//暂停及恢复
		case 'q':
		{	//case里定义变量要加大括号

			setColor(12, 0);
			gotoxy(MAP_X_WALL + 2, 1);
			cout << "PAUSE" << endl;//暂停的状态标识
			gotoxy(MAP_X_WALL + 2, 2);
			cout << "1. 回到游戏" << endl;
			gotoxy(MAP_X_WALL + 2, 3);
			cout << "2. 保存游戏" << endl;
			gotoxy(MAP_X_WALL + 2, 4);
			cout << "3. 退出游戏" << endl;

			char tmp = _getch();	//利用阻塞函数暂停游戏

			switch (tmp)
			{
			case '1'://恢复游戏
				gotoxy(MAP_X_WALL + 2, 1);
				cout << "     " << endl;//恢复游戏时，将提示清空
				gotoxy(MAP_X_WALL + 2, 2);
				cout << "           " << endl;
				gotoxy(MAP_X_WALL + 2, 3);
				cout << "           " << endl;
				gotoxy(MAP_X_WALL + 2, 4);
				cout << "           " << endl;
				break;
			case '2'://存档
				SaveGame();
				break;
			case '3'://退出游戏
				GameOver(this->m_SnakeBody.size()+1);//分数那是-3的，而蛇跑时会有删除尾巴，+3-1应该为+2，为何+1正确？
				g_isRunning = false;
				break;
			default:
				break;
			}


		}

		//case ' ':
		//	g_isRunning = true;
		//	break;
		//键盘控制速度
		//case '+':
		//	if (g_speed >= 25)
		//	{
		//		g_speed -= 25;
		//	}
		//	break;
		//case '-':
		//	if (g_speed < 250)
		//	{
		//		g_speed += 25;
		//	}
		//	break;

		default:
			break;
		}
	}
}

//移动贪吃蛇
void CSnake::MoveSnake()
{
	ListenKeyBoard();//监听键盘
	COORD snaHead = m_SnakeBody[0];//蛇头
	switch (m_Dir)
	{
	case UP:
		snaHead.Y--;
		break;
	case DOWN:
		snaHead.Y++;
		break;
	case LEFT:
		snaHead.X--;
		break;
	case RIGHT:
		snaHead.X++;
		break;
	}
	//插入移动后新的蛇头（先去蛇尾，再加蛇头）
	m_SnakeBody.insert(m_SnakeBody.begin(), snaHead);
}

//是否吃到食物
bool CSnake::IsEatenFood(CFood& food, vector<COORD>& barArr)
{
	COORD foodPos = food.GetFoodPos();	//食物坐标
	//坐标重合即吃到食物（吃到后则重新生成食物，不删除蛇尾

	if (m_SnakeBody[HEAD].X == foodPos.X && m_SnakeBody[HEAD].Y == foodPos.Y)
	{
		//PlaySoundA("conf\\eat.wav", NULL, SND_ASYNC | SND_NODEFAULT);

		food.GetRandomPos(m_SnakeBody, barArr);
		return true;
	}
	else
	{
		//没有吃到食物，删除蛇尾
		m_SnakeBody.erase(m_SnakeBody.end() - 1);
		return false;
	}
}

//判断生死
bool CSnake::IsAlive(vector<COORD>& barArr)
{
	//是否撞地图边界
	if (m_SnakeBody[HEAD].X <= 0 ||
		m_SnakeBody[HEAD].X >= MAP_X_WALL / 2 - 1 ||//因为x是y一半，故/2，好多这样的问题，x都要是y的一半
		m_SnakeBody[HEAD].Y <= 0 ||
		m_SnakeBody[HEAD].Y >= MAP_Y - 1)
	{
		//PlaySoundA("conf\\duang.wav", NULL, SND_ASYNC | SND_NODEFAULT);

		m_IsAlive = false;
		return m_IsAlive;
	}
	//是否撞自己（头和身相撞，蛇身重叠不算）
	for (int i = 1; i < m_SnakeBody.size(); i++)
	{
		//PlaySoundA("conf\\duang.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		if (m_SnakeBody[i].X == m_SnakeBody[HEAD].X && m_SnakeBody[i].Y == m_SnakeBody[HEAD].Y)
		{
			m_IsAlive = false;
			return m_IsAlive;
		}
	}
	//是否撞地图内障碍物
	for (int i = 0; i < barArr.size(); i++)
	{
		//PlaySoundA("conf\\duang.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		if (barArr[i].X == m_SnakeBody[HEAD].X && barArr[i].Y == m_SnakeBody[HEAD].Y)
		{
			m_IsAlive = false;
			return m_IsAlive;
		}
	}
	//m_IsAlive = true;
	return m_IsAlive;
}

//画蛇
void CSnake::DrawSanke()
{
	setColor(10, 0);	//设置蛇为绿色

	for (int i = 0; i < m_SnakeBody.size(); i++)
	{
		//□■
		//gotoxy(m_SnakeBody[i].X, m_SnakeBody[i].Y);//here
		gotoxy4s(m_SnakeBody[i].X, m_SnakeBody[i].Y);

		//蛇头与蛇身设置不同图案
		if (i == 0)
		{
			cout << "◎";
		}
		else
		{
			cout << "■";
		}
		
		//cout << "*";//here
	}

	setColor(7, 0);		//恢复原来颜色
}

//清除蛇尾
void CSnake::ClearSnake()
{
	//画蛇前必做，最后一节蛇身用空格表示
	//gotoxy(m_SnakeBody[m_SnakeBody.size() - 1].X, m_SnakeBody[m_SnakeBody.size() - 1].Y);
	gotoxy4s(m_SnakeBody[m_SnakeBody.size() - 1].X, m_SnakeBody[m_SnakeBody.size() - 1].Y);//here


	cout << "  ";//here
	//cout << " ";
}

//获取蛇长
int CSnake::GetSnakeSize()
{
	//蛇长作为分数参考，要实时显示，故放至循环内
	return m_SnakeBody.size();
}