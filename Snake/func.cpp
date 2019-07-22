#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <time.h>
#include <conio.h>
#include "data.h"
#include "func.h"
#include "food.h"
#include "snake.h"
#include "barrier.h"

using namespace std;

//打印欢迎界面
void DrawWelcome()
{
 //      
	gotoxy(MAP_X / 2 - 25, MAP_Y / 2 -15);
	cout << " .M\"\"\"dgd       db      `7MN.   `7MF'`7MMF' `YMM' `7MM\"\"\"YMM " << endl;
	gotoxy(MAP_X / 2 - 25, MAP_Y / 2 - 14);
	cout << ",MI    \"Y      ;MM:       MMN.    M    MM   .M'     MM    `7 " << endl;
	gotoxy(MAP_X / 2 - 25, MAP_Y / 2 - 13);
	cout << "`MMb.         ,V^MM.      M YMb   M    MM .d\"       MM   d   " << endl;
	gotoxy(MAP_X / 2 - 25, MAP_Y / 2 - 12);
	cout << "  `YMMNq.    ,M  `MM      M  `MN. M    MMMMM.       MMmmMM   " << endl;
	gotoxy(MAP_X / 2 - 25, MAP_Y / 2 - 11);
	cout << ".     `MM    AbmmmqMA     M   `MM.M    MM  VMA      MM   Y  ," << endl;
	gotoxy(MAP_X / 2 - 25, MAP_Y / 2 - 10);
	cout << "Mb     dM   A'     VML    M     YMM    MM   `MM.    MM     ,M" << endl;
	gotoxy(MAP_X / 2 - 25, MAP_Y / 2 - 9);
	cout << "P\"Ybmmd\"  .AMA.   .AMMA..JML.    YM  .JMML.   MMb..JMMmmmmMMM" << endl;

	gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 6);
	cout << "1. 新游戏" << endl;
	gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 4);
	cout << "2. 读取游戏" << endl;
	gotoxy(MAP_X / 2 - 10, MAP_Y / 2 -2);
	cout << "3. 退出游戏" << endl;
	gotoxy(MAP_X / 2 - 10, MAP_Y / 2 -0);
	cout << "请输入选择-> ";
}

//处理用户输入
int HandleSelect()
{
	char ch = getchar();//需要回车来确定，且输入可见
	//char ch = _getch();//不需回车来确定，且无回显

	int res = 0;

	switch (ch)
	{
	case '1'://新游戏
		g_isRunning = true;
		res = 1;
		break;
	case '2'://读档
		g_isRunning = true;
		res = 2;
		break;
	case '3'://退出游戏
		gotoxy(MAP_X / 2 - 10, MAP_Y / 2 + 3);
		cout << "Bye！" << endl; 
		res = 0;
		//cin.get();
		break;
	default:
		gotoxy(MAP_X / 2 - 10, MAP_Y / 2 + 3);
		cout << "输入错误";
		break;
	}
	return res;
}

//打印地图边界
void DrawMap()
{
	system("cls");//先清屏

	////上边界
	//for (int i = 0; i < MAP_X; i++)
	//	cout << "#";
	//cout << endl;
	////其他边界here
	//for (int i = 0; i < MAP_Y - 2; i++)
	//{
	//	for (int j = 0; j < MAP_X; j++)
	//	{
	//		if (i == 13 && j >= MAP_X - 29)
	//		{
	//			cout << "#";
	//			continue;
	//		}
	//		if (j == 0 || j == MAP_X - 29 || j == MAP_X - 1)
	//		{
	//			cout << "#";
	//		}
	//		else
	//			cout << " ";
	//	}
	//	cout << endl;
	//}
	////下边界
	//for (int i = 0; i < MAP_X; i++)
	//	cout << "#";

	for (int x = 0; x < MAP_X; x+=2)//要x+=2，还是因为x1b，y2b老问题
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			if (g_MAP[x][y]== 边界)
			{
				gotoxy(x, y);
				cout << "※";//占2B
				//cout << "#";
			}
			else
			{
				gotoxy(x, y);
				cout << " ";
			}
		}
	}

}

//游戏结束
void GameOver(int score)
{
	setColor(12, 0);

	gotoxy(MAP_X / 2 - 20, MAP_Y / 2 - 5);
	cout << "GAME OVER! " << endl;

	gotoxy(MAP_X / 2 - 20, MAP_Y / 2 - 3);
	cout << "Scores: " << score - 3 << endl;

	return;
}

//打印相关信息
void DrawGameInfo(int score,int barrSize)
{
	gotoxy(MAP_X - 22 + 14, 6);
	cout << "  ";
	gotoxy(MAP_X - 22 + 14, 4);
	cout << "  ";
	gotoxy(MAP_X - 22, 6);
	cout << "当前分数: " << score - 3 << endl;//-3，原始蛇长为3
	gotoxy(MAP_X - 22, 8);
	cout << "障碍个数: " << barrSize << endl;//
	gotoxy(MAP_X - 22, 10);
	cout << "当前速度: " << "Not Set" << endl;//

}

//打印游戏帮助
void DrawGameHelp()
{
	gotoxy(MAP_X-22+2, 18);
	cout << "操作说明：" << endl;
	gotoxy(MAP_X-22, 20);
	cout << "W: 上    S: 下" << endl;
	gotoxy(MAP_X-22, 22);
	cout << "A: 左    D: 右" << endl;
	gotoxy(MAP_X - 22, 24);
	cout << "Q: 暂停游戏" << endl;
	gotoxy(MAP_X - 22, 26);
	cout << "任意键: 恢复游戏" << endl;
}

//初始化工作
void GameInit()
{
	//设置窗口大小here
	//char buf[32];
	//sprintf_s(buf, "mode con cols=%d lines=%d", MAP_X, MAP_Y);
	//system(buf);

	//设置地图
	for (int x = 0; x < MAP_X; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			//地图边界
			if (x == 0 || x == MAP_X-2  || y == 0 || y == MAP_Y - 1 || x== MAP_X_WALL || (x>MAP_X_WALL && y== MAP_Y/2))//x == MAP_X-2还是xy轴的老问题
			{
				g_MAP[x][y] = 边界;
			}
			//地图中的障碍物
			//else if()
			else
			{
				g_MAP[x][y] = 空地;
			}
		}
	}

	//隐藏光标
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);	//获取控制台光标信息
	CursorInfo.bVisible = false;				//隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);	//设置控制台光标状态

	//初始化随机数种子
	srand((unsigned int)time(0));

	//播放BGM
	//while (true)//循环播放
	//{
	//	PlaySoundA("conf\\BGM.wav", NULL, SND_ASYNC | SND_NODEFAULT);
	//}

	PlaySoundA("conf\\BGM.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		
}

//移动光标（打印食物、蛇、障碍物
void gotoxy4s(int x, int y)
{
	COORD cur;//系统提供的坐标结构体
	cur.X = x*2;//here上下与左右速度不匹配
	//cur.X = x;
	cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}

//移动光标（打印地图、分数、提示信息等其他用）
void gotoxy(int x, int y)
{
	COORD cur;//系统提供的坐标结构体
	//cur.X = x*2;//here上下与左右速度不匹配
	cur.X = x;
	cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}

//设置颜色
void setColor(unsigned short ForeColor, unsigned short BackGroundColor)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//获取当前窗口句柄
	SetConsoleTextAttribute(handle, ForeColor + BackGroundColor * 0x10);//设置颜色
}

//设置游戏难度等级
void SetLevel()
{

}

////游戏主循环
//void PlayGame(CSnake & snake,CBarrier & barrier, CFood & food)
//{
//
//}

//存档
void SaveGame(CSnake& snake, CBarrier& barrier, CFood& food)
{
	////C++方式
	//ofstream out("conf\\game.i", ios::out | ios::binary);
	////写入蛇
	//for (int i = 0; i < snake.m_SnakeBody.size(); i++)
	//{
	//	out.write((char*)&snake.m_SnakeBody[i], sizeof(COORD));
	//}
	//out.write((char*)& snake.m_Dir, sizeof(int));
	//out.write((char*)& snake.m_IsAlive, sizeof(bool));
	////写入障碍物
	//for (int i = 0; i < barrier.m_size; i++)
	//{
	//	out.write((char*)& barrier.m_BarrArr[i], sizeof(COORD));
	//}
	//out.write((char*)& barrier.m_size, sizeof(int));
	////写入食物
	//out.write((char*)& food.m_FoodPos, sizeof(COORD));
	//out.close();

	g_SnaCount = snake.m_SnakeBody.size();//为2
	g_BarCount = barrier.m_size;//15
	//打开文件
	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, "conf\\game2.i", "wb");
	//写入障碍物
	for (int i = 0; i < barrier.m_size; i++)
	{
		fwrite(&barrier.m_BarrArr[i], sizeof(COORD), 1, pFile);
	}
	fwrite(&barrier.m_size, sizeof(int), 1, pFile);
	//写入蛇
	for (int i = 0; i < snake.m_SnakeBody.size(); i++)
	{
		fwrite(&snake.m_SnakeBody[i], sizeof(COORD), 1, pFile);
	}
	fwrite(&snake.m_Dir, sizeof(int), 1, pFile);
	fwrite(&snake.m_IsAlive, sizeof(bool), 1, pFile);
	//写入食物
	fwrite(&food.m_FoodPos, sizeof(COORD), 1, pFile);
	//关闭文件
	fclose(pFile);

}

//读档
void LoadGame(CSnake& snake, CBarrier& barrier, CFood& food)
{
	////C++方式
	//ifstream in("conf\\game.i", ios::in | ios::binary);
	//COORD tmp;
	////读取蛇
	//for (int i = 0; i < 3; i++)
	//{
	//	in.read((char*)& tmp, sizeof(COORD));
	//	snake.m_SnakeBody.push_back(tmp);
	//}
	//in.read((char*)& snake.m_Dir, sizeof(int));
	//in.read((char*)& snake.m_IsAlive, sizeof(bool));
	////读取障碍物
	//for (int i = 0; i < 15; i++)
	//{
	//	in.read((char*)& tmp, sizeof(COORD));
	//	barrier.m_BarrArr.push_back(tmp);
	//}
	//in.read((char*)& barrier.m_size, sizeof(int));
	////读取食物
	//in.read((char*)& food.m_FoodPos, sizeof(COORD));
	//in.close();

	//打开文件
	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, "conf\\game2.i", "rb");
	//读取障碍物
	COORD tmp;
	for (int i = 0; i <15; i++)
	{
		fread(&tmp, sizeof(COORD), 1, pFile);
		barrier.m_BarrArr.push_back(tmp);
	}

	fread(&barrier.m_size, sizeof(int), 1, pFile);
	//读取蛇
	COORD tmp2;
	for (int i = 0; i < 2; i++)
	{
		fread(&tmp2, sizeof(COORD), 1, pFile);
		snake.m_SnakeBody.push_back(tmp2);
	}
	fwrite(&snake.m_Dir, sizeof(int), 1, pFile);//在这报错
	fwrite(&snake.m_IsAlive, sizeof(bool), 1, pFile);//错
	//读取食物
	fread(&food.m_FoodPos, sizeof(COORD), 1, pFile);
	//关闭文件
	fclose(pFile);


	////打开文件
	//FILE* pFile = NULL;
	//errno_t err = fopen_s(&pFile, "conf\\game2.i", "rb");
	////读取文件
	//fread(&snake, sizeof(CSnake), 1, pFile);
	//fread(&barrier, sizeof(CBarrier), 1, pFile);
	//fread(&food, sizeof(CFood), 1, pFile);
	////关闭文件
	//fclose(pFile);

}

//void PlaySnd(string sound)
//{
//	//播放BGM
//	//conf\\BGM.wav
//	sound = "conf\\BGM.wav";
//	PlaySoundA("conf\\BGM.wav", NULL, SND_ASYNC | SND_NODEFAULT);
//}

///////////////////////////////////////////////////////////////////////////////////

//1. 在屏幕任何位置输出字符串
void WriteChar(int x, int y, const char* p, int color = 0)
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//获取标准输出句柄（在这是屏幕
	COORD pos = { x, y };//坐标结构体
	SetConsoleCursorPosition(hOutput, pos);//将光标移动到 屏幕上指定坐标位置
	printf(p);//在指定位置打印
}

// 2. 受控制的自由移动的点
void moveSth()
{
	//光标不可见
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//获取屏幕句柄（句柄就理解为指向某对象的指针，此句柄就代表某对象）
	CONSOLE_CURSOR_INFO cci;//控制台光标对象
	cci.dwSize = sizeof(cci);//光标大小？？干嘛用？
	cci.bVisible = FALSE;//设置光标状态为不可见
	SetConsoleCursorInfo(hOutput, &cci);//将光标状态应用到屏幕上

	int x = 10;
	int y = 20;
	int nDir = 0;
	char ch = 0;
	while (true)
	{
		int Oldx = x;
		int Oldy = y;
		WriteChar(x, y, "☆");//指定位置打印星星
		if (_kbhit() == 1)//非阻塞函数，不同于scanf，会一直阻塞等待用户输入
		{
			ch = _getch();//无回显的获取字符
		}
		else
		{
			ch = 0;
		}
		switch (ch)//通过按键来控制方向，再通过方向来控制位置变化（不同于上面，直接通过按键来控制位置
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

		switch (nDir)//再通过方向来控制位置变化（方向是中间人角色）
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
		Sleep(100);//控制速度
		//旧位置打印空，新位置打印字符，实现移动的效果
		//尽量避免system("cls")清屏这种方式，会使屏幕闪
		WriteChar(Oldx, Oldy, " ");//老位置
		WriteChar(x, y, "☆");
	}
}

// 3. 鼠标画图（没效果？
void DrawMouse()
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);//获取屏幕句柄
	INPUT_RECORD ir = {};//输入记录
	DWORD dwCount = 0;//信息数量
	while (true)
	{
		//从屏幕上获取信息，并将信息传到其他对象上（屏幕是输入，其他对象是输出，类似管道）
		ReadConsoleInput(
			hInput,  //输出句柄，固定写法，在这是屏幕，即从屏幕上获取信息 （传入参数
			&ir,     //用于获取在控制台上的信息，从屏幕上获取了啥   （传出参数
			1,       //ir的个数，一共有多少输入的东西，为1，即只有鼠标这一个（自己理解的）（传入参数
			&dwCount //读取了多少个信息  （传出参数
		);
		if (ir.EventType == MOUSE_EVENT)//如果屏幕上发生了鼠标按键事件
		{
			if (ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//如果是左键
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;//获取按键的位置
				//因为上下是一个字符，左右是半个字符，故x坐标要/2，使得上下与左右的速度一致（为何是x/2？）
				WriteChar(pos.X / 2, pos.Y, "☆");//在按键的位置画图；

			}
			if (ir.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)//如果是右键
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;
				WriteChar(pos.X / 2, pos.Y, " ");//在按键的位置清空（打印空字符
			}

		}
	}

}

// 4. 移动蛇
// 5. 吃食物，变长
// 6. 二维数组存地图，即要解决的规划问题




