#pragma once
#include "food.h"

//̰������
class CSnake
{
public:
	vector<COORD> m_SnakeBody;	//�洢����Ķ�̬����
	int m_Dir;					//�˶�����
	bool m_IsAlive;				//�Ƿ���

	CSnake();//���캯��
	void ListenKeyBoard();//��������
	void MoveSnake();//�ƶ�̰����
	bool IsEatenFood(CFood& food, vector<COORD>& barArr);//�Ƿ�Ե�ʳ��
	bool IsAlive(vector<COORD>& barArr);//�ж�����
	void DrawSanke();//����
	void ClearSnake();//�����β
	int GetSnakeSize();//��ȡ�߳�
};