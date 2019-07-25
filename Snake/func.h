#pragma once
#include <string>
#include "food.h"
#include "snake.h"
#include "barrier.h"
using std::string;
#pragma comment(lib,"winmm.lib")//����BGM

void DrawWelcome();				//��ӭ����
void DrawMapBorder();					//��ӡ��ͼ�߽�
void GameOver(int score);		//��Ϸ����
void DrawGameInfo(int score,int barrSize,int blood);		//��ӡ����
void DrawGameHelp();			//��ӡ����˵��
void GameInit();				//��ʼ����Ϸ
void Gotoxy(int x, int y);		//�ƶ���꣨��ͼ�߽硢������Ϣ�õ���
void setColor(unsigned short ForeColor, unsigned short BackGroundColor);//������ɫ

void GotoxyFor2(int x, int y);//�ƶ����꣨�ߡ�ʳ��ϰ����õ���

//void SetLevel();//������Ϸ�Ѷȵȼ�

int SelectAction();//�����û����루����Ϸor�˳���Ϸ����

int SelectWhoMap();//�����û����루ѡ��ϵͳϵͳor�Զ����ͼ

void SelectLevel();//�����û����루ѡ���Ѷ�

void SaveGame(CSnake& snake, CBarrier& barrier, CFood& food);//�浵

void LoadGame(CSnake& snake, CBarrier& barrier, CFood& food);//����

string SetMap();//�Զ����ͼ

void LoadMap(CBarrier& barrier,string str);

void PlayBGM();
//void PlayGame(CSnake& snake, CBarrier& barrier, CFood& food);
int  SelectWhenMap();

void SetCursorState(bool b);

//void HandleSelect(CSnake* psnake, CBarrier* pbarrier, CFood* pfood);

//vector<COORD> CustomizeMap();

string ShowMaps();//here