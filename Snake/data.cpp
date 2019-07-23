#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "data.h"
#include "func.h"

int dir[4][2] = { { 0,1 },{ 0,-1 },{ 1,0 },{ -1,0 } };
int g_speed = 200;		//结合sleep使用，越大越慢
//int g_window_width = 80;
//int g_window_height = 40;
int g_MAP[MAP_X][MAP_Y];//存储地图边界
int g_BarrMAP[MAP_X_WALL][MAP_Y] = {0};//存储障碍物
bool g_isRunning = false;
int g_SnaCount;
int g_BarCount;
