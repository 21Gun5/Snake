#pragma once
#include <vector>
using std::vector;

class CBarrier
{
public:
	vector<COORD> m_BarrArr;//障碍物数组
	int m_size;//总个数，越多难度越大,在用的时候，与m_BarArr.size()是一致的，就是通过此个数来创建的动态数组
	
	CBarrier();
	CBarrier(vector<COORD>& snaBody,int size = 20);
	void DrawBarr();
	//vector<COORD> SetBarr();
	//void SaveBarrFile(vector<COORD> &BarrTmp);
	int GetBarrSize();
};