#pragma once

//宏定义
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define HEAD 0

//全局变量
extern int dir[4][2];
extern int g_speed;//结合sleep使用，越大越慢

//全局函数
void gotoxy(int x, int y);//移动光标到指定位置
void setColor(unsigned short ForeColor = 7, unsigned short BackGroundColor = 0);//设置颜色

//坐标结构体（自定义的，系统提供的是COORD
typedef struct _POS
{
	int x;
	int y;
}POS,PPOS;

//设置类
class CSetting
{
public:
	//窗口大小
	static const int window_height = 40;
	static const int window_width = 80;
public:
	//static成员，可由类名直接调用
	static void GameInit();
};