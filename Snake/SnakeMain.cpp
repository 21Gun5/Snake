#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <ctime>
#include <conio.h>
#include <Windows.h>
#include "data.h"
#include "func.h"
using namespace std;

//食物类
class CFood
{	
public:
	POS m_FoodPos;		//食物坐标

	//构造函数，传入参数为蛇身坐标
	CFood(vector<POS>& coord)
	{
		RandomXY(coord);
	}

	//获得随机位置
	void RandomXY(vector<POS>& coord)
	{
		m_FoodPos.x = rand() % (g_window_width - 30) + 1;
		m_FoodPos.y = rand() % (g_window_height - 2) + 1;
		unsigned int i;

		//食物不可在蛇身上，若有要重新生成
		for (i = 0; i < coord.size(); i++)
		{
			//重新生成
			if (coord[i].x == m_FoodPos.x && coord[i].y == m_FoodPos.y)
			{
				m_FoodPos.x = rand() % (g_window_width - 30) + 1;
				m_FoodPos.y = rand() % (g_window_height - 2) + 1;
				i = 0;
			}
		}
	}

	//打印食物
	void DrawFood()
	{
		setColor(12, 0);
		gotoxy(m_FoodPos.x, m_FoodPos.y);
		cout << "@";
		setColor(7, 0);
	}

	//获取食物位置
	POS GetFoodPos()
	{
		return m_FoodPos;
	}
};

//贪吃蛇类
class Snake
{
public:
	vector<POS> m_SnakeBody;	//存储蛇身体的向量
	int m_Dir;					//运动方向
	bool m_IsAlive;				//是否存活

	//构造函数
	Snake() :m_Dir(1), m_IsAlive(true)
	{
		POS snakeHead;
		snakeHead.x = g_window_width / 2 - 15;
		snakeHead.y = g_window_height / 2;

		m_SnakeBody.push_back(snakeHead);
		snakeHead.y++;
		m_SnakeBody.push_back(snakeHead);
		snakeHead.y++;
		m_SnakeBody.push_back(snakeHead); //初始蛇身长度三节
	}

	//监听键盘
	void ListenKeyBoard()
	{
		char ch;

		if (_kbhit())					//kbhit 非阻塞函数 
		{
			ch = _getch();	//使用 getch 函数获取键盘输入 
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
			case '+':
				if (g_speed >= 25)
				{
					g_speed -= 25;
				}
				break;
			case '-':
				if (g_speed < 250)
				{
					g_speed += 25;
				}
				break;
			}
		}
	}

	//是否撞到自己
	bool IsMeetSelf(POS head)
	{
		for (unsigned int i = 1; i < m_SnakeBody.size(); i++)
		{
			if (head.x == m_SnakeBody[i].x && head.y == m_SnakeBody[i].y)
			{
				return true;
			}
		}
		return false;
	}

	//移动贪吃蛇
	void MoveSnake()
	{
		ListenKeyBoard();//监听键盘
		POS head = m_SnakeBody[0];//蛇头
		switch (this->m_Dir)
		{
		case UP:
			head.y--;
			break;
		case DOWN:
			head.y++;
			break;
		case LEFT:
			head.x--;
			break;
		case RIGHT:
			head.x++;
			break;
		}
		//插入移动后新的蛇头
		m_SnakeBody.insert(m_SnakeBody.begin(), head);
	}

	//是否吃到食物
	bool IsEatenFood(CFood& f)
	{
		//获取食物坐标
		POS food_coordinate = f.GetFoodPos();
		//吃到食物，食物重新生成，不删除蛇尾
		if (m_SnakeBody[HEAD].x == food_coordinate.x && m_SnakeBody[HEAD].y == food_coordinate.y)
		{
			f.RandomXY(m_SnakeBody);
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
	bool IsAlive()
	{
		if (m_SnakeBody[HEAD].x <= 0 ||
			m_SnakeBody[HEAD].x >= g_window_width - 29 ||
			m_SnakeBody[HEAD].y <= 0 ||
			m_SnakeBody[HEAD].y >= g_window_height - 1)
		{
			//超出边界
			m_IsAlive = false;
			return m_IsAlive;
		}
		//和自己碰到一起
		for (unsigned int i = 1; i < m_SnakeBody.size(); i++)
		{
			if (m_SnakeBody[i].x == m_SnakeBody[HEAD].x && m_SnakeBody[i].y == m_SnakeBody[HEAD].y)
			{
				m_IsAlive = false;
				return m_IsAlive;
			}
		}
		m_IsAlive = true;

		return m_IsAlive;
	}

	//画蛇
	void DrawSanke()
	{
		//设置颜色为浅绿色
		setColor(10, 0);
		for (unsigned int i = 0; i < this->m_SnakeBody.size(); i++)
		{
			gotoxy(m_SnakeBody[i].x, m_SnakeBody[i].y);
			cout << "*";
		}
		//恢复原来的颜色
		setColor(7, 0);
	}

	//清除蛇尾，画蛇前必做
	void ClearSnake()
	{
		gotoxy(m_SnakeBody[this->m_SnakeBody.size() - 1].x, m_SnakeBody[this->m_SnakeBody.size() - 1].y);
		cout << " ";
	}

	//获取蛇长
	int GetSnakeSize()
	{
		return m_SnakeBody.size();
	}
};

int main()
{
	//各对象实例化
	Snake  snake;
	CFood food(snake.m_SnakeBody);
	
	GameInit();				//初始化
	DrawWelcome();			//欢迎界面
	system("pause");		//过渡到游戏界面
	DrawMap();				//打印地图边框
	DrawGameInfo();			//打印相关信息
	
	while (true)
	{
		DrawScore(snake.GetSnakeSize());	//打印分数
		food.DrawFood();					//打印食物
		snake.ClearSnake();					//清理蛇尾
		snake.IsEatenFood(food);			//是否吃到食物
		snake.MoveSnake();					//让蛇跑起来
		snake.DrawSanke();					//画蛇

		if (!snake.IsAlive())				//是否活着
		{
			GameOver(snake.GetSnakeSize());
			break;
		}
		Sleep(g_speed);						//控制游戏速度
	}

	//消耗多余字符，避免打印系统提示
	cin.get();
	cin.get();

	return 0;
}