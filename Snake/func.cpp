#include <iostream>
#include <windows.h>
#include <time.h>
#include "data.h"
#include "func.h"
using namespace std;

//��ӭ����
void DrawWelcome()
{
	cout << "Welcome!";
}

//��ӡ��ͼ�߽�
void DrawMap()
{
	system("cls");
	int i, j;
	for (i = 0; i < g_window_width; i++)
		cout << "#";
	cout << endl;
	for (i = 0; i < g_window_height - 2; i++)
	{
		for (j = 0; j < g_window_width; j++)
		{
			if (i == 13 && j >= g_window_width - 29)
			{
				cout << "#";
				continue;
			}

			if (j == 0 || j == g_window_width - 29 || j == g_window_width - 1)
			{
				cout << "#";
			}
			else
				cout << " ";

		}
		cout << endl;
	}
	for (i = 0; i < g_window_width; i++)
		cout << "#";

}

//��Ϸ����
void GameOver(int score)
{
	setColor(12, 0);
	gotoxy(g_window_width / 2 - 20, g_window_height / 2 - 5);
	cout << "GAME OVER! " << endl;;
	gotoxy(g_window_width / 2 - 20, g_window_height / 2 - 3);
	cout << "Scores: " << score << endl;
}

//��ӡ����
void DrawScore(int score)
{
	gotoxy(g_window_width - 22 + 14, 6);
	cout << "  ";
	gotoxy(g_window_width - 22 + 14, 4);
	cout << "  ";

	gotoxy(g_window_width - 22, 6);
	cout << "��ǰ����: " << score << endl;

}

//��ӡ����˵��
void DrawGameInfo()
{
	gotoxy(g_window_width - 22, 18);
	cout << "����˵����" << endl;
	gotoxy(g_window_width - 22, 20);
	cout << "W: ��    S: ��" << endl;
	gotoxy(g_window_width - 22, 22);
	cout << "A: ��    D: ��" << endl;
}

void GameInit()
{
	//������Ϸ���ڴ�Сhere
	char buffer[32];
	sprintf_s(buffer, "mode con cols=%d lines=%d", g_window_width, g_window_height);
	system(buffer);
	//system("mode con cols = 80 lines = 40");

	//���ع��here
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = false; //���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬

	//��ʼ�����������
	srand((unsigned int)time(0));
}

//�ƶ���굽ָ��λ��
void gotoxy(int x, int y)
{
	COORD cur;//ϵͳ�ṩ������ṹ��
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