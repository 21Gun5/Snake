#pragma once

//�궨��
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define HEAD 0

//ȫ�ֱ���
extern int dir[4][2];
extern int g_speed;			//���sleepʹ�ã�Խ��Խ��
extern int g_window_width;	//���ڿ��
extern int g_window_height;	//���ڸ߶�

//����ṹ�壨�Զ���ģ�ϵͳ�ṩ����COORD
typedef struct _POS
{
	int x;
	int y;
}POS,PPOS;
