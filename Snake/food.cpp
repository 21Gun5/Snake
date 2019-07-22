#include <iostream>
#include <time.h>
#include <windows.h>
#include <vector>
#include "data.h"
#include "food.h"
#include "snake.h"
#include "func.h"
using namespace std;

//���캯�������ô��Σ��ɸ�ʵ��
CFood::CFood(vector<COORD>& snaBody, vector<COORD>& barrArr)//������������֤ʳ���Ƿ����������
{
	GetRandomPos(snaBody, barrArr);
}

//������λ��
void CFood::GetRandomPos(vector<COORD>& snaBody, vector<COORD>& barrArr)
{
	m_FoodPos.X = rand() % (MAP_X_WALL / 2 - 2) + 1;//��Ϊx��yһ�룬��/2
	//m_FoodPos.X = rand() % (MAP_X - 50) + 1;here
	m_FoodPos.Y = rand() % (MAP_Y - 2) + 1;

	for (int i = 0; i < snaBody.size(); i++)		//��������
	{
		//ʳ�ﲻ�ɳ�������������������������
		if (snaBody[i].X == m_FoodPos.X && snaBody[i].Y == m_FoodPos.Y)
		{
			m_FoodPos.X = rand() % (MAP_X_WALL / 2 - 2) + 1;//��Ϊx��yһ�룬��/2
			//m_FoodPos.X = rand() % (MAP_X - 50) + 1;here
			m_FoodPos.Y = rand() % (MAP_Y - 2) + 1;
		}
	}

	for (int i = 0; i < barrArr.size(); i++)		//������ͼ�������ϰ���
	{
		//ʳ�ﲻ�ɳ������ϰ������������������
		if (barrArr[i].X == m_FoodPos.X && barrArr[i].Y == m_FoodPos.Y)
		{
			m_FoodPos.X = rand() % (MAP_X_WALL / 2 - 2) + 1;//��Ϊx��yһ�룬��/2
			//m_FoodPos.X = rand() % (MAP_X - 50) + 1;here
			m_FoodPos.Y = rand() % (MAP_Y - 2) + 1;
		}
	}

}

//��ӡʳ��
void CFood::DrawFood()
{
	setColor(12, 0);	//ʳ���ɫ
	//gotoxy(m_FoodPos.X, m_FoodPos.Y);
	gotoxy4s(m_FoodPos.X, m_FoodPos.Y);//here
	cout << "��";
	setColor(7, 0);		//�ٻ�����
}

//��ȡʳ��λ��
COORD CFood::GetFoodPos()
{
	return m_FoodPos;
}

