//#include <time.h>
//#include <iostream>
//#include <vector>
//#include "setting.h"
//#include "food.h"
//#include "snake.h"
//using namespace std;
//
////��ȡ���λ��
//void CFood::RandomXY(vector<COORDINATE>& coord)
//{
//	m_coordinate.x = rand() % (CSetting::window_width - 30) + 1;
//	m_coordinate.y = rand() % (CSetting::window_height - 2) + 1;
//	unsigned int i;
//	//ԭ���ϲ�����ʳ��������ߵ�λ���ϣ�����У���������
//	for (i = 0; i < coord.size(); i++)
//	{
//		//ʳ������������λ���ϡ���������
//		if (coord[i].x == m_coordinate.x && coord[i].y == m_coordinate.y)
//		{
//			m_coordinate.x = rand() % (CSetting::window_width - 30) + 1;
//			m_coordinate.y = rand() % (CSetting::window_height - 2) + 1;
//			i = 0;
//		}
//	}
//}
//
////�вι��캯��
//CFood::CFood(vector<COORDINATE>& coord)
//{
//	RandomXY(coord);
//}
//
////��ʳ��
//void CFood::DrawFood()
//{
//	setColor(12, 0);
//	gotoxy(m_coordinate.x, m_coordinate.y);
//	cout << "@";
//	setColor(7, 0);
//}
//
////��ȡʳ��λ��
//COORDINATE CFood::GetFoodCoordinate()
//{
//	return m_coordinate;
//}