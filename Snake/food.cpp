//#include <iostream>
//#include <time.h>
//#include <vector>
//#include "setting.h"
//#include "food.h"
//#include "snake.h"
//using namespace std;
//
//
////���캯�����������Ϊ��������
//CFood::CFood(vector<POS>& coord)
//{
//	CFood::RandomXY(coord);
//}
//
////������λ��
//void CFood::RandomXY(vector<POS>& coord)
//{
//	m_FoodPos.x = rand() % (CSetting::window_width - 30) + 1;
//	m_FoodPos.y = rand() % (CSetting::window_height - 2) + 1;
//	unsigned int i;
//	//ԭ���ϲ�����ʳ��������ߵ�λ���ϣ�����У���������
//	for (i = 0; i < coord.size(); i++)
//	{
//		//ʳ������������λ���ϡ���������
//		if(coord[i].x == m_FoodPos.x && coord[i].y == m_FoodPos.y)
//		{
//			m_FoodPos.x = rand() % (CSetting::window_width - 30) + 1;
//			m_FoodPos.y = rand() % (CSetting::window_height - 2) + 1;
//			i = 0;
//		}
//	}
//}
//
////��ӡʳ��
//void CFood::DrawFood()
//{
//	setColor(12, 0);
//	gotoxy(m_FoodPos.x, m_FoodPos.y);
//	cout << "@";
//	setColor(7, 0);
//}
//
////��ȡʳ��λ��
//POS CFood::GetFoodPos()
//{
//	return m_FoodPos;
//}