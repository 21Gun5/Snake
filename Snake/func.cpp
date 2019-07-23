#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <time.h>
#include <conio.h>
#include "data.h"
#include "func.h"
#include "food.h"
#include "snake.h"
#include "barrier.h"

using namespace std;

//��ӡ��ӭ����
void DrawWelcome()
{
 //      
	gotoxy(MAP_X / 2 - 25, MAP_Y / 2 -15);
	cout << " .M\"\"\"dgd       db      `7MN.   `7MF'`7MMF' `YMM' `7MM\"\"\"YMM " << endl;
	gotoxy(MAP_X / 2 - 25, MAP_Y / 2 - 14);
	cout << ",MI    \"Y      ;MM:       MMN.    M    MM   .M'     MM    `7 " << endl;
	gotoxy(MAP_X / 2 - 25, MAP_Y / 2 - 13);
	cout << "`MMb.         ,V^MM.      M YMb   M    MM .d\"       MM   d   " << endl;
	gotoxy(MAP_X / 2 - 25, MAP_Y / 2 - 12);
	cout << "  `YMMNq.    ,M  `MM      M  `MN. M    MMMMM.       MMmmMM   " << endl;
	gotoxy(MAP_X / 2 - 25, MAP_Y / 2 - 11);
	cout << ".     `MM    AbmmmqMA     M   `MM.M    MM  VMA      MM   Y  ," << endl;
	gotoxy(MAP_X / 2 - 25, MAP_Y / 2 - 10);
	cout << "Mb     dM   A'     VML    M     YMM    MM   `MM.    MM     ,M" << endl;
	gotoxy(MAP_X / 2 - 25, MAP_Y / 2 - 9);
	cout << "P\"Ybmmd\"  .AMA.   .AMMA..JML.    YM  .JMML.   MMb..JMMmmmmMMM" << endl;

	gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 6);
	cout << "1. ����Ϸ" << endl;
	gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 4);
	cout << "2. ��ȡ��Ϸ" << endl;
	gotoxy(MAP_X / 2 - 10, MAP_Y / 2 -2);
	cout << "3. ���Ƶ�ͼ" << endl;
	gotoxy(MAP_X / 2 - 10, MAP_Y / 2);
	cout << "4. �˳���Ϸ" << endl;
	gotoxy(MAP_X / 2 - 10, MAP_Y / 2 +2);
	cout << "������ѡ��-> ";
}

//��ӡ��ͼ�߽�
void DrawMap()
{
	system("cls");//������

	for (int x = 0; x < MAP_X; x+=2)//Ҫx+=2��������Ϊx1b��y2b������
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			if (g_MAP[x][y]== �߽�)
			{
				gotoxy(x, y);
				cout << "��";//ռ2B
				//cout << "#";
			}
			else
			{
				gotoxy(x, y);
				cout << " ";
			}
		}
	}

	//for (int x = 0; x < MAP_X; x+=2)//Ҫx+=2��������Ϊx1b��y2b������
	//{
	//	for (int y = 0; y < MAP_Y; y++)
	//	{
	//		if (g_MAP[x][y] == �߽�)
	//		{
	//			gotoxy4s(x, y);
	//			cout << "��";//ռ2B
	//			//cout << "#";
	//		}
	//		else
	//		{
	//			gotoxy(x, y);
	//			cout << "  ";
	//		}
	//	}
	//}

}

//��Ϸ����
void GameOver(int score)
{
	setColor(12, 0);

	gotoxy(MAP_X / 2 - 20, MAP_Y / 2 - 5);
	cout << "GAME OVER! " << endl;

	gotoxy(MAP_X / 2 - 20, MAP_Y / 2 - 3);
	cout << "Scores: " << score - 3 << endl;

	return;
}

//��ӡ�����Ϣ
void DrawGameInfo(int score,int barrSize)
{
	setColor(12, 0);
	gotoxy(MAP_X_WALL + 2, 1);
	cout << "RUNNING" << endl;//�������е�״̬��ʶ
	gotoxy(MAP_X_WALL + 2, 2);
	cout << "q: ��ͣ��Ϸ" << endl;
	setColor(7, 0);

	g_Speed = 5 + (300 - g_SleepTime) / 25;
	gotoxy(MAP_X - 22 + 14, 6);
	cout << "  ";
	gotoxy(MAP_X - 22 + 14, 4);
	cout << "  ";
	gotoxy(MAP_X - 22, 6);
	cout << "��ǰ����: " << (score - 3)*5 << endl;//-3��ԭʼ�߳�Ϊ3,*5����һ��Ϊ5��
	gotoxy(MAP_X - 22, 8);
	cout << "�ϰ�����: " << barrSize << endl;//
	gotoxy(MAP_X - 22, 10);
	cout << "��ǰ�ٶ�: " << g_Speed << endl;//

}

//��ӡ��Ϸ����
void DrawGameHelp()
{
	gotoxy(MAP_X-22+2, 18);
	cout << "����˵����" << endl;
	gotoxy(MAP_X-22, 20);
	cout << "W: ��    S: ��" << endl;
	gotoxy(MAP_X-22, 22);
	cout << "A: ��    D: ��" << endl;
	gotoxy(MAP_X - 22, 24);
	cout << "+:����  -:����" << endl;
	//gotoxy(MAP_X - 22, 26);
	//cout << "�����: �ָ���Ϸ" << endl;
}

//��ʼ������
void GameInit()
{
	//���ô��ڴ�Сhere
	//char buf[32];
	//sprintf_s(buf, "mode con cols=%d lines=%d", MAP_X, MAP_Y);
	//system(buf);

	//���õ�ͼ
	for (int x = 0; x < MAP_X; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			//��ͼ�߽�
			if (x == 0 || x == MAP_X-2  || y == 0 || y == MAP_Y - 1 || x== MAP_X_WALL || (x>MAP_X_WALL && y== MAP_Y/2))//x == MAP_X-2����xy���������
			{
				g_MAP[x][y] = �߽�;
			}
			//��ͼ�е��ϰ���
			//else if()
			else
			{
				g_MAP[x][y] = �յ�;
			}
		}
	}

	////���õ�ͼ
	//for (int x = 0; x < MAP_X; x++)
	//{
	//	for (int y = 0; y < MAP_Y; y++)
	//	{
	//		//��ͼ�߽�
	//		if (x == 0 || x == MAP_X  || y == 0 || y == MAP_Y - 1 || x== MAP_X_WALL || (x>MAP_X_WALL&& x<MAP_X && y== MAP_Y/2))//x == MAP_X-2����xy���������
	//		{
	//			g_MAP[x][y] = �߽�;
	//		}
	//		//��ͼ�е��ϰ���
	//		else
	//		{
	//			g_MAP[x][y] = �յ�;
	//		}
	//	}
	//}

	//���ع��
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);	//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = false;				//���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);	//���ÿ���̨���״̬

	//��ʼ�����������
	srand((unsigned int)time(0));

	//����BGM
	//while (true)//ѭ������
	//{
	//	PlaySoundA("conf\\BGM.wav", NULL, SND_ASYNC | SND_NODEFAULT);
	//}

	//�ȱ𲥣�����
	//PlaySoundA("conf\\BGM.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		
}

//�ƶ���꣨��ӡʳ��ߡ��ϰ���
void gotoxy4s(int x, int y)
{
	COORD cur;//ϵͳ�ṩ������ṹ��
	cur.X = x*2;//here�����������ٶȲ�ƥ��
	//cur.X = x;
	cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}

//�ƶ���꣨��ӡ��ͼ����������ʾ��Ϣ�������ã�
void gotoxy(int x, int y)
{
	COORD cur;//ϵͳ�ṩ������ṹ��
	//cur.X = x*2;//here�����������ٶȲ�ƥ��
	cur.X = x;
	cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}

//������ɫ
void setColor(unsigned short ForeColor, unsigned short BackGroundColor)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ��ǰ���ھ��
	SetConsoleTextAttribute(handle, ForeColor + BackGroundColor * 0x10);//������ɫ
}

//�浵
void SaveGame(CSnake& snake, CBarrier& barrier, CFood& food)
{
	////C++��ʽ
	//ofstream out("conf\\game2.i", ios::out | ios::binary);
	////д����
	//for (int i = 0; i < snake.m_SnakeBody.size(); i++)
	//{
	//	out.write((char*)&snake.m_SnakeBody[i], sizeof(COORD));
	//}
	//out.write((char*)& snake.m_Dir, sizeof(int));
	//out.write((char*)& snake.m_IsAlive, sizeof(bool));
	////д���ϰ���
	//for (int i = 0; i < barrier.m_size; i++)
	//{
	//	out.write((char*)& barrier.m_BarrArr[i], sizeof(COORD));
	//}
	//out.write((char*)& barrier.m_size, sizeof(int));
	////д��ʳ��
	//out.write((char*)& food.m_FoodPos, sizeof(COORD));
	//out.close();

	g_SnaCount = snake.m_SnakeBody.size();//Ϊ2
	g_BarCount = barrier.m_size;//15
	//���ļ�
	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, "conf\\game.i", "wb");
	//д�뵱ǰ˯��ʱ�䣬�Ա�֤�ٶ��ڶ�ȡʱҲ����
	fwrite(&g_SleepTime, sizeof(int), 1, pFile);
	//д���ϰ����������ߵ�����
	fwrite(&g_SnaCount, sizeof(int), 1, pFile);
	fwrite(&g_BarCount, sizeof(int), 1, pFile);
	//д���ϰ���
	for (int i = 0; i < barrier.m_size; i++)
	{
		fwrite(&barrier.m_BarrArr[i], sizeof(COORD), 1, pFile);
	}
	fwrite(&barrier.m_size, sizeof(int), 1, pFile);
	//д��ʳ��
	fwrite(&food.m_FoodPos, sizeof(COORD), 1, pFile);
	//д����
	for (int i = 0; i < snake.m_SnakeBody.size(); i++)
	{
		fwrite(&snake.m_SnakeBody[i], sizeof(COORD), 1, pFile);
	}
	fwrite(&snake.m_SnakeTail, sizeof(COORD), 1, pFile);//Ҫ����βҲд�룬��Ϊ��ȡ���ߣ���β�������Σ���������iseat���������ڹ��ڶ�ȡʱ��ҲҪ����βpushback��ȥ�����ֲ��ٵ���һ����һ����һ��������ȡ����������
	fwrite(&snake.m_Dir, sizeof(int), 1, pFile);
	fwrite(&snake.m_IsAlive, sizeof(bool), 1, pFile);
	
	//�ر��ļ�
	fclose(pFile);

}

//����
void LoadGame(CSnake& snake, CBarrier& barrier, CFood& food)
{
	////C++��ʽ
	//ifstream in("conf\\game2.i", ios::in | ios::binary);
	//COORD tmp;
	////��ȡ��
	//for (int i = 0; i < 3; i++)
	//{
	//	in.read((char*)& tmp, sizeof(COORD));
	//	snake.m_SnakeBody.push_back(tmp);
	//}
	//in.read((char*)& snake.m_Dir, sizeof(int));
	//in.read((char*)& snake.m_IsAlive, sizeof(bool));
	////��ȡ�ϰ���
	//for (int i = 0; i < 15; i++)
	//{
	//	in.read((char*)& tmp, sizeof(COORD));
	//	barrier.m_BarrArr.push_back(tmp);
	//}
	//in.read((char*)& barrier.m_size, sizeof(int));
	////��ȡʳ��
	//in.read((char*)& food.m_FoodPos, sizeof(COORD));
	//in.close();

	//���ļ�
	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, "conf\\game.i", "rb");

	//��ȡ��ǰ˯��ʱ�䣬�Ա�֤�ٶ��ڶ�ȡʱҲ����
	fread(&g_SleepTime, sizeof(int), 1, pFile);
	//д���ϰ����������ߵ�����
	fread(&g_SnaCount, sizeof(int), 1, pFile);
	fread(&g_BarCount, sizeof(int), 1, pFile);
	//��ȡ�ϰ���
	COORD tmp;
	for (int i = 0; i <g_BarCount; i++)
	{
		fread(&tmp, sizeof(COORD), 1, pFile);
		barrier.m_BarrArr.push_back(tmp);
	}
	fread(&barrier.m_size, sizeof(int), 1, pFile);
	//��ȡʳ��
	fread(&food.m_FoodPos, sizeof(COORD), 1, pFile);
	//��ȡ��
	COORD tmp2;
	for (int i = 0; i < g_SnaCount; i++)
	{
		fread(&tmp2, sizeof(COORD), 1, pFile);
		snake.m_SnakeBody.push_back(tmp2);
	}
	fread(&snake.m_SnakeTail, sizeof(COORD), 1, pFile);
	snake.m_SnakeBody.push_back(snake.m_SnakeTail);//�������Σ�Ҫ��һ����ȥ���ֲ�
	fread(&snake.m_Dir, sizeof(int), 1, pFile);//���ⱨ��
	fread(&snake.m_IsAlive, sizeof(bool), 1, pFile);//��

	//�ر��ļ�
	fclose(pFile);


	////���ļ�
	//FILE* pFile = NULL;
	//errno_t err = fopen_s(&pFile, "conf\\game2.i", "rb");
	////��ȡ�ļ�
	//fread(&snake, sizeof(CSnake), 1, pFile);
	//fread(&barrier, sizeof(CBarrier), 1, pFile);
	//fread(&food, sizeof(CFood), 1, pFile);
	////�ر��ļ�
	//fclose(pFile);

}


//�Զ����ͼ
void SaveMap()
{
	DrawMap();
	//��ӡ�༭��ͼ�İ�����Ϣ
	setColor(12, 0);
	gotoxy(MAP_X - 20, 4);
	cout << "�༭��ͼ" << endl;
	gotoxy(MAP_X - 24, 6);
	cout << "��������������ϰ�" << endl;
	gotoxy(MAP_X - 24, 8);
	cout << "�Ҽ������������ϰ�" << endl;
	gotoxy(MAP_X - 24, 10);
	cout << "����˫�����˳��༭" << endl;
	setColor(7, 0);

	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD ir = {};
	DWORD dwCount = 0;
	SetConsoleMode(hInput, ENABLE_MOUSE_INPUT);

	vector<COORD> BarrTmp;//�ϰ�������
	int barrTmpSize  = 0;

	while (true)
	{
		ReadConsoleInput(hInput,&ir,1,&dwCount);
		if (ir.EventType == MOUSE_EVENT)
		{
			if (ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;//��ȡ������λ��
				if (pos.X > 0 && pos.X < MAP_X_WALL && pos.Y >0 && pos.Y < MAP_Y)
				{
					//BarrTmp.push_back(pos);//��������
					//barrTmpSize++;

					g_BarrMAP[pos.X][pos.Y] = 1;
					gotoxy4s(pos.X/2, pos.Y);//����/2�������һƥ��5/2*2=4����֤��x����ռ������λ���ַ���xֻ����ż���������ܼ��ٳ����
					cout << "��";
				}
			}
			if (ir.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;
				if (pos.X > 0 && pos.X < MAP_X_WALL && pos.Y >0 && pos.Y < MAP_Y)
				{

					//for (vector<COORD>::iterator it = BarrTmp.begin(); it!=  BarrTmp.end(); it++)
					//{
					//	if (pos.X == it->X && pos.Y == it->Y)//����������ģ���ɾ��
					//	{
					//		BarrTmp.erase(it);
					//		barrTmpSize--;
					//		gotoxy4s(pos.X/2, pos.Y);
					//		cout << "  ";
					//	}
					//}

					g_BarrMAP[pos.X][pos.Y] = 0;
					gotoxy4s(pos.X/2, pos.Y);
					cout << "  ";
					
				}	
			}
			if (ir.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition; 
				if (!(pos.X > 0 && pos.X < MAP_X_WALL && pos.Y >0 && pos.Y < MAP_Y))
				{
					//��ͼ��˫�����˳���������������������ϰ�����
					break;
				}
			}
		}
	}


	for (int i = 0; i < MAP_X_WALL; i++)
	{
		for (int j = 0; j < MAP_Y; j++)
		{
			if (g_BarrMAP[i][j] == 1)
			{
				/*
				ԭ����51������x����������/2*2����5/2*2=4������41
				��ֱ�ӵ�X=x*2���Ǹ��ƶ�����������81��ӡ
				��Ҫ����ȷ��41������/2
				������Ӱ����ص����x��һ����λ����y��������λ���ӣ����ǣ�
				*/
				int t = i / 2;//5/2=2
				t = t * 2;//2*2=4���������
				COORD tmp = { t/2,j };//����Ϊ��ӡ��ʱ��Ҫ*2�����ٳ���
				BarrTmp.push_back(tmp);
				barrTmpSize++;
			}
		}
	}

	//д���ͼ�ļ�
	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, "conf\\map.i", "wb");
	fwrite(&barrTmpSize, sizeof(int), 1, pFile);//д���ϰ�������
	for (int i = 0; i < BarrTmp.size(); i++)//д���ϰ���
	{
		fwrite(&BarrTmp[i], sizeof(COORD), 1, pFile);
	}
	fclose(pFile);
}

//�����û��Զ���ĵ�ͼ
void LoadMap(CBarrier& barrier)
{
	//vector<COORD> BarrTmp;//�ϰ�������
	//int barrTmpSize = 0;
	COORD tmp;

	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, "conf\\map.i", "rb");
	fread(&barrier.m_size, sizeof(int), 1, pFile);//д���ϰ�������
	for (int i = 0; i < barrier.m_size; i++)//д���ϰ���
	{
		fread(&tmp, sizeof(COORD), 1, pFile);
		barrier.m_BarrArr.push_back(tmp);//һ��Ҫ����tmp����������ֱ�Ӷ���BarrTmp[i]
	}
	fclose(pFile);

	//cout << barrTmpSize << endl;
	//for (int i = 0; i < barrTmpSize; i++)
	//{
	//	cout << BarrTmp[i].X << BarrTmp[i].Y << endl;
	//}
}

//�����û�����
int HandleSelect()
{
	//char ch = getchar();//��Ҫ�س���ȷ����������ɼ�
	char ch = _getch();//����س���ȷ�������޻���

	int res = 0;

	switch (ch)
	{
	case '1'://����Ϸ
		g_isRunning = true;
		res = 1;
		break;
	case '2'://����
		g_isRunning = true;
		res = 2;
		break;
	case '3'://�Զ����ͼ
		res = 3;
		break;
	case '4'://�˳���Ϸ
		gotoxy(MAP_X / 2 - 10, MAP_Y / 2 + 3);
		cout << "Bye��" << endl;
		res = 0;
		//cin.get();
		break;
	default:
		gotoxy(MAP_X / 2 - 10, MAP_Y / 2 + 3);
		cout << "�������";
		break;
	}
	return res;
}

//�����û����루ѡ���ͼ
int HandleSelectMap()
{
	system("cls");
	
	gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 6);
	cout << "��ѡ���ͼ��" << endl;
	gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 4);
	cout << "1. ϵͳĬ��" << endl;
	gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 2);
	cout << "2. ����ṩ" << endl;
	gotoxy(MAP_X / 2 - 10, MAP_Y / 2);
	cout << "������ѡ��-> ";

	int rres = 0;
	//char cch = getchar();//��Ҫ�س���ȷ����������ɼ�
	char cch = _getch();
	
	switch (cch)
	{
	case '1'://ϵͳĬ��
		break;
	case '2'://����ṩ
		rres = 1;
		break;
	default:
		gotoxy(MAP_X / 2 - 10, MAP_Y / 2 + 3);
		cout << "�������";
		break;
	}

	return rres;

}

//�����û����루ѡ��ȼ���
void HandleSelectLevel()
{
	//ͨ��ʱ����ϰ��������Ѷ�
	system("cls");

	gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 6);
	cout << "��Ϸ�Ѷȣ�" << endl;
	gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 4);
	cout << "1. ��" << endl;
	gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 2);
	cout << "2. һ��" << endl;
	gotoxy(MAP_X / 2 - 10, MAP_Y / 2);
	cout << "3. ����" << endl;
	gotoxy(MAP_X / 2 - 10, MAP_Y / 2+2);
	cout << "������ѡ��-> ";

	char cch = _getch();
	switch (cch)
	{
	case '1'://��
		g_LevelBarrsize = 10;
		g_SleepTime = 400;
		break;
	case '2'://һ��
		g_LevelBarrsize = 20;
		g_SleepTime = 300;
		break;
	case '3'://����
		g_LevelBarrsize = 40;
		g_SleepTime = 200;
		break;
	}
}

////��Ϸ��ѭ��
//void PlayGame(CSnake & snake,CBarrier & barrier, CFood & food)
//{
//
//}

////������Ϸ�Ѷȵȼ�
//void SetLevel()
//{
//
//}

//void PlaySnd(string sound)
//{
//	//����BGM
//	//conf\\BGM.wav
//	sound = "conf\\BGM.wav";
//	PlaySoundA("conf\\BGM.wav", NULL, SND_ASYNC | SND_NODEFAULT);
//}

///////////////////////////////////////////////////////////////////////////////////

//1. ����Ļ�κ�λ������ַ���
//void WriteChar(int x, int y, const char* p, int color = 0)
//{
//	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ��׼����������������Ļ
//	COORD pos = { x, y };//����ṹ��
//	SetConsoleCursorPosition(hOutput, pos);//������ƶ��� ��Ļ��ָ������λ��
//	printf(p);//��ָ��λ�ô�ӡ
//}

//// 2. �ܿ��Ƶ������ƶ��ĵ�
//void moveSth()
//{
//	//��겻�ɼ�
//	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ��Ļ�������������Ϊָ��ĳ�����ָ�룬�˾���ʹ���ĳ����
//	CONSOLE_CURSOR_INFO cci;//����̨������
//	cci.dwSize = sizeof(cci);//����С���������ã�
//	cci.bVisible = FALSE;//���ù��״̬Ϊ���ɼ�
//	SetConsoleCursorInfo(hOutput, &cci);//�����״̬Ӧ�õ���Ļ��
//
//	int x = 10;
//	int y = 20;
//	int nDir = 0;
//	char ch = 0;
//	while (true)
//	{
//		int Oldx = x;
//		int Oldy = y;
//		WriteChar(x, y, "��");//ָ��λ�ô�ӡ����
//		if (_kbhit() == 1)//��������������ͬ��scanf����һֱ�����ȴ��û�����
//		{
//			ch = _getch();//�޻��ԵĻ�ȡ�ַ�
//		}
//		else
//		{
//			ch = 0;
//		}
//		switch (ch)//ͨ�����������Ʒ�����ͨ������������λ�ñ仯����ͬ�����棬ֱ��ͨ������������λ��
//		{
//		case 'w':
//			nDir = 0;
//			break;
//		case 's':
//			nDir = 1;
//			break;
//		case 'a':
//			nDir = 2;
//			break;
//		case 'd':
//			nDir = 3;
//			break;
//		default:
//			break;
//		}
//
//		switch (nDir)//��ͨ������������λ�ñ仯���������м��˽�ɫ��
//		{
//		case 0:
//			y--;
//			break;
//		case 1:
//			y++;
//			break;
//		case 2:
//			x--;
//			break;
//		case 3:
//			x++;
//			break;
//		default:
//			break;
//		}
//		Sleep(100);//�����ٶ�
//		//��λ�ô�ӡ�գ���λ�ô�ӡ�ַ���ʵ���ƶ���Ч��
//		//��������system("cls")�������ַ�ʽ����ʹ��Ļ��
//		WriteChar(Oldx, Oldy, " ");//��λ��
//		WriteChar(x, y, "��");
//	}
//}

//// 3. ��껭ͼ
//void DrawMouse()
//{
//	system("cls");
//	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
//	INPUT_RECORD ir = {};
//	DWORD dwCount = 0;
//
//	SetConsoleMode(hInput, ENABLE_MOUSE_INPUT);
//	while (true)
//	{
//		
//		ReadConsoleInput(
//			hInput,  
//			&ir,     
//			1,       
//			&dwCount 
//		);
//		if (ir.EventType == MOUSE_EVENT)
//		{
//			if (ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
//			{
//				COORD pos = ir.Event.MouseEvent.dwMousePosition;//��ȡ������λ��
//				//��Ϊ������һ���ַ��������ǰ���ַ�����x����Ҫ/2��ʹ�����������ҵ��ٶ�һ�£�Ϊ����x/2����
//				gotoxy4s(pos.X / 2, pos.Y);
//				cout << "��";
//
//			}
//			if (ir.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
//			{
//				COORD pos = ir.Event.MouseEvent.dwMousePosition;
//				gotoxy4s(pos.X / 2, pos.Y);
//				cout << "  ";
//			}
//
//		}
//	}
//
//}

// 4. �ƶ���
// 5. ��ʳ��䳤
// 6. ��ά������ͼ����Ҫ����Ĺ滮����




