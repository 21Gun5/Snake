#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "setting.h"

int dir[4][2] = { { 0,1 },{ 0,-1 },{ 1,0 },{ -1,0 } };
int g_speed = 100;//���sleepʹ�ã�Խ��Խ��

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

void CSetting::GameInit()
{
	//������Ϸ���ڴ�Сhere
	char buffer[32];
	sprintf_s(buffer, "mode con cols=%d lines=%d", window_width, window_height);
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