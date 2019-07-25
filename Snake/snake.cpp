#include <iostream>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <vector>
#include "data.h"
#include "snake.h"
#include "func.h"
using namespace std;

CSnake::CSnake() {}
CSnake::CSnake(int dir) :m_Dir(dir), m_IsAlive(true), m_Blood(3)//
{
	COORD snakeHead;
	snakeHead.X = MAP_X_WALL / 4;//因为x1B，y2B，故x/4，而y/2
	snakeHead.Y = MAP_Y / 2;

	m_SnakeBody.push_back(snakeHead);
	snakeHead.Y++;
	m_SnakeBody.push_back(snakeHead);
	snakeHead.Y++;
	m_SnakeBody.push_back(snakeHead); //初始蛇身长度三节
}
void CSnake::DrawSanke()
{
	setColor(10, 0);	//设为绿色
	for (int i = 0; i < m_SnakeBody.size(); i++)
	{
		GotoxyFor2(m_SnakeBody[i].X, m_SnakeBody[i].Y);
		if (i == 0)
		{
			cout << "◎";
		}
		else
		{
			cout << "■";
		}
	}
	setColor(7, 0);
}
void CSnake::ClearSnakeTail()
{
	//画蛇前必做，蛇尾清空
	GotoxyFor2(m_SnakeBody[m_SnakeBody.size() - 1].X, m_SnakeBody[m_SnakeBody.size() - 1].Y);
	cout << "  ";
}
int CSnake::GetSnakeSize()
{
	//蛇长作分数
	return m_SnakeBody.size();
}
bool CSnake::IsAlive(vector<COORD>& barArr)
{
	//是否撞边界
	if (m_SnakeBody[HEAD].X <= 0 ||
		m_SnakeBody[HEAD].X >= MAP_X_WALL / 2 - 1 ||
		m_SnakeBody[HEAD].Y <= 0 ||
		m_SnakeBody[HEAD].Y >= MAP_Y - 1)
	{
		m_Blood -= 3;	//撞墙一下就死
		if (m_Blood <= 0)
			m_IsAlive = false;
		return m_IsAlive;
	}
	//是否撞自己（针对头和身
	for (int i = 1; i < m_SnakeBody.size(); i++)
	{
		if (m_SnakeBody[i].X == m_SnakeBody[HEAD].X && m_SnakeBody[i].Y == m_SnakeBody[HEAD].Y)
		{
			m_Blood--;
			if (m_Blood <= 0)
				m_IsAlive = false;
			return m_IsAlive;
		}
	}
	//是否撞障碍物
	for (vector<COORD>::iterator it = barArr.begin(); it != barArr.end(); it++)
	{
		if (it->X == m_SnakeBody[HEAD].X && it->Y == m_SnakeBody[HEAD].Y)
		{
			m_Blood--;
			if (m_Blood <= 0)
				m_IsAlive = false;
			return m_IsAlive;
		}
	}
	return m_IsAlive;
}
bool CSnake::IsEatenFood(CFood& food, vector<COORD>& barArr)
{
	COORD foodPos = food.GetFoodPos();
	if (m_SnakeBody[HEAD].X == foodPos.X && m_SnakeBody[HEAD].Y == foodPos.Y)
	{
		//坐标重合即吃到（吃到后则重新生成，不删除蛇尾
		//一个食物五分，5个食物即25分，为一个速度等级
		g_foodCount++;
		if (g_foodCount == 5)//每吃五个，速度大一级，并且加条命
		{
			g_SleepTime -= 25;
			m_Blood++;
			g_foodCount = 0;
		}
		food.GetRandomPos(m_SnakeBody, barArr);

		return true;
	}
	else
	{
		//没吃到，删除蛇尾
		m_SnakeTail = *(m_SnakeBody.end() - 1);
		m_SnakeBody.erase(m_SnakeBody.end() - 1);
		return false;
	}
}
void CSnake::MoveSnake(CSnake& snake, CBarrier& barrier, CFood& food)
{
	ListenKeyBoard(snake, barrier, food);
	COORD snaHead = m_SnakeBody[0];
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
void CSnake::ListenKeyBoard(CSnake& snake, CBarrier& barrier, CFood& food)
{
	char ch = 0;

	if (_kbhit())				//非阻塞函数 
	{
		ch = _getch();			//无回显接受输入
		switch (ch)
		{
		case 'w':
		{
			if (this->m_Dir == DOWN)
				break;
			this->m_Dir = UP;
			break;
		}
		case 's':
		{
			if (this->m_Dir == UP)
				break;
			this->m_Dir = DOWN;
			break;
		}
		case 'a':
		{
			if (this->m_Dir == RIGHT)
				break;
			this->m_Dir = LEFT;
			break;
		}
		case 'd':
		{
			if (this->m_Dir == LEFT)
				break;
			this->m_Dir = RIGHT;
			break;
		}
		case 'q':
		{
			//暂停及恢复
			mciSendString("pause bgm", NULL, 0, NULL);	//暂停bgm
			setColor(12, 0);
			Gotoxy(MAP_X_WALL + 2, 1);
			cout << "       " << endl;
			Gotoxy(MAP_X_WALL + 2, 1);
			cout << "PAUSE" << endl;					//暂停的状态标识
			Gotoxy(MAP_X_WALL + 2, 2);
			cout << "1. 回到游戏" << endl;
			Gotoxy(MAP_X_WALL + 2, 3);
			cout << "2. 退出游戏" << endl;
			char tmp;
			do
			{
				tmp = _getch();	//利用阻塞函数暂停游戏
			} while (!(tmp == '1' || tmp == '2' || tmp == '3'));//只有输入123才可

			switch (tmp)
			{
			case '1'://恢复游戏
			{
				mciSendString("resume bgm", NULL, 0, NULL);//恢复bgm

				Gotoxy(MAP_X_WALL + 2, 1);
				cout << "RUNNING" << endl;//恢复游戏时，将提示清空
				Gotoxy(MAP_X_WALL + 2, 2);
				cout << "q: 暂停游戏" << endl;
				Gotoxy(MAP_X_WALL + 2, 3);
				cout << "           " << endl;
				Gotoxy(MAP_X_WALL + 2, 4);
				cout << "           " << endl;
				break;
			}

			case '2'://退出并选择是否存档
			{
				//恢复游戏时，将提示清空
				Gotoxy(MAP_X_WALL + 2, 1);
				cout << "想如何退出?" << endl;
				Gotoxy(MAP_X_WALL + 2, 2);
				cout << "1. 保存退出" << endl;
				Gotoxy(MAP_X_WALL + 2, 3);
				cout << "2. 直接退出" << endl;

				char op = _getch();
				if (op == '1')		//保存退出
				{
					SaveGame(snake, barrier, food);
					GameOver(this->m_SnakeBody.size() + 1);//分数-3，蛇跑时会删尾，+3-1应+2，为何+1？
					g_isRunning = false;
					break;
				}
				else if (op == '2')	//直接退出
				{
					GameOver(this->m_SnakeBody.size() + 1);
					g_isRunning = false;
					break;
				}
			}
			default:
				break;
			}
			break;
		}
		//键盘控制速度
		case '+':
		{
			g_SleepTime -= 25;
			break;
		}
		case '-':
		{
			if (g_SleepTime > 400)//最小速度为1，不可再小
			{
				break;
			}
			g_SleepTime += 25;
			break;
		}
		default:
			break;
		}
	}
}