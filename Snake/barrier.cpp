#include <iostream>
#include <stdlib.h>
#include <vector>
#include <windows.h>
#include "barrier.h"
#include "func.h"
#include "data.h"
using namespace std;

//无参构造，读取文件时，对象接收者为空
CBarrier::CBarrier() {}

//有参构造
CBarrier::CBarrier(vector<COORD>& snaBody, int size) :m_size(size)
{
	COORD barr;
	for (int i = 0; i < m_size; i++)
	{
		//遍历蛇身
		for (int j = 0; j < snaBody.size(); j++)
		{
			barr.X = rand() % (MAP_X_WALL / 2 - 2);
			barr.Y = rand() % (MAP_Y - 2) + 1;

			//障碍不可出现在蛇身，若出现则重新生成
			if (snaBody[j].X == barr.X && snaBody[j].Y == barr.Y)
			{
				barr.X = rand() % (MAP_X_WALL / 2 - 2);
				barr.Y = rand() % (MAP_Y - 2) + 1;
			}

		}

		m_BarrArr.push_back(barr);

	}
}

//打印障碍物
void CBarrier::DrawBarr()
{
	for (int i = 0; i < m_size; i++)
	{
		GotoxyFor2(m_BarrArr[i].X, m_BarrArr[i].Y);
		cout << "※";
	}
}

//得到地图内障碍物数量
int CBarrier::GetBarrSize()
{
	return m_size;
}

//
//vector<COORD> CBarrier::SetBarr()
//{
//	DrawMapBorder();		//首先打印地图边界
//
//	//提示信息
//	setColor(12, 0);
//	gotoxy(MAP_X - 20, 4);
//	cout << "编辑地图" << endl;
//	gotoxy(MAP_X - 24, 6);
//	cout << "左键单击：创建障碍" << endl;
//	gotoxy(MAP_X - 24, 8);
//	cout << "右键单击：消除障碍" << endl;
//	gotoxy(MAP_X - 24, 10);
//	cout << "界外双击：退出编辑" << endl;
//	setColor(7, 0);
//
//	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
//	INPUT_RECORD ir = {};
//	DWORD dwCount = 0;
//	SetConsoleMode(hInput, ENABLE_MOUSE_INPUT);
//
//	vector<COORD> BarrTmp;//障碍物数组
//	int barrTmpSize = 0;
//
//	while (true)
//	{
//		ReadConsoleInput(hInput, &ir, 1, &dwCount);
//		if (ir.EventType == MOUSE_EVENT)
//		{
//			if (ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
//			{
//				COORD pos = ir.Event.MouseEvent.dwMousePosition;//获取按键的位置
//				if (pos.X > 0 && pos.X < MAP_X_WALL && pos.Y >0 && pos.Y < MAP_Y)
//				{
//					//BarrTmp.push_back(pos);//加入数组
//					//barrTmpSize++;
//
//					g_BarrMAP[pos.X][pos.Y] = 1;
//					gotoxy4s(pos.X / 2, pos.Y);//在这/2真是妙的一匹，5/2*2=4，保证这x方向占两个单位的字符，x只能是偶数，这样能减少出错，妙！
//					cout << "※";
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
//					//	if (pos.X == it->X && pos.Y == it->Y)//若是数组里的，则删除
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
//					//地图外双击才退出，避免与左键单击创建障碍混淆
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
//				原来是51，避免x是奇数，故/2*2，即5/2*2=4，即得41
//				若直接调X=x*2的那个移动函数，则在81打印
//				若要得正确的41，则再/2
//				真他妈坑啊，藏得真深，x轴一个单位，而y轴两个单位，坑！谨记！
//				*/
//				int t = i / 2;//5/2=2
//				t = t * 2;//2*2=4，妙啊！！！
//				COORD tmp = { t / 2,j };//，因为打印的时候还要*2，故再除二
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
//	//写入地图文件
//	FILE* pFile = NULL;
//	errno_t err = fopen_s(&pFile, "conf\\map.i", "wb");
//	fwrite(&barrTmpSize, sizeof(int), 1, pFile);//写入障碍物数量
//	for (int i = 0; i < BarrTmp.size(); i++)//写入障碍物
//	{
//		fwrite(&BarrTmp[i], sizeof(COORD), 1, pFile);
//	}
//	fclose(pFile);
//}
