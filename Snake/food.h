//#pragma once
//#include <vector>
//#include "setting.h"
//#include "snake.h"
//
////ʳ����
//class Food
//{	
//public:
//	POS m_FoodPos;		//ʳ������
//
//	//���캯�����������Ϊ��������
//	Food(vector<POS>& coord)
//	{
//		RandomXY(coord);
//	}
//
//	//������λ��
//	void RandomXY(vector<POS>& coord)
//	{
//		m_FoodPos.x = rand() % (CSetting::window_width - 30) + 1;
//		m_FoodPos.y = rand() % (CSetting::window_height - 2) + 1;
//		unsigned int i;
//
//		//ʳ�ﲻ���������ϣ�����Ҫ��������
//		for (i = 0; i < coord.size(); i++)
//		{
//			//��������
//			if (coord[i].x == m_FoodPos.x && coord[i].y == m_FoodPos.y)
//			{
//				m_FoodPos.x = rand() % (CSetting::window_width - 30) + 1;
//				m_FoodPos.y = rand() % (CSetting::window_height - 2) + 1;
//				i = 0;
//			}
//		}
//	}
//
//	//��ӡʳ��
//	void DrawFood()
//	{
//		setColor(12, 0);
//		gotoxy(m_FoodPos.x, m_FoodPos.y);
//		cout << "@";
//		setColor(7, 0);
//	}
//
//	//��ȡʳ��λ��
//	POS GetFoodPos()
//	{
//		return m_FoodPos;
//	}
//};
