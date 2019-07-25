#pragma once
#include <string>
#include "food.h"
#include "snake.h"
#include "barrier.h"
using std::string;
#pragma comment(lib,"winmm.lib")//播放BGM

void DrawWelcome();				//欢迎界面
void DrawMapBorder();					//打印地图边界
void GameOver(int score);		//游戏结束
void DrawGameInfo(int score,int barrSize,int blood);		//打印分数
void DrawGameHelp();			//打印操作说明
void GameInit();				//初始化游戏
void Gotoxy(int x, int y);		//移动光标（地图边界、其他信息用到）
void setColor(unsigned short ForeColor, unsigned short BackGroundColor);//设置颜色

void GotoxyFor2(int x, int y);//移动坐标（蛇、食物、障碍物用到）

//void SetLevel();//设置游戏难度等级

int SelectAction();//处理用户输入（新游戏or退出游戏……

int SelectWhoMap();//处理用户输入（选择系统系统or自定义地图

void SelectLevel();//处理用户输入（选择难度

void SaveGame(CSnake& snake, CBarrier& barrier, CFood& food);//存档

void LoadGame(CSnake& snake, CBarrier& barrier, CFood& food);//读档

string SetMap();//自定义地图

void LoadMap(CBarrier& barrier,string str);

void PlayBGM();
//void PlayGame(CSnake& snake, CBarrier& barrier, CFood& food);
int  SelectWhenMap();

void SetCursorState(bool b);

//void HandleSelect(CSnake* psnake, CBarrier* pbarrier, CFood* pfood);

//vector<COORD> CustomizeMap();

string ShowMaps();//here