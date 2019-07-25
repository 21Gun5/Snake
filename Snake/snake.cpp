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
	snakeHead.X = MAP_X_WALL / 4;//��Ϊx1B��y2B����x/4����y/2
	snakeHead.Y = MAP_Y / 2;

	m_SnakeBody.push_back(snakeHead);
	snakeHead.Y++;
	m_SnakeBody.push_back(snakeHead);
	snakeHead.Y++;
	m_SnakeBody.push_back(snakeHead); //��ʼ����������
}
void CSnake::DrawSanke()
{
	setColor(10, 0);	//��Ϊ��ɫ
	for (int i = 0; i < m_SnakeBody.size(); i++)
	{
		GotoxyFor2(m_SnakeBody[i].X, m_SnakeBody[i].Y);
		if (i == 0)
		{
			cout << "��";
		}
		else
		{
			cout << "��";
		}
	}
	setColor(7, 0);
}
void CSnake::ClearSnakeTail()
{
	//����ǰ��������β���
	GotoxyFor2(m_SnakeBody[m_SnakeBody.size() - 1].X, m_SnakeBody[m_SnakeBody.size() - 1].Y);
	cout << "  ";
}
int CSnake::GetSnakeSize()
{
	//�߳�������
	return m_SnakeBody.size();
}
bool CSnake::IsAlive(vector<COORD>& barArr)
{
	//�Ƿ�ײ�߽�
	if (m_SnakeBody[HEAD].X <= 0 ||
		m_SnakeBody[HEAD].X >= MAP_X_WALL / 2 - 1 ||
		m_SnakeBody[HEAD].Y <= 0 ||
		m_SnakeBody[HEAD].Y >= MAP_Y - 1)
	{
		m_Blood -= 3;	//ײǽһ�¾���
		if (m_Blood <= 0)
			m_IsAlive = false;
		return m_IsAlive;
	}
	//�Ƿ�ײ�Լ������ͷ����
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
	//�Ƿ�ײ�ϰ���
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
		//�����غϼ��Ե����Ե������������ɣ���ɾ����β
		//һ��ʳ����֣�5��ʳ�Ｔ25�֣�Ϊһ���ٶȵȼ�
		g_foodCount++;
		if (g_foodCount == 5)//ÿ��������ٶȴ�һ�������Ҽ�����
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
		//û�Ե���ɾ����β
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
	//�����ƶ����µ���ͷ����ȥ��β���ټ���ͷ��
	m_SnakeBody.insert(m_SnakeBody.begin(), snaHead);
}
void CSnake::ListenKeyBoard(CSnake& snake, CBarrier& barrier, CFood& food)
{
	char ch = 0;

	if (_kbhit())				//���������� 
	{
		ch = _getch();			//�޻��Խ�������
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
			//��ͣ���ָ�
			mciSendString("pause bgm", NULL, 0, NULL);	//��ͣbgm
			setColor(12, 0);
			Gotoxy(MAP_X_WALL + 2, 1);
			cout << "       " << endl;
			Gotoxy(MAP_X_WALL + 2, 1);
			cout << "PAUSE" << endl;					//��ͣ��״̬��ʶ
			Gotoxy(MAP_X_WALL + 2, 2);
			cout << "1. �ص���Ϸ" << endl;
			Gotoxy(MAP_X_WALL + 2, 3);
			cout << "2. �˳���Ϸ" << endl;
			char tmp;
			do
			{
				tmp = _getch();	//��������������ͣ��Ϸ
			} while (!(tmp == '1' || tmp == '2' || tmp == '3'));//ֻ������123�ſ�

			switch (tmp)
			{
			case '1'://�ָ���Ϸ
			{
				mciSendString("resume bgm", NULL, 0, NULL);//�ָ�bgm

				Gotoxy(MAP_X_WALL + 2, 1);
				cout << "RUNNING" << endl;//�ָ���Ϸʱ������ʾ���
				Gotoxy(MAP_X_WALL + 2, 2);
				cout << "q: ��ͣ��Ϸ" << endl;
				Gotoxy(MAP_X_WALL + 2, 3);
				cout << "           " << endl;
				Gotoxy(MAP_X_WALL + 2, 4);
				cout << "           " << endl;
				break;
			}

			case '2'://�˳���ѡ���Ƿ�浵
			{
				//�ָ���Ϸʱ������ʾ���
				Gotoxy(MAP_X_WALL + 2, 1);
				cout << "������˳�?" << endl;
				Gotoxy(MAP_X_WALL + 2, 2);
				cout << "1. �����˳�" << endl;
				Gotoxy(MAP_X_WALL + 2, 3);
				cout << "2. ֱ���˳�" << endl;

				char op = _getch();
				if (op == '1')		//�����˳�
				{
					SaveGame(snake, barrier, food);
					GameOver(this->m_SnakeBody.size() + 1);//����-3������ʱ��ɾβ��+3-1Ӧ+2��Ϊ��+1��
					g_isRunning = false;
					break;
				}
				else if (op == '2')	//ֱ���˳�
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
		//���̿����ٶ�
		case '+':
		{
			g_SleepTime -= 25;
			break;
		}
		case '-':
		{
			if (g_SleepTime > 400)//��С�ٶ�Ϊ1��������С
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