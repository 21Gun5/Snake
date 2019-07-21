//#include <iostream>
//#include <time.h>
//#include <vector>
//#include "data.h"
//#include "food.h"
//#include "snake.h"
//#include "func.h"
//using namespace std;
//
////构造函数
//CFood::CFood(vector<POS>& snaBody)//传入蛇身以验证食物是否出现在蛇身
//{
//	CFood::GetRandomPos(snaBody);
//}
//
////获得随机位置
//void CFood::GetRandomPos(vector<POS>& snaBody)
//{
//	m_FoodPos.x = rand() % (g_window_width - 30) + 1;
//	m_FoodPos.y = rand() % (g_window_height - 2) + 1;
//
//	for (int i = 0; i < snaBody.size(); i++)		//遍历蛇身
//	{
//		//食物不可出现在蛇身，若出现则重新生成
//		if (snaBody[i].x == m_FoodPos.x && snaBody[i].y == m_FoodPos.y)
//		{
//			m_FoodPos.x = rand() % (g_window_width - 30) + 1;
//			m_FoodPos.y = rand() % (g_window_height - 2) + 1;
//		}
//	}
//}
//
////打印食物
//void CFood::DrawFood()
//{
//	setColor(12, 0);	//食物红色
//	gotoxy(m_FoodPos.x, m_FoodPos.y);
//	cout << "$";
//	setColor(7, 0);		//再换回来
//}
//
////获取食物位置
//POS CFood::GetFoodPos()
//{
//	return m_FoodPos;
//}
