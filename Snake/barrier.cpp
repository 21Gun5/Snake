#include <iostream>
#include <stdlib.h>
#include <vector>
#include <windows.h>
#include "barrier.h"
#include "func.h"
#include "data.h"
using namespace std;

CBarrier::CBarrier(int size):m_size(size)
{
	COORD barr;
	for (int i = 0; i < m_size; i++)
	{
		barr.X = rand() % (MAP_X_WALL / 2 - 2);
		barr.Y = rand() % (MAP_Y - 2) + 1;
		m_BarrArr.push_back(barr);
	}
}
void CBarrier::DrawBarr()
{
	for (int i = 0; i < m_size; i++)
	{
		gotoxy4s(m_BarrArr[i].X, m_BarrArr[i].Y);
		cout << "¡ù";
	}
}
int CBarrier::GetBarrSize()
{
	return m_size;
}

