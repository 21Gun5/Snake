#pragma once

//�궨��
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define HEAD 0

//ȫ�ֱ���
extern int dir[4][2];
extern int g_speed;//���sleepʹ�ã�Խ��Խ��

//ȫ�ֺ���
void gotoxy(int x, int y);//�ƶ���굽ָ��λ��
void setColor(unsigned short ForeColor = 7, unsigned short BackGroundColor = 0);//������ɫ

//����ṹ�壨�Զ���ģ�ϵͳ�ṩ����COORD
typedef struct _POS
{
	int x;
	int y;
}POS,PPOS;

//������
class CSetting
{
public:
	//���ڴ�С
	static const int window_height = 40;
	static const int window_width = 80;
public:
	//static��Ա����������ֱ�ӵ���
	static void GameInit();
};