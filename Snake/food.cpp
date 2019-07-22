#include <iostream>
#include <time.h>
#include <windows.h>
#include <vector>
#include "data.h"
#include "food.h"
#include "snake.h"
#include "func.h"
using namespace std;

//构造函数（引用传参，可改实参
CFood::CFood(vector<COORD>& snaBody, vector<COORD>& barrArr)//传入蛇身以验证食物是否出现在蛇身
{
	GetRandomPos(snaBody, barrArr);
}

//获得随机位置
void CFood::GetRandomPos(vector<COORD>& snaBody, vector<COORD>& barrArr)
{
	m_FoodPos.X = rand() % (MAP_X_WALL / 2 - 2) + 1;//因为x是y一半，故/2
	//m_FoodPos.X = rand() % (MAP_X - 50) + 1;here
	m_FoodPos.Y = rand() % (MAP_Y - 2) + 1;

	for (int i = 0; i < snaBody.size(); i++)		//遍历蛇身
	{
		//食物不可出现在蛇身，若出现则重新生成
		if (snaBody[i].X == m_FoodPos.X && snaBody[i].Y == m_FoodPos.Y)
		{
			m_FoodPos.X = rand() % (MAP_X_WALL / 2 - 2) + 1;//因为x是y一半，故/2
			//m_FoodPos.X = rand() % (MAP_X - 50) + 1;here
			m_FoodPos.Y = rand() % (MAP_Y - 2) + 1;
		}
	}

	for (int i = 0; i < barrArr.size(); i++)		//遍历地图内所有障碍物
	{
		//食物不可出现在障碍物，若出现则重新生成
		if (barrArr[i].X == m_FoodPos.X && barrArr[i].Y == m_FoodPos.Y)
		{
			m_FoodPos.X = rand() % (MAP_X_WALL / 2 - 2) + 1;//因为x是y一半，故/2
			//m_FoodPos.X = rand() % (MAP_X - 50) + 1;here
			m_FoodPos.Y = rand() % (MAP_Y - 2) + 1;
		}
	}

}

//打印食物
void CFood::DrawFood()
{
	setColor(12, 0);	//食物红色
	//gotoxy(m_FoodPos.X, m_FoodPos.Y);
	gotoxy4s(m_FoodPos.X, m_FoodPos.Y);//here
	cout << "□";
	setColor(7, 0);		//再换回来
}

//获取食物位置
COORD CFood::GetFoodPos()
{
	return m_FoodPos;
}

