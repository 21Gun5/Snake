#pragma once
#include <string>
#include <vector>
#include "food.h"
#include "snake.h"
#include "barrier.h"
#pragma comment(lib,"winmm.lib")
using namespace std;

void DrawWelcome();				//��ӭ����
void DrawMapBorder();			//��ͼ�߽�
void DrawGameHelp();			//����˵��
void DrawGameInfo(int score, int barrSize, int blood);	//��������ֵ��

void GameInit();				//��Ϸ��ʼǰ�ĳ�ʼ��
void GameOver(int score);		//��Ϸ�������ɨβ����

void Gotoxy(int x, int y);		//�ƶ���꣨��ͨһ��λ�ַ���
void GotoxyFor2(int x, int y);	//�ƶ����꣨�ߵ�����λ�ַ���
void SetCursorState(bool b);	//���ù��״̬
void PlayBGM();					//���ű�������
void setColor(unsigned short ForeColor, unsigned short BackGroundColor);//������ɫ

int SelectAction();				//��/��ȡ/�˳���Ϸ
int SelectWhoMap();				//ϵͳ/�Զ����ͼ
int SelectWhenMap();			//�½�/���е�ͼ
void SelectLevel();				//������Ϸ�Ѷ�

string SetMap();				//�Զ����ͼ
string ShowMaps();				//��ʾ��ͼ���û�ѡ��
void LoadMap(CBarrier& barrier, string str);//�����ͼ

string ShowGames();				//��ʾ�浵���û�ѡ��
void SaveGame(CSnake& snake, CBarrier& barrier, CFood& food);//�浵
void LoadGame(CSnake& snake, CBarrier& barrier, CFood& food, string str);//����
