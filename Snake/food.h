#pragma once
#include <vector>
using std::vector;

//食物类
class CFood
{
public:
	COORD m_FoodPos;		//食物坐标
	CFood(vector<COORD>& snaBody, vector<COORD>& barrArr);//构造函数（引用传参，可改实参；传入蛇身以验证食物是否出现在蛇身
	void GetRandomPos(vector<COORD>& snaBody, vector<COORD>& barrArr);//获得随机位置
	void DrawFood();//打印食物
	COORD GetFoodPos();//获取食物位置
};