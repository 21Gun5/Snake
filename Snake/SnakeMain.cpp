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
using namespace std;

//食物类
class CFood
{
public:
	POS m_FoodPos;		//食物坐标

	//构造函数（引用传参，可改实参
	CFood(vector<POS> & snaBody)//传入蛇身以验证食物是否出现在蛇身
	{
		GetRandomPos(snaBody);
	}

	//获得随机位置
	void GetRandomPos(vector<POS> & snaBody)
	{
		m_FoodPos.x = rand() % (g_window_width - 30) + 1;//here
		//m_FoodPos.x = rand() % (g_window_width - 50) + 1;
		m_FoodPos.y = rand() % (g_window_height - 2) + 1;
		
		for (int i = 0; i < snaBody.size(); i++)		//遍历蛇身
		{
			//食物不可出现在蛇身，若出现则重新生成
			if (snaBody[i].x == m_FoodPos.x && snaBody[i].y == m_FoodPos.y)
			{
				m_FoodPos.x = rand() % (g_window_width - 30) + 1;//here
				//m_FoodPos.x = rand() % (g_window_width - 50) + 1;
				m_FoodPos.y = rand() % (g_window_height - 2) + 1;
			}
		}
	}

	//打印食物
	void DrawFood()
	{
		setColor(12, 0);	//食物红色
		gotoxy(m_FoodPos.x, m_FoodPos.y);
		//gotoxy4s(m_FoodPos.x, m_FoodPos.y);//here
		cout << "$";
		setColor(7, 0);		//再换回来
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
		//snakeHead.x = g_window_width / 2 - 15;
		snakeHead.x = g_window_width / 2 - 15 - 10;
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
		char ch = 0;

		if (_kbhit())				//kbhit非阻塞函数 
		{
			ch = _getch();			//使用 getch 函数获取键盘输入 
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
			//case ' ':

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
	void MoveSnake()
	{
		ListenKeyBoard();//监听键盘
		POS snaHead = m_SnakeBody[0];//蛇头
		switch (m_Dir)
		{
		case UP:
			snaHead.y--;
			break;
		case DOWN:
			snaHead.y++;
			break;
		case LEFT:
			snaHead.x--;
			break;
		case RIGHT:
			snaHead.x++;
			break;
		}
		//插入移动后新的蛇头（先去蛇尾，再加蛇头）
		m_SnakeBody.insert(m_SnakeBody.begin(), snaHead);
	}

	//是否吃到食物
	bool IsEatenFood(CFood& food)
	{
		POS foodPos = food.GetFoodPos();	//食物坐标
		//坐标重合即吃到食物（吃到后则重新生成食物，不删除蛇尾
		if (m_SnakeBody[HEAD].x == foodPos.x && m_SnakeBody[HEAD].y == foodPos.y)
		{
			food.GetRandomPos(m_SnakeBody);
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
		//是否撞墙
		if (m_SnakeBody[HEAD].x <= 0 ||
			m_SnakeBody[HEAD].x >= g_window_width - 29 ||
			m_SnakeBody[HEAD].y <= 0 ||
			m_SnakeBody[HEAD].y >= g_window_height - 1)
		{
			m_IsAlive = false;
			return m_IsAlive;
		}
		//是否撞自己（只管头和身
		for (int i = 1; i < m_SnakeBody.size(); i++)
		{
			if (m_SnakeBody[i].x == m_SnakeBody[HEAD].x && m_SnakeBody[i].y == m_SnakeBody[HEAD].y)
			{
				m_IsAlive = false;
				return m_IsAlive;
			}
		}
		//m_IsAlive = true;
		return m_IsAlive;
	}

	//画蛇
	void DrawSanke()
	{
		setColor(10, 0);	//设置蛇为绿色

		for (int i = 0; i < m_SnakeBody.size(); i++)
		{
			//□■
			gotoxy(m_SnakeBody[i].x, m_SnakeBody[i].y);//here
			//gotoxy4s(m_SnakeBody[i].x, m_SnakeBody[i].y);
			//cout << "■";
			cout << "*";
		}

		setColor(7, 0);		//恢复原来颜色
	}

	//清除蛇尾
	void ClearSnake()
	{
		//画蛇前必做，最后一节蛇身用空格表示
		gotoxy(m_SnakeBody[m_SnakeBody.size() - 1].x, m_SnakeBody[m_SnakeBody.size() - 1].y);
		//gotoxy4s(m_SnakeBody[m_SnakeBody.size() - 1].x, m_SnakeBody[m_SnakeBody.size() - 1].y);here


		//cout << "  ";here
		cout << " ";
	}

	//获取蛇长
	int GetSnakeSize()
	{
		//蛇长作为分数参考，要实时显示，故放至循环内
		return m_SnakeBody.size();
	}
};

int main()
{
	//各对象实例化
	Snake snake;
	CFood food(snake.m_SnakeBody);

	GameInit();				//初始化
	DrawWelcome();			//欢迎界面
	system("pause");		//提示按键到下一界面
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