#pragma once
#include "food.h"
#include "barrier.h"

class CSnake
{
public:
	vector<COORD> m_SnakeBody;	//存储蛇身的动态数组
	COORD m_SnakeTail;			//蛇尾，读取时，蛇尾少了两次，要加一个补上
	int m_Dir;					//运动方向
	bool m_IsAlive;				//是否存活
	int m_Blood;				//默认三条命

	CSnake();					//读取文件时需构造空对象
	CSnake(int dir);			//有参构造，设置初始方向
	int GetSnakeSize();			//获取蛇长
	void ClearSnakeTail();		//清除蛇尾
	void DrawSanke();			//画蛇
	bool IsAlive(vector<COORD>& barArr);								//判断生死
	bool IsEatenFood(CFood& food, vector<COORD>& barArr);				//是否吃到食物
	void MoveSnake(CSnake& snake, CBarrier& barrier, CFood& food);		//移动蛇
	void ListenKeyBoard(CSnake& snake, CBarrier& barrier, CFood& food);	//监听键盘	
};