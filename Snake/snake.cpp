#include <iostream>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <vector>
#include "data.h"
#include "snake.h"
#include "func.h"
using namespace std;

//�޲ι��죬��ȡ�ļ�ʱ�����������Ϊ��
CSnake::CSnake() {}

//�вι���
CSnake::CSnake(int dir) :m_Dir(dir), m_IsAlive(true),m_Blood(3)//
{
	COORD snakeHead;
	//snakeHead.X = MAP_X / 2 - 15;
	snakeHead.X = MAP_X_WALL / 4;//��Ϊx1B��y2B����x/4����y/2
	snakeHead.Y = MAP_Y / 2;

	m_SnakeBody.push_back(snakeHead);
	snakeHead.Y++;
	m_SnakeBody.push_back(snakeHead);
	snakeHead.Y++;
	m_SnakeBody.push_back(snakeHead); //��ʼ����������
}

//��������
void CSnake::ListenKeyBoard(CSnake& snake, CBarrier& barrier, CFood& food)
{
	char ch = 0;

	if (_kbhit())				//kbhit���������� 
	{
		ch = _getch();			//ʹ�� getch ������ȡ��������
		//PlaySoundA("conf\\click.wav", NULL, SND_ASYNC | SND_NODEFAULT);
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
			//��ͣ���ָ�
		}

		case 'q':
		{	//case�ﶨ�����Ҫ�Ӵ�����
			mciSendString("pause bgm", NULL, 0, NULL);//��ͣbgm
			setColor(12, 0);
			gotoxy(MAP_X_WALL + 2, 1);
			cout << "       " << endl;//��ͣ��״̬��ʶ
			gotoxy(MAP_X_WALL + 2, 1);
			cout << "PAUSE" << endl;//��ͣ��״̬��ʶ
			gotoxy(MAP_X_WALL + 2, 2);
			cout << "1. �ص���Ϸ" << endl;
			gotoxy(MAP_X_WALL + 2, 3);
			cout << "2. �˳���Ϸ" << endl;
			//gotoxy(MAP_X_WALL + 2, 4);
			//cout << "3. �˳���Ϸ" << endl;

			char tmp;
			do
			{
				tmp = _getch();	//��������������ͣ��Ϸ
			} while (!(tmp == '1' || tmp == '2' || tmp == '3'));//ֻ��123�ſɣ�����һֱ������ͣ״̬��ֱ��123

			switch (tmp)
			{
			case '1'://�ָ���Ϸ
			{
				mciSendString("resume bgm", NULL, 0, NULL);//�ָ�bgm

				gotoxy(MAP_X_WALL + 2, 1);
				cout << "RUNNING" << endl;//�ָ���Ϸʱ������ʾ���
				gotoxy(MAP_X_WALL + 2, 2);
				cout << "q: ��ͣ��Ϸ" << endl;
				gotoxy(MAP_X_WALL + 2, 3);
				cout << "           " << endl;
				gotoxy(MAP_X_WALL + 2, 4);
				cout << "           " << endl;
				break;
			}

			case '2'://�˳���ѡ���Ƿ�浵
			{
				//mciSendString("resume bgm", NULL, 0, NULL);//�ָ�bgm
				//�ָ���Ϸʱ������ʾ���
				gotoxy(MAP_X_WALL + 2, 1);
				cout << "������˳�?" << endl;
				gotoxy(MAP_X_WALL + 2, 2);
				cout << "1. �����˳�" << endl;
				gotoxy(MAP_X_WALL + 2, 3);
				cout << "2. ֱ���˳�" << endl;

				int op = _getch();
				if (op == 1)
				{
					SaveGame(snake, barrier, food);
					break;
				}
				else
				{
					GameOver(this->m_SnakeBody.size() + 1);//��������-3�ģ�������ʱ����ɾ��β�ͣ�+3-1Ӧ��Ϊ+2��Ϊ��+1��ȷ��
					g_isRunning = false;
					break;
				}



			}

			//case '3'://�˳���Ϸ
			//{
			//	//�ָ���Ϸʱ������ʾ���
			//	gotoxy(MAP_X_WALL + 2, 1);
			//	cout << "     " << endl;//�ָ���Ϸʱ������ʾ���
			//	gotoxy(MAP_X_WALL + 2, 2);
			//	cout << "           " << endl;
			//	gotoxy(MAP_X_WALL + 2, 3);
			//	cout << "           " << endl;
			//	gotoxy(MAP_X_WALL + 2, 4);
			//	cout << "           " << endl;

			//	GameOver(this->m_SnakeBody.size() + 1);//��������-3�ģ�������ʱ����ɾ��β�ͣ�+3-1Ӧ��Ϊ+2��Ϊ��+1��ȷ��
			//	g_isRunning = false;
			//	break;
			//}
			default:
				break;
			}
			break;


		}

		//���̿����ٶ�
		case '+':
		{
			g_SleepTime -= 25;
			//g_Speed++;//һ���ٶȼ���Ӧ25��ʱ�伶
			break;
		}

		case '-':
		{
			if (g_SleepTime > 400)//��С�ٶ�Ϊ1��������С
			{
				break;
			}
			g_SleepTime += 25;
			//g_Speed--;
			break;
		}

		default:
			break;
		}
	}
}

//�ƶ�̰����
void CSnake::MoveSnake(CSnake& snake, CBarrier& barrier, CFood& food)
{
	ListenKeyBoard(snake, barrier, food);//��������
	COORD snaHead = m_SnakeBody[0];//��ͷ
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

//�Ƿ�Ե�ʳ��
bool CSnake::IsEatenFood(CFood& food, vector<COORD>& barArr)
{
	COORD foodPos = food.GetFoodPos();	//ʳ������

	//�����غϼ��Ե�ʳ��Ե�������������ʳ���ɾ����β
	if (m_SnakeBody[HEAD].X == foodPos.X && m_SnakeBody[HEAD].Y == foodPos.Y)
	{
		//һ��ʳ����֣�5��ʳ�Ｔ25�֣�Ϊһ���ٶȵȼ�
		g_foodCount++;
		if (g_foodCount == 5)//ÿ��������ٶȴ�һ�������Ҽ�����
		{
			g_SleepTime -= 25;
			m_Blood++;
			g_foodCount = 0;
		}
		//��Ĳ�ʵ���ˣ�ֻ�е�һ�λᲥ��
		//mciSendString("open eat.wav alias eat", NULL, 0, NULL);
		//mciSendString("play eat", NULL, 0, NULL);
		//system("pause");
		////char c = _getch();
		//mciSendString("close eat", NULL, 0, NULL);
		

		food.GetRandomPos(m_SnakeBody, barArr);

		return true;
	}
	else
	{
		//û�гԵ�ʳ�ɾ����β
		m_SnakeTail = *(m_SnakeBody.end() - 1);
		m_SnakeBody.erase(m_SnakeBody.end() - 1);
		return false;
	}
}

//�ж�����
bool CSnake::IsAlive(vector<COORD>& barArr)
{
	//�Ƿ�ײ��ͼ�߽�
	if (m_SnakeBody[HEAD].X <= 0 ||
		m_SnakeBody[HEAD].X >= MAP_X_WALL / 2 - 1 ||//��Ϊx��yһ�룬��/2���ö����������⣬x��Ҫ��y��һ��
		m_SnakeBody[HEAD].Y <= 0 ||
		m_SnakeBody[HEAD].Y >= MAP_Y - 1)
	{
		//mciSendString("play duang", NULL, 0, NULL);
		m_Blood-=3;//ײǽһ�¾���
		if(m_Blood == 0) 
			m_IsAlive = false;
		return m_IsAlive;
	}
	//�Ƿ�ײ�Լ���ͷ������ײ�������ص����㣩
	for (int i = 1; i < m_SnakeBody.size(); i++)
	{
		
		if (m_SnakeBody[i].X == m_SnakeBody[HEAD].X && m_SnakeBody[i].Y == m_SnakeBody[HEAD].Y)
		{
			//mciSendString("play duang", NULL, 0, NULL);
			m_Blood--;
			if (m_Blood == 0)
				m_IsAlive = false;
			return m_IsAlive;
		}
	}
	//�Ƿ�ײ��ͼ���ϰ���
	for(vector<COORD>::iterator it = barArr.begin();it!=barArr.end();it++)
	//for (int i = 0; i < barArr.size(); i++)
	{
		
		if (it->X == m_SnakeBody[HEAD].X && it->Y == m_SnakeBody[HEAD].Y)
		{
			//mciSendString("play duang", NULL, 0, NULL);
			m_Blood--;
			//barArr.erase(it);//ײ�ϰ���֮���Ĩ�������ˣ��������ˣ���ϰ��
			if (m_Blood == 0)
				m_IsAlive = false;
			
			return m_IsAlive;
		}
	}
	//m_IsAlive = true;
	return m_IsAlive;
}

//����
void CSnake::DrawSanke()
{
	setColor(10, 0);	//������Ϊ��ɫ

	for (int i = 0; i < m_SnakeBody.size(); i++)
	{
		//����
		//gotoxy(m_SnakeBody[i].X, m_SnakeBody[i].Y);//here
		gotoxy4s(m_SnakeBody[i].X, m_SnakeBody[i].Y);

		//��ͷ���������ò�ͬͼ��
		if (i == 0)
		{
			cout << "��";
		}
		else
		{
			cout << "��";
		}

		//cout << "*";//here
	}

	setColor(7, 0);		//�ָ�ԭ����ɫ
}

//�����β
void CSnake::ClearSnake()
{
	//����ǰ���������һ�������ÿո��ʾ
	//gotoxy(m_SnakeBody[m_SnakeBody.size() - 1].X, m_SnakeBody[m_SnakeBody.size() - 1].Y);
	gotoxy4s(m_SnakeBody[m_SnakeBody.size() - 1].X, m_SnakeBody[m_SnakeBody.size() - 1].Y);//here


	cout << "  ";//here
	//cout << " ";
}

//��ȡ�߳�
int CSnake::GetSnakeSize()
{
	//�߳���Ϊ�����ο���Ҫʵʱ��ʾ���ʷ���ѭ����
	return m_SnakeBody.size();
}