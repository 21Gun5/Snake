#include <iostream>
#include "drawSth.h"
#include "setting.h"
using namespace std;

//��ӭ����
void DrawWelcome()
{
	cout << "Welcome!";
}

//��ӡ��ͼ�߽�
void DrawMap()
{
	system("cls");
	int i, j;
	for (i = 0; i < CSetting::window_width; i++)
		cout << "#";
	cout << endl;
	for (i = 0; i < CSetting::window_height - 2; i++)
	{
		for (j = 0; j < CSetting::window_width; j++)
		{
			if (i == 13 && j >= CSetting::window_width - 29)
			{
				cout << "#";
				continue;
			}

			if (j == 0 || j == CSetting::window_width - 29 || j == CSetting::window_width - 1)
			{
				cout << "#";
			}
			else
				cout << " ";

		}
		cout << endl;
	}
	for (i = 0; i < CSetting::window_width; i++)
		cout << "#";

}

//��Ϸ����
void GameOver(int score)
{
	setColor(12, 0);
	gotoxy(CSetting::window_width / 2 - 20, CSetting::window_height / 2 - 5);
	cout << "GAME OVER! " << endl;;
	gotoxy(CSetting::window_width / 2 - 20, CSetting::window_height / 2 - 3);
	cout << "Scores: " << score << endl;
}

//��ӡ����
void DrawScore(int score)
{
	gotoxy(CSetting::window_width - 22 + 14, 6);
	cout << "  ";
	gotoxy(CSetting::window_width - 22 + 14, 4);
	cout << "  ";

	gotoxy(CSetting::window_width - 22, 6);
	cout << "��ǰ����: " << score << endl;

}

//��ӡ����˵��
void DrawGameInfo()
{
	gotoxy(CSetting::window_width - 22, 18);
	cout << "����˵����" << endl;
	gotoxy(CSetting::window_width - 22, 20);
	cout << "W: ��    S: ��" << endl;
	gotoxy(CSetting::window_width - 22, 22);
	cout << "A: ��    D: ��" << endl;
}

