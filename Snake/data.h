#pragma once

//�궨��
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define HEAD 0//��������0λ�ñ�����ͷ

#define MAP_X 90//xһ���ַ���y����2���ַ�����2���������ֽ��ַ�����ͬ(90=60+30)
#define MAP_Y 30
#define MAP_X_WALL 60
#define �յ� 0
#define ʳ�� 1
#define �ϰ� 2
#define �� 3

//ȫ�ֱ���
extern int dir[4][2];
extern int g_speed;			//���sleepʹ�ã�Խ��Խ��
//extern int g_window_width;	//���ڿ��
//extern int g_window_height;	//���ڸ߶�

extern int g_MAP[MAP_X][MAP_Y];

//����ṹ�壨�Զ���ģ�ϵͳ�ṩ����COORD
typedef struct _POS
{
	int x;
	int y;
}POS,PPOS;
