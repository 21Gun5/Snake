#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "data.h"
#include "func.h"

int dir[4][2] = { { 0,1 },{ 0,-1 },{ 1,0 },{ -1,0 } };
int g_SleepTime = 300;		//���sleepʹ�ã�Խ��Խ����200-400��25Ϊ��λ��200-1��300-5��400-9��
int g_Speed= 5;//һ���ٶȼ���Ӧ25��ʱ�伶����ʼΪ5����1-9��300-200=100��100/25=4��5+4=9��400-300=100��100/25=4��5-4=1��
//int g_window_width = 80;
//int g_window_height = 40;
int g_MAP[MAP_X][MAP_Y];//�洢��ͼ�߽�
int g_BarrMAP[MAP_X_WALL][MAP_Y] = {0};//�洢�ϰ���
bool g_isRunning = false;
int g_SnaCount;
int g_BarCount;

int g_foodCount = 0;
int g_LevelBarrsize = 0;
