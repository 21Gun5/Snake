//#include <iostream>
//#include <time.h>
//#include <vector>
//#include "setting.h"
//#include "food.h"
//#include "snake.h"
//using namespace std;
//
//
////构造函数，传入参数为蛇身坐标
//CFood::CFood(vector<POS>& coord)
//{
//	CFood::RandomXY(coord);
//}
//
////获得随机位置
//void CFood::RandomXY(vector<POS>& coord)
//{
//	m_FoodPos.x = rand() % (CSetting::window_width - 30) + 1;
//	m_FoodPos.y = rand() % (CSetting::window_height - 2) + 1;
//	unsigned int i;
//	//原则上不允许食物出现在蛇的位置上，如果有，重新生成
//	for (i = 0; i < coord.size(); i++)
//	{
//		//食物出现在蛇身的位置上。重新生成
//		if(coord[i].x == m_FoodPos.x && coord[i].y == m_FoodPos.y)
//		{
//			m_FoodPos.x = rand() % (CSetting::window_width - 30) + 1;
//			m_FoodPos.y = rand() % (CSetting::window_height - 2) + 1;
//			i = 0;
//		}
//	}
//}
//
////打印食物
//void CFood::DrawFood()
//{
//	setColor(12, 0);
//	gotoxy(m_FoodPos.x, m_FoodPos.y);
//	cout << "@";
//	setColor(7, 0);
//}
//
////获取食物位置
//POS CFood::GetFoodPos()
//{
//	return m_FoodPos;
//}