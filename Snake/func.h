#pragma once

void DrawWelcome();				//欢迎界面
void DrawMap();					//打印地图边界
void GameOver(int score);		//游戏结束
void DrawScore(int score);		//打印分数
void DrawGameInfo();			//打印操作说明
void GameInit();				//初始化游戏
void gotoxy(int x, int y);		//移动光标
void setColor(unsigned short ForeColor, unsigned short BackGroundColor);//设置颜色