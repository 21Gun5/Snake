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

//ʳ����
class CFood
{	
public:
	POS m_FoodPos;		//ʳ������

	//���캯�����������Ϊ��������
	CFood(vector<POS>& coord)
	{
		RandomXY(coord);
	}

	//������λ��
	void RandomXY(vector<POS>& coord)
	{
		m_FoodPos.x = rand() % (g_window_width - 30) + 1;
		m_FoodPos.y = rand() % (g_window_height - 2) + 1;
		unsigned int i;

		//ʳ�ﲻ���������ϣ�����Ҫ��������
		for (i = 0; i < coord.size(); i++)
		{
			//��������
			if (coord[i].x == m_FoodPos.x && coord[i].y == m_FoodPos.y)
			{
				m_FoodPos.x = rand() % (g_window_width - 30) + 1;
				m_FoodPos.y = rand() % (g_window_height - 2) + 1;
				i = 0;
			}
		}
	}

	//��ӡʳ��
	void DrawFood()
	{
		setColor(12, 0);
		gotoxy(m_FoodPos.x, m_FoodPos.y);
		cout << "@";
		setColor(7, 0);
	}

	//��ȡʳ��λ��
	POS GetFoodPos()
	{
		return m_FoodPos;
	}
};

//̰������
class Snake
{
public:
	vector<POS> m_SnakeBody;	//�洢�����������
	int m_Dir;					//�˶�����
	bool m_IsAlive;				//�Ƿ���

	//���캯��
	Snake() :m_Dir(1), m_IsAlive(true)
	{
		POS snakeHead;
		snakeHead.x = g_window_width / 2 - 15;
		snakeHead.y = g_window_height / 2;

		m_SnakeBody.push_back(snakeHead);
		snakeHead.y++;
		m_SnakeBody.push_back(snakeHead);
		snakeHead.y++;
		m_SnakeBody.push_back(snakeHead); //��ʼ����������
	}

	//��������
	void ListenKeyBoard()
	{
		char ch;

		if (_kbhit())					//kbhit ���������� 
		{
			ch = _getch();	//ʹ�� getch ������ȡ�������� 
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

	//�Ƿ�ײ���Լ�
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

	//�ƶ�̰����
	void MoveSnake()
	{
		ListenKeyBoard();//��������
		POS head = m_SnakeBody[0];//��ͷ
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
		//�����ƶ����µ���ͷ
		m_SnakeBody.insert(m_SnakeBody.begin(), head);
	}

	//�Ƿ�Ե�ʳ��
	bool IsEatenFood(CFood& f)
	{
		//��ȡʳ������
		POS food_coordinate = f.GetFoodPos();
		//�Ե�ʳ�ʳ���������ɣ���ɾ����β
		if (m_SnakeBody[HEAD].x == food_coordinate.x && m_SnakeBody[HEAD].y == food_coordinate.y)
		{
			f.RandomXY(m_SnakeBody);
			return true;
		}
		else
		{
			//û�гԵ�ʳ�ɾ����β
			m_SnakeBody.erase(m_SnakeBody.end() - 1);
			return false;
		}
	}

	//�ж�����
	bool IsAlive()
	{
		if (m_SnakeBody[HEAD].x <= 0 ||
			m_SnakeBody[HEAD].x >= g_window_width - 29 ||
			m_SnakeBody[HEAD].y <= 0 ||
			m_SnakeBody[HEAD].y >= g_window_height - 1)
		{
			//�����߽�
			m_IsAlive = false;
			return m_IsAlive;
		}
		//���Լ�����һ��
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

	//����
	void DrawSanke()
	{
		//������ɫΪǳ��ɫ
		setColor(10, 0);
		for (unsigned int i = 0; i < this->m_SnakeBody.size(); i++)
		{
			gotoxy(m_SnakeBody[i].x, m_SnakeBody[i].y);
			cout << "*";
		}
		//�ָ�ԭ������ɫ
		setColor(7, 0);
	}

	//�����β������ǰ����
	void ClearSnake()
	{
		gotoxy(m_SnakeBody[this->m_SnakeBody.size() - 1].x, m_SnakeBody[this->m_SnakeBody.size() - 1].y);
		cout << " ";
	}

	//��ȡ�߳�
	int GetSnakeSize()
	{
		return m_SnakeBody.size();
	}
};

int main()
{
	//������ʵ����
	Snake  snake;
	CFood food(snake.m_SnakeBody);
	
	GameInit();				//��ʼ��
	DrawWelcome();			//��ӭ����
	system("pause");		//���ɵ���Ϸ����
	DrawMap();				//��ӡ��ͼ�߿�
	DrawGameInfo();			//��ӡ�����Ϣ
	
	while (true)
	{
		DrawScore(snake.GetSnakeSize());	//��ӡ����
		food.DrawFood();					//��ӡʳ��
		snake.ClearSnake();					//������β
		snake.IsEatenFood(food);			//�Ƿ�Ե�ʳ��
		snake.MoveSnake();					//����������
		snake.DrawSanke();					//����

		if (!snake.IsAlive())				//�Ƿ����
		{
			GameOver(snake.GetSnakeSize());
			break;
		}
		Sleep(g_speed);						//������Ϸ�ٶ�
	}

	//���Ķ����ַ��������ӡϵͳ��ʾ
	cin.get();
	cin.get();

	return 0;
}