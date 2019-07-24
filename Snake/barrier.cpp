#include <iostream>
#include <stdlib.h>
#include <vector>
#include <windows.h>
#include "barrier.h"
#include "func.h"
#include "data.h"
using namespace std;

//�޲ι��죬��ȡ�ļ�ʱ�����������Ϊ��
CBarrier::CBarrier() {}

//�вι���
CBarrier::CBarrier(vector<COORD>& snaBody, int size) :m_size(size)
{
	COORD barr;
	for (int i = 0; i < m_size; i++)
	{
		//��������
		for (int j = 0; j < snaBody.size(); j++)
		{
			barr.X = rand() % (MAP_X_WALL / 2 - 2);
			barr.Y = rand() % (MAP_Y - 2) + 1;

			//�ϰ����ɳ�������������������������
			if (snaBody[j].X == barr.X && snaBody[j].Y == barr.Y)
			{
				barr.X = rand() % (MAP_X_WALL / 2 - 2);
				barr.Y = rand() % (MAP_Y - 2) + 1;
			}

		}

		m_BarrArr.push_back(barr);

	}
}

//��ӡ�ϰ���
void CBarrier::DrawBarr()
{
	for (int i = 0; i < m_size; i++)
	{
		GotoxyFor2(m_BarrArr[i].X, m_BarrArr[i].Y);
		cout << "��";
	}
}

//�õ���ͼ���ϰ�������
int CBarrier::GetBarrSize()
{
	return m_size;
}

//
//vector<COORD> CBarrier::SetBarr()
//{
//	DrawMapBorder();		//���ȴ�ӡ��ͼ�߽�
//
//	//��ʾ��Ϣ
//	setColor(12, 0);
//	gotoxy(MAP_X - 20, 4);
//	cout << "�༭��ͼ" << endl;
//	gotoxy(MAP_X - 24, 6);
//	cout << "��������������ϰ�" << endl;
//	gotoxy(MAP_X - 24, 8);
//	cout << "�Ҽ������������ϰ�" << endl;
//	gotoxy(MAP_X - 24, 10);
//	cout << "����˫�����˳��༭" << endl;
//	setColor(7, 0);
//
//	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
//	INPUT_RECORD ir = {};
//	DWORD dwCount = 0;
//	SetConsoleMode(hInput, ENABLE_MOUSE_INPUT);
//
//	vector<COORD> BarrTmp;//�ϰ�������
//	int barrTmpSize = 0;
//
//	while (true)
//	{
//		ReadConsoleInput(hInput, &ir, 1, &dwCount);
//		if (ir.EventType == MOUSE_EVENT)
//		{
//			if (ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
//			{
//				COORD pos = ir.Event.MouseEvent.dwMousePosition;//��ȡ������λ��
//				if (pos.X > 0 && pos.X < MAP_X_WALL && pos.Y >0 && pos.Y < MAP_Y)
//				{
//					//BarrTmp.push_back(pos);//��������
//					//barrTmpSize++;
//
//					g_BarrMAP[pos.X][pos.Y] = 1;
//					gotoxy4s(pos.X / 2, pos.Y);//����/2�������һƥ��5/2*2=4����֤��x����ռ������λ���ַ���xֻ����ż���������ܼ��ٳ����
//					cout << "��";
//				}
//			}
//			if (ir.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
//			{
//				COORD pos = ir.Event.MouseEvent.dwMousePosition;
//				if (pos.X > 0 && pos.X < MAP_X_WALL && pos.Y >0 && pos.Y < MAP_Y)
//				{
//
//					//for (vector<COORD>::iterator it = BarrTmp.begin(); it!=  BarrTmp.end(); it++)
//					//{
//					//	if (pos.X == it->X && pos.Y == it->Y)//����������ģ���ɾ��
//					//	{
//					//		BarrTmp.erase(it);
//					//		barrTmpSize--;
//					//		gotoxy4s(pos.X/2, pos.Y);
//					//		cout << "  ";
//					//	}
//					//}
//
//					g_BarrMAP[pos.X][pos.Y] = 0;
//					gotoxy4s(pos.X / 2, pos.Y);
//					cout << "  ";
//
//				}
//			}
//			if (ir.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
//			{
//				COORD pos = ir.Event.MouseEvent.dwMousePosition;
//				if (!(pos.X > 0 && pos.X < MAP_X_WALL && pos.Y >0 && pos.Y < MAP_Y))
//				{
//					//��ͼ��˫�����˳���������������������ϰ�����
//					break;
//				}
//			}
//		}
//	}
//
//
//	for (int i = 0; i < MAP_X_WALL; i++)
//	{
//		for (int j = 0; j < MAP_Y; j++)
//		{
//			if (g_BarrMAP[i][j] == 1)
//			{
//				/*
//				ԭ����51������x����������/2*2����5/2*2=4������41
//				��ֱ�ӵ�X=x*2���Ǹ��ƶ�����������81��ӡ
//				��Ҫ����ȷ��41������/2
//				������Ӱ����ص����x��һ����λ����y��������λ���ӣ����ǣ�
//				*/
//				int t = i / 2;//5/2=2
//				t = t * 2;//2*2=4���������
//				COORD tmp = { t / 2,j };//����Ϊ��ӡ��ʱ��Ҫ*2�����ٳ���
//				BarrTmp.push_back(tmp);
//				barrTmpSize++;
//			}
//		}
//	}
//
//	return BarrTmp;
//}
//
//
//void CBarrier::SaveBarrFile(vector<COORD> &BarrTmp)
//{
//	int barrTmpSize = BarrTmp.size();
//	//д���ͼ�ļ�
//	FILE* pFile = NULL;
//	errno_t err = fopen_s(&pFile, "conf\\map.i", "wb");
//	fwrite(&barrTmpSize, sizeof(int), 1, pFile);//д���ϰ�������
//	for (int i = 0; i < BarrTmp.size(); i++)//д���ϰ���
//	{
//		fwrite(&BarrTmp[i], sizeof(COORD), 1, pFile);
//	}
//	fclose(pFile);
//}
