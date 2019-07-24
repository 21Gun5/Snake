#pragma once
#include "food.h"
#include "barrier.h"

//贪吃蛇类
class CSnake
{
public:
	vector<COORD> m_SnakeBody;	//存储蛇身的动态数组
	COORD m_SnakeTail;			//蛇尾，读取时，蛇尾少了两次，要加一个补上
	int m_Dir;					//运动方向
	bool m_IsAlive;				//是否存活
	int m_Blood;//默认三条命

	CSnake();//构造函数
	CSnake(int dir);
	void ListenKeyBoard(CSnake& snake, CBarrier& barrier, CFood& food);//监听键盘
	void MoveSnake(CSnake& snake, CBarrier& barrier, CFood& food);//移动贪吃蛇
	bool IsEatenFood(CFood& food, vector<COORD>& barArr);//是否吃到食物
	bool IsAlive(vector<COORD>& barArr);//判断生死
	void DrawSanke();//画蛇
	void ClearSnakeTail();//清除蛇尾
	int GetSnakeSize();//获取蛇长
};