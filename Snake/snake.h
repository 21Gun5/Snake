#pragma once
#include "food.h"

//贪吃蛇类
class CSnake
{
public:
	vector<COORD> m_SnakeBody;	//存储蛇身的动态数组
	int m_Dir;					//运动方向
	bool m_IsAlive;				//是否存活

	CSnake();//构造函数
	void ListenKeyBoard();//监听键盘
	void MoveSnake();//移动贪吃蛇
	bool IsEatenFood(CFood& food, vector<COORD>& barArr);//是否吃到食物
	bool IsAlive(vector<COORD>& barArr);//判断生死
	void DrawSanke();//画蛇
	void ClearSnake();//清除蛇尾
	int GetSnakeSize();//获取蛇长
};