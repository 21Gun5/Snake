//#pragma once
//#include <vector>
//#include "setting.h"
//#include "snake.h"
//
////食物类
//class Food
//{	
//public:
//	POS m_FoodPos;		//食物坐标
//
//	//构造函数，传入参数为蛇身坐标
//	Food(vector<POS>& coord)
//	{
//		RandomXY(coord);
//	}
//
//	//获得随机位置
//	void RandomXY(vector<POS>& coord)
//	{
//		m_FoodPos.x = rand() % (CSetting::window_width - 30) + 1;
//		m_FoodPos.y = rand() % (CSetting::window_height - 2) + 1;
//		unsigned int i;
//
//		//食物不可在蛇身上，若有要重新生成
//		for (i = 0; i < coord.size(); i++)
//		{
//			//重新生成
//			if (coord[i].x == m_FoodPos.x && coord[i].y == m_FoodPos.y)
//			{
//				m_FoodPos.x = rand() % (CSetting::window_width - 30) + 1;
//				m_FoodPos.y = rand() % (CSetting::window_height - 2) + 1;
//				i = 0;
//			}
//		}
//	}
//
//	//打印食物
//	void DrawFood()
//	{
//		setColor(12, 0);
//		gotoxy(m_FoodPos.x, m_FoodPos.y);
//		cout << "@";
//		setColor(7, 0);
//	}
//
//	//获取食物位置
//	POS GetFoodPos()
//	{
//		return m_FoodPos;
//	}
//};
