#pragma once
#include "food.h"
#include "snake.h"
#include "barrier.h"
#pragma comment(lib,"winmm.lib")//����BGM

void DrawWelcome();				//��ӭ����
void DrawMap();					//��ӡ��ͼ�߽�
void GameOver(int score);		//��Ϸ����
void DrawGameInfo(int score,int barrSize);		//��ӡ����
void DrawGameHelp();			//��ӡ����˵��
void GameInit();				//��ʼ����Ϸ
void gotoxy(int x, int y);		//�ƶ���꣨��ͼ�߽硢������Ϣ�õ���
void setColor(unsigned short ForeColor, unsigned short BackGroundColor);//������ɫ

void gotoxy4s(int x, int y);//�ƶ����꣨�ߡ�ʳ��ϰ����õ���

void SetLevel();//������Ϸ�Ѷȵȼ�

int HandleSelect();//�����û�����

void SaveGame(CSnake& snake, CBarrier& barrier, CFood& food);//�浵

void LoadGame(CSnake& snake, CBarrier& barrier, CFood& food);//����

//void PlayGame(CSnake& snake, CBarrier& barrier, CFood& food);

