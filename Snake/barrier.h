#pragma once
#include <vector>
using std::vector;

class CBarrier
{
public:
	vector<COORD> m_BarrArr;//�ϰ�������
	int m_size;//�ܸ�����Խ���Ѷ�Խ��,���õ�ʱ����m_BarArr.size()��һ�µģ�����ͨ���˸����������Ķ�̬����
	CBarrier(int size = 20);
	void DrawBarr();
	int GetBarrSize();
};