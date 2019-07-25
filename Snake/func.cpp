#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <io.h>
#include <time.h>
#include <iomanip>
#include <conio.h>
#include "data.h"
#include "func.h"
#include "food.h"
#include "snake.h"
#include "barrier.h"

using namespace std;

void DrawWelcome()
{
	/*
	1. ��ӡ��ӭ����
	2. ����ͼ������ʾ��Ϣ
	*/

	 //��ӡͼ��
	Gotoxy(MAP_X / 2 - 25, MAP_Y / 2 - 15);
	cout << " .M\"\"\"dgd       db      `7MN.   `7MF'`7MMF' `YMM' `7MM\"\"\"YMM " << endl;
	Gotoxy(MAP_X / 2 - 25, MAP_Y / 2 - 14);
	cout << ",MI    \"Y      ;MM:       MMN.    M    MM   .M'     MM    `7 " << endl;
	Gotoxy(MAP_X / 2 - 25, MAP_Y / 2 - 13);
	cout << "`MMb.         ,V^MM.      M YMb   M    MM .d\"       MM   d   " << endl;
	Gotoxy(MAP_X / 2 - 25, MAP_Y / 2 - 12);
	cout << "  `YMMNq.    ,M  `MM      M  `MN. M    MMMMM.       MMmmMM   " << endl;
	Gotoxy(MAP_X / 2 - 25, MAP_Y / 2 - 11);
	cout << ".     `MM    AbmmmqMA     M   `MM.M    MM  VMA      MM   Y  ," << endl;
	Gotoxy(MAP_X / 2 - 25, MAP_Y / 2 - 10);
	cout << "Mb     dM   A'     VML    M     YMM    MM   `MM.    MM     ,M" << endl;
	Gotoxy(MAP_X / 2 - 25, MAP_Y / 2 - 9);
	cout << "P\"Ybmmd\"  .AMA.   .AMMA..JML.    YM  .JMML.   MMb..JMMmmmmMMM" << endl;

	//��ʾ��Ϣ
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 6);
	cout << "1. ����Ϸ" << endl;
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 4);
	cout << "2. ��ȡ��Ϸ" << endl;
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 2);
	cout << "3. �˳���Ϸ" << endl;
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 -0);
	cout << "������ѡ��-> ";
	SetCursorState(true);			//�û�����ʱ�����ɼ�
}

void DrawMapBorder()
{
	/*
	1. ��ӡ��ͼ�߽�
	*/

	system("cls");						//��ҳ������
	for (int x = 0; x < MAP_X; x += 2)	//Ҫx+=2����xy�����С��ͬ
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			if (g_MAP[x][y] == �߽�)
			{
				Gotoxy(x, y);
				cout << "��";			//ռ2�ַ�
			}
		}
	}
}

void GameOver(int score)
{
	/*
	1. ��Ϸ�������ɨβ����
	2. �ر�bgm�ļ�
	3. ��Ϸ��������ʾ��Ϣ�����շ���
	*/

	//�ر������ļ�
	mciSendString("close bgm", NULL, 0, NULL);	//close�رն���stopֹͣ
	
	//��ʾ��Ϣ
	setColor(12, 0);
	Gotoxy(MAP_X / 2 - 20, MAP_Y / 2 - 5);
	cout << "GAME OVER! " << endl;
	Gotoxy(MAP_X / 2 - 20, MAP_Y / 2 - 3);
	cout << "Scores: " << score - 3 << endl;	//�����ʼ3��

	return;
}

void DrawGameInfo(int score, int barrSize,int blood)
{
	/*
	1. ����״̬
	2. ����������ֵ��
	*/

	//����or��ͣ״̬
	setColor(12, 0);
	Gotoxy(MAP_X_WALL + 2, 1);
	cout << "RUNNING" << endl;//�������е�״̬��ʶ
	Gotoxy(MAP_X_WALL + 2, 2);
	cout << "q: ��ͣ��Ϸ" << endl;
	setColor(7, 0);

	//��������Ϣ
	g_Speed = 5 + (300 - g_SleepTime) / 25;
	Gotoxy(MAP_X - 22 + 14, 6);
	cout << "  ";
	Gotoxy(MAP_X - 22 + 14, 4);
	cout << "  ";
	Gotoxy(MAP_X - 22, 5);
	cout << "��ǰ����: " << setw(2) << (score - 3) * 5 << endl;//-3��ԭʼ�߳�Ϊ3��*5����һ��5��
	Gotoxy(MAP_X - 22, 7);
	cout << "��ǰ����: " << setw(2) << blood << endl;
	Gotoxy(MAP_X - 22, 9);
	cout << "�ϰ�����: " << setw(2) << barrSize << endl;
	Gotoxy(MAP_X - 22, 11);
	cout << "��ǰ�ٶ�: " << setw(2)<< g_Speed << endl;			//��setw������10��9��0����
}

void DrawGameHelp()
{
	//��ӡ��Ϸ����
	Gotoxy(MAP_X - 22 + 2, 18);
	cout << "����˵����" << endl;
	Gotoxy(MAP_X - 22, 20);
	cout << "W: ��    S: ��" << endl;
	Gotoxy(MAP_X - 22, 22);
	cout << "A: ��    D: ��" << endl;
	Gotoxy(MAP_X - 22, 24);
	cout << "+:����  -:����" << endl;
}

void SetCursorState(bool b)
{
	/*
	1. ���ù��״̬
	2. �û�����ǰ��ʾ���꣬���������
	*/

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);	//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = b;					//��ʾ/���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);	//���ÿ���̨���״̬
}

void GameInit()
{
	/*
	1. ��Ϸ��ʼǰ�ĳ�ʼ����������Ӧɨβ����
	2. ��ͼ������
	*/

	//���õ�ͼ
	for (int x = 0; x < MAP_X; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			//��ͼ�߽�
			if (x == 0 || x == MAP_X - 2 || x == MAP_X_WALL||	//������
				y == 0 || y == MAP_Y - 1  ||					//�����
				(x > MAP_X_WALL && y == MAP_Y / 2))				//������Ϣ����Ϸ��Ϣ�ָ���
			{
				g_MAP[x][y] = �߽�;
			}
		}
	}

	//���ع��
	SetCursorState(false);

	//��ʼ�����������
	srand((unsigned int)time(0));

	//���ű������֣���ѭ��
	PlayBGM();
}

void GotoxyFor2(int x, int y)
{
	/*
	1. �ƶ���굽ָ��λ��
	2. �������ߡ�ʳ��ϰ�������2��λ���ַ�
	*/

	COORD cur;
	cur.X = x * 2;//here�����������ٶȲ�ƥ��
	//cur.X = x;
	cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}

void Gotoxy(int x, int y)
{
	/*
	1. �ƶ���굽ָ��λ��
	2. ��������ͨ��1��λ�ַ�
	*/

	COORD cur;
	cur.X = x;
	cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}

void setColor(unsigned short ForeColor, unsigned short BackGroundColor)
{
	/*
	������ɫ
	*/

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);					//��ȡ��ǰ���ھ��
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
	errno_t err = fopen_s(&pFile, "conf\\game\\game.i", "wb");
	//д�뵱ǰ����ֵ
	fwrite(&snake.m_Blood, sizeof(int), 1, pFile);
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
	errno_t err = fopen_s(&pFile, "conf\\game\\game.i", "rb");

	//��ȡ����ֵ 
	fread(&snake.m_Blood, sizeof(int), 1, pFile);
	//��ȡ��ǰ˯��ʱ�䣬�Ա�֤�ٶ��ڶ�ȡʱҲ����
	fread(&g_SleepTime, sizeof(int), 1, pFile);
	//д���ϰ����������ߵ�����
	fread(&g_SnaCount, sizeof(int), 1, pFile);
	fread(&g_BarCount, sizeof(int), 1, pFile);
	//��ȡ�ϰ���
	COORD tmp;
	for (int i = 0; i < g_BarCount; i++)
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





int SelectAction()
{
	/*
	1. ѡ������Ϸ or ��ȡ��Ϸ or �˳���Ϸ
	*/

	int input = _getch()-48;	//�޻��Խ��գ�-48��֤��0-9������ASCII
	SetCursorState(false);	//���������ع��

	switch (input)
	{
	case ����Ϸ:
	{
		g_isRunning = true;
		break;
	}
	case ��ȡ��Ϸ:
	{
		g_isRunning = true;
		break;
	}
	case �˳���Ϸ:
	{
		Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 + 3);
		cout << "Bye! " << endl;
		break;
	}
	default:
		Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 + 3);
		cout << "�������";
		break;
	}
	return input;
}

int SelectWhoMap()
{
	/*
	1. ѡ��ϵͳ��ͼ or �û��Զ����ͼ
	*/

	//��ӡ��ʾ��Ϣ
	system("cls");				//��ҳ������
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 6);
	cout << "��ѡ���ͼ��" << endl;
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 4);
	cout << "1. ϵͳĬ��" << endl;
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 2);
	cout << "2. ����ṩ" << endl;
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2);
	cout << "������ѡ��-> ";
	SetCursorState(true);		//�û�����ǰ��ʾ���

	int input = _getch()-48;	//������0-9������ASCII
	SetCursorState(false);		//������������ع��

	return input;
}

void SelectLevel()
{
	/*
	1. ѡ��ȼ���ֻ������ϵͳ��ͼ
	2. ˯��ʱ�䡢�ϰ������������Ѷȵȼ�
	*/

	//��ӡ��ʾ��Ϣ
	system("cls");				//��ҳ������
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 6);
	cout << "��Ϸ�Ѷȣ�" << endl;
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 4);
	cout << "1. ��" << endl;
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 2);
	cout << "2. һ��" << endl;
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2);
	cout << "3. ����" << endl;
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 + 2);
	cout << "������ѡ��-> ";
	SetCursorState(true);		//��ʾ���

	int input = _getch()-48;	//����ASCII
	SetCursorState(false);		//���ع��

	//�Ѷ����ϰ������������ȡ���˯��ʱ��ɷ���
	switch (input)
	{
	case ��:
		g_LevelBarrsize = 10;
		g_SleepTime = 400;
		break;
	case һ��:
		g_LevelBarrsize = 20;
		g_SleepTime = 300;
		break;
	case ����:
		g_LevelBarrsize = 40;
		g_SleepTime = 200;
		break;
	default:
		break;
	}
}

int SelectWhenMap()
{
	/*
	1. ѡ���¾ɵ�ͼ��ֻ�������û��Զ����ͼ
	2. �½���ͼ or ֮ǰ�����ϵ�ͼ
	*/

	//��ʾ��Ϣ
	system("cls");
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 6);
	cout << "��ͼѡ��" << endl;
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 4);
	cout << "1. �½���ͼ" << endl;
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 2);
	cout << "2. ���е�ͼ" << endl;
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 );
	cout << "������ѡ��-> ";
	SetCursorState(true);//��ʾ���

	int input = _getch()-48;
	SetCursorState(false);//���ع��

	return input;
}

string SetMap()
{
	/*
	1. �û��Զ����ͼ������
	2. ʵ�����������ϰ����Ų�
	2. ��������¼�
	3. �ɶ�ά������Ϊ��Ļ���ļ����н�
	*/

	DrawMapBorder();		//���ȴ�ӡ��ͼ�߽�

	//��ʾ��Ϣ
	setColor(12, 0);
	Gotoxy(MAP_X - 20, 4);
	cout << "�༭��ͼ" << endl;
	Gotoxy(MAP_X - 24, 6);
	cout << "��������������ϰ�" << endl;
	Gotoxy(MAP_X - 24, 8);
	cout << "�Ҽ������������ϰ�" << endl;
	Gotoxy(MAP_X - 24, 10);
	cout << "����˫�����˳��༭" << endl;
	setColor(7, 0);

	//����¼����
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD ir = {};
	DWORD dwCount = 0;
	SetConsoleMode(hInput, ENABLE_MOUSE_INPUT);

	vector<COORD> BarrTmp;//�ϰ�������
	int barrTmpSize = 0;

	//��������¼�����������Ļ
	while (true)
	{
		ReadConsoleInput(hInput, &ir, 1, &dwCount);
		if (ir.EventType == MOUSE_EVENT)
		{
			if (ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;//��ȡ������λ��
				if (pos.X > 0 && pos.X < MAP_X_WALL && pos.Y >0 && pos.Y < MAP_Y)
				{

					g_BarrMAP[pos.X][pos.Y] = 1;
					GotoxyFor2(pos.X / 2, pos.Y);//����/2�������һƥ��5/2*2=4����֤��x����ռ������λ���ַ���xֻ����ż���������ܼ��ٳ����
					cout << "��";
				}
			}
			if (ir.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;
				if (pos.X > 0 && pos.X < MAP_X_WALL && pos.Y >0 && pos.Y < MAP_Y)
				{

					g_BarrMAP[pos.X][pos.Y] = 0;
					GotoxyFor2(pos.X / 2, pos.Y);
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

	//����Ļ״̬�����ά����
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
				COORD tmp = { t / 2,j };//����Ϊ��ӡ��ʱ��Ҫ*2�����ٳ���
				BarrTmp.push_back(tmp);
				barrTmpSize++;
			}
		}
	}

	//��ʾ��Ϣ

	string str;
	system("cls");
	setColor(12, 0);
	Gotoxy(MAP_X - 24, 12);
	cout << "�������ͼ����" << endl;
	Gotoxy(MAP_X - 24, 14);
	cin >> str;
	setColor(7, 0);

	string str1 = str + ".i";
	string str2 = "conf\\map\\" + str1;
	const char* filename = str2.c_str();




	//�����������Ϣд���ļ�
	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, filename, "wb");
	//errno_t err = fopen_s(&pFile, "conf\\map.i", "wb");
	fwrite(&barrTmpSize, sizeof(int), 1, pFile);//д���ϰ�������
	for (int i = 0; i < BarrTmp.size(); i++)	//����д���ϰ���
	{
		fwrite(&BarrTmp[i], sizeof(COORD), 1, pFile);
	}
	fclose(pFile);

	return str1;
}

void LoadMap(CBarrier& barrier,string str)
{
	/*
	1. �����û��Զ���ĵ�ͼ
	2. ������Ϊ�ϰ������
	*/
	str = "conf\\map\\" + str;
	const char* filename = str.c_str();//here


	COORD tmp;
	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, filename, "rb");//here
	//errno_t err = fopen_s(&pFile, "conf\\map.i", "rb");
	fread(&barrier.m_size, sizeof(int), 1, pFile);	//��ȡ�ϰ�������
	for (int i = 0; i < barrier.m_size; i++)		//������ȡ�ϰ���
	{
		fread(&tmp, sizeof(COORD), 1, pFile);
		barrier.m_BarrArr.push_back(tmp);			//����tmp����������ֱ�Ӷ���
	}
	fclose(pFile);
}

//here
string ShowMaps()
{
	//Ŀ���ļ���·��
	std::string inPath = "conf/map/*.i";//�����ļ����µ�����.jpg�ļ�
	//���ڲ��ҵľ��
	long handle;
	_finddata_t fileinfo;
	//��һ�β���
	handle = _findfirst(inPath.c_str(), &fileinfo);
	if (handle == -1)
		return 0;
	do
	{
		g_Maps.push_back(fileinfo.name);
		//�ҵ����ļ����ļ���
		//cout << fileinfo.name;
		//printf("%s\n", fileinfo.name);

	} while (!_findnext(handle, &fileinfo));

	_findclose(handle);


	system("cls");
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 8);
	cout << "��ѡ���ͼ" << endl;

	int i = 0;
	for (; i < g_Maps.size(); i++)
	{
		//��ʾ��Ϣ
		Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 6 + i);
		cout << i + 1 << ". " << g_Maps[i] << endl;
		//printf("%d. %s\n", i+1, g_MAP[i]);
		//cout << g_Maps[i].substr() << endl;
	}
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 6 + i);
	cout << "������ѡ��-> ";

	int input = _getch() - 48;

	return g_Maps[input - 1];

}



void PlayBGM()
{
	/*
	1. ���ű������֣���ѭ��)
	2. ����Ϸ���ţ�������ֹͣ
	3. ��ͣʱֹͣ���ָ�ʱ����
	*/

	// ����Ƶ�ļ�������ʱ�ر�
	mciSendString("open conf/BGM.mp3 alias bgm", NULL, 0, NULL);//�������ɴ�д
	mciSendString("play bgm repeat", NULL, 0, NULL);			// ѭ������,������.mp3��ʽ
}
