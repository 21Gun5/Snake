#pragma once
#include <vector>
using std::vector;

//ʳ����
class CFood
{
public:
	COORD m_FoodPos;		//ʳ������
	CFood(vector<COORD>& snaBody, vector<COORD>& barrArr);//���캯�������ô��Σ��ɸ�ʵ�Σ�������������֤ʳ���Ƿ����������
	void GetRandomPos(vector<COORD>& snaBody, vector<COORD>& barrArr);//������λ��
	void DrawFood();//��ӡʳ��
	COORD GetFoodPos();//��ȡʳ��λ��
};