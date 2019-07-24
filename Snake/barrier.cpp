#include <iostream>
#include <stdlib.h>
#include <vector>
#include <windows.h>
#include "barrier.h"
#include "func.h"
#include "data.h"
using namespace std;

//�޲ι��죬��ȡ�ļ�ʱ�����������Ϊ��
CBarrier::CBarrier() {}

//�вι���
CBarrier::CBarrier(vector<COORD>& snaBody, int size) :m_size(size)
{
	COORD barr;
	for (int i = 0; i < m_size; i++)
	{
		//��������
		for (int j = 0; j < snaBody.size(); j++)
		{
			barr.X = rand() % (MAP_X_WALL / 2 - 2);
			barr.Y = rand() % (MAP_Y - 2) + 1;

			//�ϰ����ɳ�������������������������
			if (snaBody[j].X == barr.X && snaBody[j].Y == barr.Y)
			{
				barr.X = rand() % (MAP_X_WALL / 2 - 2);
				barr.Y = rand() % (MAP_Y - 2) + 1;
			}

		}

		m_BarrArr.push_back(barr);

	}
}

//��ӡ�ϰ���
void CBarrier::DrawBarr()
{
	for (int i = 0; i < m_size; i++)
	{
		gotoxy4s(m_BarrArr[i].X, m_BarrArr[i].Y);
		cout << "��";
	}
}

//�õ���ͼ���ϰ�������
int CBarrier::GetBarrSize()
{
	return m_size;
}

