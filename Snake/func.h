#pragma once
#include <string>
#include <vector>
#include "food.h"
#include "snake.h"
#include "barrier.h"
#pragma comment(lib,"winmm.lib")
using namespace std;

void DrawWelcome();				//欢迎界面
void DrawMapBorder();			//地图边界
void DrawGameHelp();			//操作说明
void DrawGameInfo(int score, int barrSize, int blood);	//分数生命值等

void GameInit();				//游戏开始前的初始化
void GameOver(int score);		//游戏结束后的扫尾工作

void Gotoxy(int x, int y);		//移动光标（普通一单位字符）
void GotoxyFor2(int x, int y);	//移动坐标（蛇等两单位字符）
void SetCursorState(bool b);	//设置光标状态
void PlayBGM();					//播放背景音乐
void setColor(unsigned short ForeColor, unsigned short BackGroundColor);//设置颜色

int SelectAction();				//新/读取/退出游戏
int SelectWhoMap();				//系统/自定义地图
int SelectWhenMap();			//新建/已有地图
void SelectLevel();				//设置游戏难度

string SetMap();				//自定义地图
string ShowMaps();				//显示地图供用户选择
void LoadMap(CBarrier& barrier, string str);//导入地图

string ShowGames();				//显示存档供用户选择
void SaveGame(CSnake& snake, CBarrier& barrier, CFood& food);//存档
void LoadGame(CSnake& snake, CBarrier& barrier, CFood& food, string str);//读档
