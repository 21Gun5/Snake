#pragma once
#include <string>
#include <vector>
using namespace std;

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

#define 新游戏 1
#define 读取游戏 2
#define 退出游戏 3

#define 系统默认 1
#define 自定义 2

#define 简单 1
#define 一般 2
#define 困难 3

#define 新建地图 1
#define 已有地图 2

//全局变量
extern int dir[4][2];
extern int g_Speed;//速度，仅作显示用，g_Speed = 5 + (300 - g_SleepTime) / 25;
extern int g_SleepTime;//间接控制速度，+-键相应-+，吃食物-（是用户+-键、蛇吃食 与 速度的中间者
extern int g_barrQuantity;//障碍物数量
extern int g_level;//游戏等级
extern int g_snaLen;//蛇的长度
extern bool g_isRunning;//游戏是否运行
extern int g_SnaCount;//蛇身数量，保存读取游戏用
extern int g_BarCount;//障碍物数量，保存读取游戏用

extern int g_foodCount;//吃到了多少食物，吃的越多速度越快
extern int g_LevelBarrsize;//障碍物数量，选择难度时用;

//extern bool g_isRunning;//是否暂停
//extern int g_window_width;	//窗口宽度
//extern int g_window_height;	//窗口高度

extern int g_MAP[MAP_X][MAP_Y];
extern int g_BarrMAP[MAP_X_WALL][MAP_Y];

extern vector<string> g_Maps;

//坐标结构体（自定义的，系统提供的是COORD
//typedef struct _POS
//{
//	int x;
//	int y;
//}POS,PPOS;
