#pragma once
#include <vector>
using std::vector;

class CFood
{
public:
	COORD m_FoodPos;			//食物坐标
	CFood();
	CFood(vector<COORD>& snaBody, vector<COORD>& barrArr);
	void DrawFood();			//打印食物
	COORD GetFoodPos();			//获取食物位置
	void GetRandomPos(vector<COORD>& snaBody, vector<COORD>& barrArr);//获得随机位置

};