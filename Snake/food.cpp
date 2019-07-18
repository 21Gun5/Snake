//#include <time.h>
//#include <iostream>
//#include <vector>
//#include "setting.h"
//#include "food.h"
//#include "snake.h"
//using namespace std;
//
////获取随机位置
//void CFood::RandomXY(vector<COORDINATE>& coord)
//{
//	m_coordinate.x = rand() % (CSetting::window_width - 30) + 1;
//	m_coordinate.y = rand() % (CSetting::window_height - 2) + 1;
//	unsigned int i;
//	//原则上不允许食物出现在蛇的位置上，如果有，重新生成
//	for (i = 0; i < coord.size(); i++)
//	{
//		//食物出现在蛇身的位置上。重新生成
//		if (coord[i].x == m_coordinate.x && coord[i].y == m_coordinate.y)
//		{
//			m_coordinate.x = rand() % (CSetting::window_width - 30) + 1;
//			m_coordinate.y = rand() % (CSetting::window_height - 2) + 1;
//			i = 0;
//		}
//	}
//}
//
////有参构造函数
//CFood::CFood(vector<COORDINATE>& coord)
//{
//	RandomXY(coord);
//}
//
////画食物
//void CFood::DrawFood()
//{
//	setColor(12, 0);
//	gotoxy(m_coordinate.x, m_coordinate.y);
//	cout << "@";
//	setColor(7, 0);
//}
//
////获取食物位置
//COORDINATE CFood::GetFoodCoordinate()
//{
//	return m_coordinate;
//}