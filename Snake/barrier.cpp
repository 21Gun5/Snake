#include <iostream>
#include <stdlib.h>
#include <vector>
#include <windows.h>
#include "barrier.h"
#include "func.h"
#include "data.h"
using namespace std;

CBarrier::CBarrier() {}
CBarrier::CBarrier(vector<COORD>& snaBody, int size) :m_size(size)
{
	COORD barr;
	for (int i = 0; i < m_size; i++)
	{
		//遍历蛇身
		for (int j = 0; j < snaBody.size(); j++)
		{
			barr.X = rand() % (MAP_X_WALL / 2 - 2);
			barr.Y = rand() % (MAP_Y - 2) + 1;
			//障碍不可出现在蛇身，若出现则重新生成
			if (snaBody[j].X == barr.X && snaBody[j].Y == barr.Y)
			{
				barr.X = rand() % (MAP_X_WALL / 2 - 2);
				barr.Y = rand() % (MAP_Y - 2) + 1;
			}

		}
		m_BarrArr.push_back(barr);
	}
}
void CBarrier::DrawBarr()
{
	for (int i = 0; i < m_size; i++)
	{
		GotoxyFor2(m_BarrArr[i].X, m_BarrArr[i].Y);
		cout << "※";
	}
}
int CBarrier::GetBarrSize()
{
	return m_size;
}
