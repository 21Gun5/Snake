#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <ctime>
#include <conio.h>
#include <Windows.h>
#include "setting.h"
#include "drawSth.h"
using namespace std;

//食物类
class Food
{
private:
	//食物坐标
	POS m_coordinate;
public:
	//坐标范围：
	//x: 1 to CSetting::window_width - 30 闭区间
	//y: 1 to CSetting::window_height - 2 闭区间
	void RandomXY(vector<POS>& coord)
	{
		m_coordinate.x = rand() % (CSetting::window_width - 30) + 1;
		m_coordinate.y = rand() % (CSetting::window_height - 2) + 1;
		unsigned int i;
		//原则上不允许食物出现在蛇的位置上，如果有，重新生成
		for (i = 0; i < coord.size(); i++)
		{
			//食物出现在蛇身的位置上。重新生成
			if (coord[i].x == m_coordinate.x && coord[i].y == m_coordinate.y)
			{
				m_coordinate.x = rand() % (CSetting::window_width - 30) + 1;
				m_coordinate.y = rand() % (CSetting::window_height - 2) + 1;
				i = 0;
			}
		}
	}
	//默认构造函数
	Food() {}
	//构造函数，传入参数为蛇身坐标
	Food(vector<POS>& coord)
	{
		RandomXY(coord);
	}
	//画出食物的位置
	void DrawFood()
	{
		setColor(12, 0);
		gotoxy(m_coordinate.x, m_coordinate.y);
		cout << "@";
		setColor(7, 0);
	}
	//接口，获取食物位置
	POS GetFoodCoordinate()
	{
		return m_coordinate;
	}

};
//贪吃蛇类，定义贪吃蛇的移动，打印，吃食物等等
//地图范围width:2 to width-2  height: 2 to height-2
class Snake
{
private:
	bool m_model; //true人机  false AI
	int m_direction;
	bool m_is_alive;
private: //AI功能相关
	bool m_chess[CSetting::window_width - 29 + 1][CSetting::window_height]; //AI功能用
	//FindPathBFS m_AISnake;
	POS map_size;
public://蛇身坐标
	vector<POS> m_coordinate;

public://默认构造函数
	Snake(bool model = false) : m_model(model) //默认人机模式
	{
		map_size.x = CSetting::window_width - 29 + 1;
		map_size.y = CSetting::window_height;
		//移动方向向上
		m_direction = 1;
		m_is_alive = true;
		POS snake_head;
		snake_head.x = CSetting::window_width / 2 - 15;
		snake_head.y = CSetting::window_height / 2;

		this->m_coordinate.push_back(snake_head);
		snake_head.y++;
		this->m_coordinate.push_back(snake_head);
		snake_head.y++;
		this->m_coordinate.push_back(snake_head); //初始蛇身长度三节

		//围墙是障碍
		for (int i = 0; i < CSetting::window_width - 29 + 1; i++)
		{
			m_chess[i][0] = true;
			m_chess[i][CSetting::window_height - 1] = true;
		}

		for (int j = 0; j < CSetting::window_height - 1; j++)
		{
			m_chess[0][j] = true;
			m_chess[CSetting::window_width - 29][j] = true;
		}

	}
	//设置游戏模式
	void set_model(bool m) { m_model = m; }
	//监听键盘
	void listen_key_borad()
	{
		char ch;

		if (_kbhit())					//kbhit 非阻塞函数 
		{
			ch = _getch();	//使用 getch 函数获取键盘输入 
			switch (ch)
			{
			case 'w':
			case 'W':
				if (this->m_direction == DOWN)
					break;
				this->m_direction = UP;
				break;
			case 's':
			case 'S':
				if (this->m_direction == UP)
					break;
				this->m_direction = DOWN;
				break;
			case 'a':
			case 'A':
				if (this->m_direction == RIGHT)
					break;
				this->m_direction = LEFT;
				break;
			case 'd':
			case 'D':
				if (this->m_direction == LEFT)
					break;
				this->m_direction = RIGHT;
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

	//检测是否碰到自己
	bool self_collision(POS head)
	{
		for (unsigned int i = 1; i < m_coordinate.size(); i++)
		{
			if (head.x == m_coordinate[i].x && head.y == m_coordinate[i].y)
			{
				return true;
			}
		}
		return false;
	}

	//移动贪吃蛇
	void move_snake()
	{
		//监听键盘
		listen_key_borad();
		//蛇头
		POS head = m_coordinate[0];
		//direction方向:1 上  2 下  3 左  4 右
		switch (this->m_direction)
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
		m_coordinate.insert(m_coordinate.begin(), head);
	}
	//判断是否吃到食物
	bool is_eat_food(Food& f)
	{
		//获取食物坐标
		POS food_coordinate = f.GetFoodCoordinate();
		//吃到食物，食物重新生成，不删除蛇尾
		if (m_coordinate[HEAD].x == food_coordinate.x && m_coordinate[HEAD].y == food_coordinate.y)
		{
			f.RandomXY(m_coordinate);
			return true;
		}
		else
		{
			//没有吃到食物，删除蛇尾
			m_coordinate.erase(m_coordinate.end() - 1);
			return false;
		}
	}
	//判断贪吃蛇死了没
	bool snake_is_alive()
	{
		if (m_coordinate[HEAD].x <= 0 ||
			m_coordinate[HEAD].x >= CSetting::window_width - 29 ||
			m_coordinate[HEAD].y <= 0 ||
			m_coordinate[HEAD].y >= CSetting::window_height - 1)
		{
			//超出边界
			m_is_alive = false;
			return m_is_alive;
		}
		//和自己碰到一起
		for (unsigned int i = 1; i < m_coordinate.size(); i++)
		{
			if (m_coordinate[i].x == m_coordinate[HEAD].x && m_coordinate[i].y == m_coordinate[HEAD].y)
			{
				m_is_alive = false;
				return m_is_alive;
			}
		}
		m_is_alive = true;

		return m_is_alive;
	}
	//画出贪吃蛇
	void draw_snake()
	{
		//设置颜色为浅绿色
		setColor(10, 0);
		for (unsigned int i = 0; i < this->m_coordinate.size(); i++)
		{
			gotoxy(m_coordinate[i].x, m_coordinate[i].y);
			cout << "*";
		}
		//恢复原来的颜色
		setColor(7, 0);
	}
	//清除屏幕上的贪吃蛇
	void ClearSnake()
	{
		for (unsigned int i = 0; i < m_coordinate.size(); i++)
		{
			m_chess[m_coordinate[i].x][m_coordinate[i].y] = false;
		}
		gotoxy(m_coordinate[this->m_coordinate.size() - 1].x, m_coordinate[this->m_coordinate.size() - 1].y);
		cout << " ";

	}
	//获取贪吃蛇的长度
	int GetSnakeSize()
	{
		return m_coordinate.size();
	}
	//获取当前游戏模式
	bool GetModel()
	{
		return m_model;
	}
};

//主函数，组合各种类和资源，进行游戏。
int main()
{
	CSetting setting;
	//PrintInfo print_info;
	Snake  snake;
	//初始化游戏
	setting.GameInit();
	//游戏模式选择
	DrawWelcome();


	gotoxy(CSetting::window_width / 2 - 10, CSetting::window_height / 2 + 3);
	system("pause");
	//画地图
	DrawMap();
	DrawGameInfo();
	//生成食物
	Food food(snake.m_coordinate);
	//游戏死循环
	while (true)
	{
		//打印成绩
		DrawScore(snake.GetSnakeSize());
		//画出食物
		food.DrawFood();
		//清理蛇尾，每次画蛇前必做
		snake.ClearSnake();
		//判断是否吃到食物
		snake.is_eat_food(food);
		//根据用户模式选择不同的调度方式
		snake.move_snake();
		
		//画蛇
		snake.draw_snake();
		//判断蛇是否还活着
		if (!snake.snake_is_alive())
		{
			GameOver(snake.GetSnakeSize());
			break;
		}
		//控制游戏速度
		Sleep(g_speed);
	}

	cin.get();
	cin.get();

	return 0;
}