#pragma once
#include "food.h"
#include "barrier.h"

//̰������
class CSnake
{
public:
	vector<COORD> m_SnakeBody;	//�洢����Ķ�̬����
	COORD m_SnakeTail;			//��β����ȡʱ����β�������Σ�Ҫ��һ������
	int m_Dir;					//�˶�����
	bool m_IsAlive;				//�Ƿ���
	int m_Blood;//Ĭ��������

	CSnake();//���캯��
	CSnake(int dir);
	void ListenKeyBoard(CSnake& snake, CBarrier& barrier, CFood& food);//��������
	void MoveSnake(CSnake& snake, CBarrier& barrier, CFood& food);//�ƶ�̰����
	bool IsEatenFood(CFood& food, vector<COORD>& barArr);//�Ƿ�Ե�ʳ��
	bool IsAlive(vector<COORD>& barArr);//�ж�����
	void DrawSanke();//����
	void ClearSnakeTail();//�����β
	int GetSnakeSize();//��ȡ�߳�
};