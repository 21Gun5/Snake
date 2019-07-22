#pragma once
#include "food.h"
#include "snake.h"
#include "barrier.h"
#pragma comment(lib,"winmm.lib")//播放BGM

void DrawWelcome();				//欢迎界面
void DrawMap();					//打印地图边界
void GameOver(int score);		//游戏结束
void DrawGameInfo(int score,int barrSize);		//打印分数
void DrawGameHelp();			//打印操作说明
void GameInit();				//初始化游戏
void gotoxy(int x, int y);		//移动光标（地图边界、其他信息用到）
void setColor(unsigned short ForeColor, unsigned short BackGroundColor);//设置颜色

void gotoxy4s(int x, int y);//移动坐标（蛇、食物、障碍物用到）

void SetLevel();//设置游戏难度等级

int HandleSelect();//处理用户输入

void SaveGame(CSnake& snake, CBarrier& barrier, CFood& food);//存档

void LoadGame(CSnake& snake, CBarrier& barrier, CFood& food);//读档

//void PlayGame(CSnake& snake, CBarrier& barrier, CFood& food);

