//#include <iostream>
//#include <time.h>
//#include <vector>
//#include "data.h"
//#include "food.h"
//#include "snake.h"
//#include "func.h"
//using namespace std;
//
////���캯��
//CFood::CFood(vector<POS>& snaBody)//������������֤ʳ���Ƿ����������
//{
//	CFood::GetRandomPos(snaBody);
//}
//
////������λ��
//void CFood::GetRandomPos(vector<POS>& snaBody)
//{
//	m_FoodPos.x = rand() % (g_window_width - 30) + 1;
//	m_FoodPos.y = rand() % (g_window_height - 2) + 1;
//
//	for (int i = 0; i < snaBody.size(); i++)		//��������
//	{
//		//ʳ�ﲻ�ɳ�������������������������
//		if (snaBody[i].x == m_FoodPos.x && snaBody[i].y == m_FoodPos.y)
//		{
//			m_FoodPos.x = rand() % (g_window_width - 30) + 1;
//			m_FoodPos.y = rand() % (g_window_height - 2) + 1;
//		}
//	}
//}
//
////��ӡʳ��
//void CFood::DrawFood()
//{
//	setColor(12, 0);	//ʳ���ɫ
//	gotoxy(m_FoodPos.x, m_FoodPos.y);
//	cout << "$";
//	setColor(7, 0);		//�ٻ�����
//}
//
////��ȡʳ��λ��
//POS CFood::GetFoodPos()
//{
//	return m_FoodPos;
//}
