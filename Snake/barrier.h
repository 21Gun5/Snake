#pragma once
#include <vector>
using std::vector;

class CBarrier
{
public:
	vector<COORD> m_BarrArr;//障碍物数组
	int m_size;				//总个数，越多难度越大
	CBarrier();
	CBarrier(vector<COORD>& snaBody, int size = 20);
	void DrawBarr();
	int GetBarrSize();
};