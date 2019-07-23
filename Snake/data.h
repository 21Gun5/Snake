#pragma once

//宏定义
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define HEAD 0//蛇身数组0位置便是蛇头
#define MAP_X 90//x一个字符，y方向2个字符，故2倍，若两字节字符，则同(90=60+30)
#define MAP_Y 30
#define MAP_X_WALL 60
#define 空地 0
#define 食物 1
#define 边界 2
#define 蛇 3

//全局变量
extern int dir[4][2];
extern int g_speed;			//结合sleep使用，越大越慢
extern int g_barrQuantity;//障碍物数量
extern int g_level;//游戏等级
extern int g_snaLen;//蛇的长度
extern bool g_isRunning;//游戏是否运行
extern int g_SnaCount;
extern int g_BarCount;

//extern bool g_isRunning;//是否暂停
//extern int g_window_width;	//窗口宽度
//extern int g_window_height;	//窗口高度

extern int g_MAP[MAP_X][MAP_Y];
extern int g_BarrMAP[MAP_X_WALL][MAP_Y];

//坐标结构体（自定义的，系统提供的是COORD
//typedef struct _POS
//{
//	int x;
//	int y;
//}POS,PPOS;
