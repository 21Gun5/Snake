#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "data.h"
#include "func.h"

int dir[4][2] = { { 0,1 },{ 0,-1 },{ 1,0 },{ -1,0 } };
int g_speed = 200;//���sleepʹ�ã�Խ��Խ��
int g_window_width = 80;
int g_window_height = 40;