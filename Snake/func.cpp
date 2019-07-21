#include <iostream>
#include <windows.h>
#include <time.h>
#include "data.h"
#include "func.h"
#include <conio.h>

using namespace std;

//��ӡ��ӭ����
void DrawWelcome()
{
	cout << "Welcome!" << endl;
}

//��ӡ��ͼ�߽�
void DrawMap()
{
	system("cls");//������
	//�ϱ߽�
	for (int i = 0; i < g_window_width; i++)
		cout << "#";
	cout << endl;
	//�����߽�here
	for (int i = 0; i < g_window_height - 2; i++)
	{
		for (int j = 0; j < g_window_width; j++)
		{
			if (i == 13 && j >= g_window_width - 29)
			{
				cout << "#";
				continue;
			}
			if (j == 0 || j == g_window_width - 29 || j == g_window_width - 1)
			{
				cout << "#";
			}
			else
				cout << " ";
		}
		cout << endl;
	}
	//�±߽�
	for (int i = 0; i < g_window_width; i++)
		cout << "#";
}

//��Ϸ����
void GameOver(int score)
{
	setColor(12, 0);

	gotoxy(g_window_width / 2 - 20, g_window_height / 2 - 5);
	cout << "GAME OVER! " << endl;

	gotoxy(g_window_width / 2 - 20, g_window_height / 2 - 3);
	cout << "Scores: " << score - 3 << endl;
}

//��ӡ����
void DrawScore(int score)
{
	gotoxy(g_window_width - 22 + 14, 6);
	cout << "  ";
	gotoxy(g_window_width - 22 + 14, 4);
	cout << "  ";
	gotoxy(g_window_width - 22, 6);
	cout << "��ǰ����: " << score - 3 << endl;//-3��ԭʼ�߳�Ϊ3
}

//��ӡ����˵��
void DrawGameInfo()
{
	gotoxy(g_window_width - 22, 18);
	cout << "����˵����" << endl;
	gotoxy(g_window_width - 22, 20);
	cout << "W: ��    S: ��" << endl;
	gotoxy(g_window_width - 22, 22);
	cout << "A: ��    D: ��" << endl;
}

//��ʼ������
void GameInit()
{
	//���ô��ڴ�Сhere
	char buf[32];
	sprintf_s(buf, "mode con cols=%d lines=%d", g_window_width, g_window_height);
	system(buf);

	//���ع��
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);	//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = false;				//���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);	//���ÿ���̨���״̬

	//��ʼ�����������
	srand((unsigned int)time(0));
}

//�ƶ����
void gotoxy4s(int x, int y)
{
	COORD cur;//ϵͳ�ṩ������ṹ��
	cur.X = x*2;//here�����������ٶȲ�ƥ��
	//cur.X = x;
	cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}

//�ƶ����
void gotoxy(int x, int y)
{
	COORD cur;//ϵͳ�ṩ������ṹ��
	//cur.X = x*2;//here�����������ٶȲ�ƥ��
	cur.X = x;
	cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}

//������ɫ
void setColor(unsigned short ForeColor, unsigned short BackGroundColor)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ��ǰ���ھ��
	SetConsoleTextAttribute(handle, ForeColor + BackGroundColor * 0x10);//������ɫ
}

////////////////////////////////////////////////

//1. ����Ļ�κ�λ������ַ���
void WriteChar(int x, int y, const char* p, int color = 0)
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ��׼����������������Ļ
	COORD pos = { x, y };//����ṹ��
	SetConsoleCursorPosition(hOutput, pos);//������ƶ��� ��Ļ��ָ������λ��
	printf(p);//��ָ��λ�ô�ӡ
}

// 2. �ܿ��Ƶ������ƶ��ĵ�
void moveSth()
{
	//��겻�ɼ�
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ��Ļ��������������Ϊָ��ĳ�����ָ�룬�˾���ʹ���ĳ����
	CONSOLE_CURSOR_INFO cci;//����̨������
	cci.dwSize = sizeof(cci);//����С���������ã�
	cci.bVisible = FALSE;//���ù��״̬Ϊ���ɼ�
	SetConsoleCursorInfo(hOutput, &cci);//�����״̬Ӧ�õ���Ļ��

	int x = 10;
	int y = 20;
	int nDir = 0;
	char ch = 0;
	while (true)
	{
		int Oldx = x;
		int Oldy = y;
		WriteChar(x, y, "��");//ָ��λ�ô�ӡ����
		if (_kbhit() == 1)//��������������ͬ��scanf����һֱ�����ȴ��û�����
		{
			ch = _getch();//�޻��ԵĻ�ȡ�ַ�
		}
		else
		{
			ch = 0;
		}
		switch (ch)//ͨ�����������Ʒ�����ͨ������������λ�ñ仯����ͬ�����棬ֱ��ͨ������������λ��
		{
		case 'w':
			nDir = 0;
			break;
		case 's':
			nDir = 1;
			break;
		case 'a':
			nDir = 2;
			break;
		case 'd':
			nDir = 3;
			break;
		default:
			break;
		}

		switch (nDir)//��ͨ������������λ�ñ仯���������м��˽�ɫ��
		{
		case 0:
			y--;
			break;
		case 1:
			y++;
			break;
		case 2:
			x--;
			break;
		case 3:
			x++;
			break;
		default:
			break;
		}
		Sleep(100);//�����ٶ�
		//��λ�ô�ӡ�գ���λ�ô�ӡ�ַ���ʵ���ƶ���Ч��
		//��������system("cls")�������ַ�ʽ����ʹ��Ļ��
		WriteChar(Oldx, Oldy, " ");//��λ��
		WriteChar(x, y, "��");
	}
}

// 3. ��껭ͼ��ûЧ����
void DrawMouse()
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);//��ȡ��Ļ���
	INPUT_RECORD ir = {};//�����¼
	DWORD dwCount = 0;//��Ϣ����
	while (true)
	{
		//����Ļ�ϻ�ȡ��Ϣ��������Ϣ�������������ϣ���Ļ�����룬������������������ƹܵ���
		ReadConsoleInput(
			hInput,  //���������̶�д������������Ļ��������Ļ�ϻ�ȡ��Ϣ ���������
			&ir,     //���ڻ�ȡ�ڿ���̨�ϵ���Ϣ������Ļ�ϻ�ȡ��ɶ   ����������
			1,       //ir�ĸ�����һ���ж�������Ķ�����Ϊ1����ֻ�������һ�����Լ�����ģ����������
			&dwCount //��ȡ�˶��ٸ���Ϣ  ����������
		);
		if (ir.EventType == MOUSE_EVENT)//�����Ļ�Ϸ�������갴���¼�
		{
			if (ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//��������
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;//��ȡ������λ��
				//��Ϊ������һ���ַ��������ǰ���ַ�����x����Ҫ/2��ʹ�����������ҵ��ٶ�һ�£�Ϊ����x/2����
				WriteChar(pos.X / 2, pos.Y, "��");//�ڰ�����λ�û�ͼ��

			}
			if (ir.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)//������Ҽ�
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;
				WriteChar(pos.X / 2, pos.Y, " ");//�ڰ�����λ����գ���ӡ���ַ�
			}

		}
	}

}

// 4. �ƶ���
// 5. ��ʳ��䳤

//int main()
//{
//	//WriteChar(10, 20, "hello");
//	//moveSth();
//	//DrawMouse();
//	
//	return 0;
//}


