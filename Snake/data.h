#pragma once
#include <string>
#include <vector>
using namespace std;

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
#define �߽� 2
#define �� 3

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
extern int dir[4][2];
extern int g_Speed;//�ٶȣ�������ʾ�ã�g_Speed = 5 + (300 - g_SleepTime) / 25;
extern int g_SleepTime;//��ӿ����ٶȣ�+-����Ӧ-+����ʳ��-�����û�+-�����߳�ʳ �� �ٶȵ��м���
extern int g_barrQuantity;//�ϰ�������
extern int g_level;//��Ϸ�ȼ�
extern int g_snaLen;//�ߵĳ���
extern bool g_isRunning;//��Ϸ�Ƿ�����
extern int g_SnaCount;//���������������ȡ��Ϸ��
extern int g_BarCount;//�ϰ��������������ȡ��Ϸ��

extern int g_foodCount;//�Ե��˶���ʳ��Ե�Խ���ٶ�Խ��
extern int g_LevelBarrsize;//�ϰ���������ѡ���Ѷ�ʱ��;

//extern bool g_isRunning;//�Ƿ���ͣ
//extern int g_window_width;	//���ڿ��
//extern int g_window_height;	//���ڸ߶�

extern int g_MAP[MAP_X][MAP_Y];
extern int g_BarrMAP[MAP_X_WALL][MAP_Y];

extern vector<string> g_Maps;

//����ṹ�壨�Զ���ģ�ϵͳ�ṩ����COORD
//typedef struct _POS
//{
//	int x;
//	int y;
//}POS,PPOS;
