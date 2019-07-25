#pragma once
#include <string>
#include <vector>
using namespace std;

//宏定义
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define HEAD 0			//蛇头

#define MAP_X 90		//右边界
#define MAP_Y 30		//下边界
#define MAP_X_WALL 60	//游戏界面与信息界面分割线

#define 边界 1			//标记是否为边界

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
extern int g_Speed;						//速度，g_Speed = 5 + (300 - g_SleepTime) / 25，一个速度级对应25个时间级
extern int g_SleepTime;					//间接控制速度，25为单位：200-1、300-5、400-9）
extern bool g_isRunning;				//游戏是否运行的状态

extern int g_SnaCount;					//蛇身数量，保存读取游戏用
extern int g_BarCount;					//障碍数量，保存读取游戏用
extern int g_LevelBarrsize;				//障碍数量，选择难度时用
extern int g_foodCount;					//吃了多少食物，计算速度与生命值用

extern vector<string> g_Maps;			//存储地图文件
extern vector<string> g_Games;			//存储游戏文件

extern int g_MAP[MAP_X][MAP_Y];			//存储地图边界
extern int g_BarrMAP[MAP_X_WALL][MAP_Y];//存储障碍物