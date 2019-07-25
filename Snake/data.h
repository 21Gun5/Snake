#pragma once
#include <string>
#include <vector>
using namespace std;

//�궨��
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define HEAD 0			//��ͷ

#define MAP_X 90		//�ұ߽�
#define MAP_Y 30		//�±߽�
#define MAP_X_WALL 60	//��Ϸ��������Ϣ����ָ���

#define �߽� 1			//����Ƿ�Ϊ�߽�

#define ����Ϸ 1
#define ��ȡ��Ϸ 2
#define �˳���Ϸ 3

#define ϵͳĬ�� 1
#define �Զ��� 2

#define �� 1
#define һ�� 2
#define ���� 3

#define �½���ͼ 1
#define ���е�ͼ 2

//ȫ�ֱ���
extern int g_Speed;						//�ٶȣ�g_Speed = 5 + (300 - g_SleepTime) / 25��һ���ٶȼ���Ӧ25��ʱ�伶
extern int g_SleepTime;					//��ӿ����ٶȣ�25Ϊ��λ��200-1��300-5��400-9��
extern bool g_isRunning;				//��Ϸ�Ƿ����е�״̬

extern int g_SnaCount;					//���������������ȡ��Ϸ��
extern int g_BarCount;					//�ϰ������������ȡ��Ϸ��
extern int g_LevelBarrsize;				//�ϰ�������ѡ���Ѷ�ʱ��
extern int g_foodCount;					//���˶���ʳ������ٶ�������ֵ��

extern vector<string> g_Maps;			//�洢��ͼ�ļ�
extern vector<string> g_Games;			//�洢��Ϸ�ļ�

extern int g_MAP[MAP_X][MAP_Y];			//�洢��ͼ�߽�
extern int g_BarrMAP[MAP_X_WALL][MAP_Y];//�洢�ϰ���