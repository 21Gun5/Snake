#pragma once

//宏定义
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define HEAD 0

//全局变量
extern int dir[4][2];
extern int g_speed;			//结合sleep使用，越大越慢
extern int g_window_width;	//窗口宽度
extern int g_window_height;	//窗口高度

//坐标结构体（自定义的，系统提供的是COORD
typedef struct _POS
{
	int x;
	int y;
}POS,PPOS;
