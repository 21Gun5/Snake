#pragma once
#include <vector>
using std::vector;

class CBarrier
{
public:
	vector<COORD> m_BarrArr;//�ϰ�������
	int m_size;//�ܸ�����Խ���Ѷ�Խ��,���õ�ʱ����m_BarArr.size()��һ�µģ�����ͨ���˸����������Ķ�̬����
	
	CBarrier();
	CBarrier(vector<COORD>& snaBody,int size = 20);
	void DrawBarr();
	//vector<COORD> SetBarr();
	//void SaveBarrFile(vector<COORD> &BarrTmp);
	int GetBarrSize();
};