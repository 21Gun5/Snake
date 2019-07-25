#pragma once
#include "food.h"
#include "barrier.h"

class CSnake
{
public:
	vector<COORD> m_SnakeBody;	//�洢����Ķ�̬����
	COORD m_SnakeTail;			//��β����ȡʱ����β�������Σ�Ҫ��һ������
	int m_Dir;					//�˶�����
	bool m_IsAlive;				//�Ƿ���
	int m_Blood;				//Ĭ��������

	CSnake();					//��ȡ�ļ�ʱ�蹹��ն���
	CSnake(int dir);			//�вι��죬���ó�ʼ����
	int GetSnakeSize();			//��ȡ�߳�
	void ClearSnakeTail();		//�����β
	void DrawSanke();			//����
	bool IsAlive(vector<COORD>& barArr);								//�ж�����
	bool IsEatenFood(CFood& food, vector<COORD>& barArr);				//�Ƿ�Ե�ʳ��
	void MoveSnake(CSnake& snake, CBarrier& barrier, CFood& food);		//�ƶ���
	void ListenKeyBoard(CSnake& snake, CBarrier& barrier, CFood& food);	//��������	
};