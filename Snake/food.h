#pragma once
#include <vector>
using std::vector;

class CFood
{
public:
	COORD m_FoodPos;			//ʳ������
	CFood();
	CFood(vector<COORD>& snaBody, vector<COORD>& barrArr);
	void DrawFood();			//��ӡʳ��
	COORD GetFoodPos();			//��ȡʳ��λ��
	void GetRandomPos(vector<COORD>& snaBody, vector<COORD>& barrArr);//������λ��

};