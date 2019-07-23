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
	cout << "3. 绘制地图" << endl;
	gotoxy(MAP_X / 2 - 10, MAP_Y / 2);
	cout << "4. 退出游戏" << endl;
	gotoxy(MAP_X / 2 - 10, MAP_Y / 2 +2);
	cout << "请输入选择-> ";
}

//打印地图边界
void DrawMap()
{
	system("cls");//先清屏

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

	//for (int x = 0; x < MAP_X; x+=2)//要x+=2，还是因为x1b，y2b老问题
	//{
	//	for (int y = 0; y < MAP_Y; y++)
	//	{
	//		if (g_MAP[x][y] == 边界)
	//		{
	//			gotoxy4s(x, y);
	//			cout << "※";//占2B
	//			//cout << "#";
	//		}
	//		else
	//		{
	//			gotoxy(x, y);
	//			cout << "  ";
	//		}
	//	}
	//}

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
	setColor(12, 0);
	gotoxy(MAP_X_WALL + 2, 1);
	cout << "RUNNING" << endl;//正在运行的状态标识
	gotoxy(MAP_X_WALL + 2, 2);
	cout << "q: 暂停游戏" << endl;
	setColor(7, 0);

	g_Speed = 5 + (300 - g_SleepTime) / 25;
	gotoxy(MAP_X - 22 + 14, 6);
	cout << "  ";
	gotoxy(MAP_X - 22 + 14, 4);
	cout << "  ";
	gotoxy(MAP_X - 22, 6);
	cout << "当前分数: " << (score - 3)*5 << endl;//-3，原始蛇长为3,*5，吃一个为5分
	gotoxy(MAP_X - 22, 8);
	cout << "障碍个数: " << barrSize << endl;//
	gotoxy(MAP_X - 22, 10);
	cout << "当前速度: " << g_Speed << endl;//

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
	cout << "+:加速  -:减速" << endl;
	//gotoxy(MAP_X - 22, 26);
	//cout << "任意键: 恢复游戏" << endl;
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

	////设置地图
	//for (int x = 0; x < MAP_X; x++)
	//{
	//	for (int y = 0; y < MAP_Y; y++)
	//	{
	//		//地图边界
	//		if (x == 0 || x == MAP_X  || y == 0 || y == MAP_Y - 1 || x== MAP_X_WALL || (x>MAP_X_WALL&& x<MAP_X && y== MAP_Y/2))//x == MAP_X-2还是xy轴的老问题
	//		{
	//			g_MAP[x][y] = 边界;
	//		}
	//		//地图中的障碍物
	//		else
	//		{
	//			g_MAP[x][y] = 空地;
	//		}
	//	}
	//}

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

	//先别播，烦人
	//PlaySoundA("conf\\BGM.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		
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

//存档
void SaveGame(CSnake& snake, CBarrier& barrier, CFood& food)
{
	////C++方式
	//ofstream out("conf\\game2.i", ios::out | ios::binary);
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
	errno_t err = fopen_s(&pFile, "conf\\game.i", "wb");
	//写入当前睡眠时间，以保证速度在读取时也不变
	fwrite(&g_SleepTime, sizeof(int), 1, pFile);
	//写入障碍物数量和蛇的数量
	fwrite(&g_SnaCount, sizeof(int), 1, pFile);
	fwrite(&g_BarCount, sizeof(int), 1, pFile);
	//写入障碍物
	for (int i = 0; i < barrier.m_size; i++)
	{
		fwrite(&barrier.m_BarrArr[i], sizeof(COORD), 1, pFile);
	}
	fwrite(&barrier.m_size, sizeof(int), 1, pFile);
	//写入食物
	fwrite(&food.m_FoodPos, sizeof(COORD), 1, pFile);
	//写入蛇
	for (int i = 0; i < snake.m_SnakeBody.size(); i++)
	{
		fwrite(&snake.m_SnakeBody[i], sizeof(COORD), 1, pFile);
	}
	fwrite(&snake.m_SnakeTail, sizeof(COORD), 1, pFile);//要把蛇尾也写入，因为读取的蛇，蛇尾会少两次，经过两次iseat函数，故在故在读取时，也要将蛇尾pushback进去，以弥补少的那一个（一般少一个，而读取的蛇少两个
	fwrite(&snake.m_Dir, sizeof(int), 1, pFile);
	fwrite(&snake.m_IsAlive, sizeof(bool), 1, pFile);
	
	//关闭文件
	fclose(pFile);

}

//读档
void LoadGame(CSnake& snake, CBarrier& barrier, CFood& food)
{
	////C++方式
	//ifstream in("conf\\game2.i", ios::in | ios::binary);
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
	errno_t err = fopen_s(&pFile, "conf\\game.i", "rb");

	//读取当前睡眠时间，以保证速度在读取时也不变
	fread(&g_SleepTime, sizeof(int), 1, pFile);
	//写入障碍物数量和蛇的数量
	fread(&g_SnaCount, sizeof(int), 1, pFile);
	fread(&g_BarCount, sizeof(int), 1, pFile);
	//读取障碍物
	COORD tmp;
	for (int i = 0; i <g_BarCount; i++)
	{
		fread(&tmp, sizeof(COORD), 1, pFile);
		barrier.m_BarrArr.push_back(tmp);
	}
	fread(&barrier.m_size, sizeof(int), 1, pFile);
	//读取食物
	fread(&food.m_FoodPos, sizeof(COORD), 1, pFile);
	//读取蛇
	COORD tmp2;
	for (int i = 0; i < g_SnaCount; i++)
	{
		fread(&tmp2, sizeof(COORD), 1, pFile);
		snake.m_SnakeBody.push_back(tmp2);
	}
	fread(&snake.m_SnakeTail, sizeof(COORD), 1, pFile);
	snake.m_SnakeBody.push_back(snake.m_SnakeTail);//少了两次，要加一个进去以弥补
	fread(&snake.m_Dir, sizeof(int), 1, pFile);//在这报错
	fread(&snake.m_IsAlive, sizeof(bool), 1, pFile);//错

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


//自定义地图
void SaveMap()
{
	DrawMap();
	//打印编辑地图的帮助信息
	setColor(12, 0);
	gotoxy(MAP_X - 20, 4);
	cout << "编辑地图" << endl;
	gotoxy(MAP_X - 24, 6);
	cout << "左键单击：创建障碍" << endl;
	gotoxy(MAP_X - 24, 8);
	cout << "右键单击：消除障碍" << endl;
	gotoxy(MAP_X - 24, 10);
	cout << "界外双击：退出编辑" << endl;
	setColor(7, 0);

	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD ir = {};
	DWORD dwCount = 0;
	SetConsoleMode(hInput, ENABLE_MOUSE_INPUT);

	vector<COORD> BarrTmp;//障碍物数组
	int barrTmpSize  = 0;

	while (true)
	{
		ReadConsoleInput(hInput,&ir,1,&dwCount);
		if (ir.EventType == MOUSE_EVENT)
		{
			if (ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;//获取按键的位置
				if (pos.X > 0 && pos.X < MAP_X_WALL && pos.Y >0 && pos.Y < MAP_Y)
				{
					//BarrTmp.push_back(pos);//加入数组
					//barrTmpSize++;

					g_BarrMAP[pos.X][pos.Y] = 1;
					gotoxy4s(pos.X/2, pos.Y);//在这/2真是妙的一匹，5/2*2=4，保证这x方向占两个单位的字符，x只能是偶数，这样能减少出错，妙！
					cout << "※";
				}
			}
			if (ir.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;
				if (pos.X > 0 && pos.X < MAP_X_WALL && pos.Y >0 && pos.Y < MAP_Y)
				{

					//for (vector<COORD>::iterator it = BarrTmp.begin(); it!=  BarrTmp.end(); it++)
					//{
					//	if (pos.X == it->X && pos.Y == it->Y)//若是数组里的，则删除
					//	{
					//		BarrTmp.erase(it);
					//		barrTmpSize--;
					//		gotoxy4s(pos.X/2, pos.Y);
					//		cout << "  ";
					//	}
					//}

					g_BarrMAP[pos.X][pos.Y] = 0;
					gotoxy4s(pos.X/2, pos.Y);
					cout << "  ";
					
				}	
			}
			if (ir.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition; 
				if (!(pos.X > 0 && pos.X < MAP_X_WALL && pos.Y >0 && pos.Y < MAP_Y))
				{
					//地图外双击才退出，避免与左键单击创建障碍混淆
					break;
				}
			}
		}
	}


	for (int i = 0; i < MAP_X_WALL; i++)
	{
		for (int j = 0; j < MAP_Y; j++)
		{
			if (g_BarrMAP[i][j] == 1)
			{
				/*
				原来是51，避免x是奇数，故/2*2，即5/2*2=4，即得41
				若直接调X=x*2的那个移动函数，则在81打印
				若要得正确的41，则再/2
				真他妈坑啊，藏得真深，x轴一个单位，而y轴两个单位，坑！谨记！
				*/
				int t = i / 2;//5/2=2
				t = t * 2;//2*2=4，妙啊！！！
				COORD tmp = { t/2,j };//，因为打印的时候还要*2，故再除二
				BarrTmp.push_back(tmp);
				barrTmpSize++;
			}
		}
	}

	//写入地图文件
	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, "conf\\map.i", "wb");
	fwrite(&barrTmpSize, sizeof(int), 1, pFile);//写入障碍物数量
	for (int i = 0; i < BarrTmp.size(); i++)//写入障碍物
	{
		fwrite(&BarrTmp[i], sizeof(COORD), 1, pFile);
	}
	fclose(pFile);
}

//导入用户自定义的地图
void LoadMap(CBarrier& barrier)
{
	//vector<COORD> BarrTmp;//障碍物数组
	//int barrTmpSize = 0;
	COORD tmp;

	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, "conf\\map.i", "rb");
	fread(&barrier.m_size, sizeof(int), 1, pFile);//写入障碍物数量
	for (int i = 0; i < barrier.m_size; i++)//写入障碍物
	{
		fread(&tmp, sizeof(COORD), 1, pFile);
		barrier.m_BarrArr.push_back(tmp);//一定要借用tmp变量，不可直接读入BarrTmp[i]
	}
	fclose(pFile);

	//cout << barrTmpSize << endl;
	//for (int i = 0; i < barrTmpSize; i++)
	//{
	//	cout << BarrTmp[i].X << BarrTmp[i].Y << endl;
	//}
}

//处理用户输入
int HandleSelect()
{
	//char ch = getchar();//需要回车来确定，且输入可见
	char ch = _getch();//不需回车来确定，且无回显

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
	case '3'://自定义地图
		res = 3;
		break;
	case '4'://退出游戏
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

//处理用户输入（选择地图
int HandleSelectMap()
{
	system("cls");
	
	gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 6);
	cout << "请选择地图：" << endl;
	gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 4);
	cout << "1. 系统默认" << endl;
	gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 2);
	cout << "2. 玩家提供" << endl;
	gotoxy(MAP_X / 2 - 10, MAP_Y / 2);
	cout << "请输入选择-> ";

	int rres = 0;
	//char cch = getchar();//需要回车来确定，且输入可见
	char cch = _getch();
	
	switch (cch)
	{
	case '1'://系统默认
		break;
	case '2'://玩家提供
		rres = 1;
		break;
	default:
		gotoxy(MAP_X / 2 - 10, MAP_Y / 2 + 3);
		cout << "输入错误";
		break;
	}

	return rres;

}

//处理用户输入（选择等级）
void HandleSelectLevel()
{
	//通过时间和障碍来控制难度
	system("cls");

	gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 6);
	cout << "游戏难度：" << endl;
	gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 4);
	cout << "1. 简单" << endl;
	gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 2);
	cout << "2. 一般" << endl;
	gotoxy(MAP_X / 2 - 10, MAP_Y / 2);
	cout << "3. 困难" << endl;
	gotoxy(MAP_X / 2 - 10, MAP_Y / 2+2);
	cout << "请输入选择-> ";

	char cch = _getch();
	switch (cch)
	{
	case '1'://简单
		g_LevelBarrsize = 10;
		g_SleepTime = 400;
		break;
	case '2'://一般
		g_LevelBarrsize = 20;
		g_SleepTime = 300;
		break;
	case '3'://困难
		g_LevelBarrsize = 40;
		g_SleepTime = 200;
		break;
	}
}

////游戏主循环
//void PlayGame(CSnake & snake,CBarrier & barrier, CFood & food)
//{
//
//}

////设置游戏难度等级
//void SetLevel()
//{
//
//}

//void PlaySnd(string sound)
//{
//	//播放BGM
//	//conf\\BGM.wav
//	sound = "conf\\BGM.wav";
//	PlaySoundA("conf\\BGM.wav", NULL, SND_ASYNC | SND_NODEFAULT);
//}

///////////////////////////////////////////////////////////////////////////////////

//1. 在屏幕任何位置输出字符串
//void WriteChar(int x, int y, const char* p, int color = 0)
//{
//	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//获取标准输出句柄（在这是屏幕
//	COORD pos = { x, y };//坐标结构体
//	SetConsoleCursorPosition(hOutput, pos);//将光标移动到 屏幕上指定坐标位置
//	printf(p);//在指定位置打印
//}

//// 2. 受控制的自由移动的点
//void moveSth()
//{
//	//光标不可见
//	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//获取屏幕句柄（句柄就理解为指向某对象的指针，此句柄就代表某对象）
//	CONSOLE_CURSOR_INFO cci;//控制台光标对象
//	cci.dwSize = sizeof(cci);//光标大小？？干嘛用？
//	cci.bVisible = FALSE;//设置光标状态为不可见
//	SetConsoleCursorInfo(hOutput, &cci);//将光标状态应用到屏幕上
//
//	int x = 10;
//	int y = 20;
//	int nDir = 0;
//	char ch = 0;
//	while (true)
//	{
//		int Oldx = x;
//		int Oldy = y;
//		WriteChar(x, y, "☆");//指定位置打印星星
//		if (_kbhit() == 1)//非阻塞函数，不同于scanf，会一直阻塞等待用户输入
//		{
//			ch = _getch();//无回显的获取字符
//		}
//		else
//		{
//			ch = 0;
//		}
//		switch (ch)//通过按键来控制方向，再通过方向来控制位置变化（不同于上面，直接通过按键来控制位置
//		{
//		case 'w':
//			nDir = 0;
//			break;
//		case 's':
//			nDir = 1;
//			break;
//		case 'a':
//			nDir = 2;
//			break;
//		case 'd':
//			nDir = 3;
//			break;
//		default:
//			break;
//		}
//
//		switch (nDir)//再通过方向来控制位置变化（方向是中间人角色）
//		{
//		case 0:
//			y--;
//			break;
//		case 1:
//			y++;
//			break;
//		case 2:
//			x--;
//			break;
//		case 3:
//			x++;
//			break;
//		default:
//			break;
//		}
//		Sleep(100);//控制速度
//		//旧位置打印空，新位置打印字符，实现移动的效果
//		//尽量避免system("cls")清屏这种方式，会使屏幕闪
//		WriteChar(Oldx, Oldy, " ");//老位置
//		WriteChar(x, y, "☆");
//	}
//}

//// 3. 鼠标画图
//void DrawMouse()
//{
//	system("cls");
//	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
//	INPUT_RECORD ir = {};
//	DWORD dwCount = 0;
//
//	SetConsoleMode(hInput, ENABLE_MOUSE_INPUT);
//	while (true)
//	{
//		
//		ReadConsoleInput(
//			hInput,  
//			&ir,     
//			1,       
//			&dwCount 
//		);
//		if (ir.EventType == MOUSE_EVENT)
//		{
//			if (ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
//			{
//				COORD pos = ir.Event.MouseEvent.dwMousePosition;//获取按键的位置
//				//因为上下是一个字符，左右是半个字符，故x坐标要/2，使得上下与左右的速度一致（为何是x/2？）
//				gotoxy4s(pos.X / 2, pos.Y);
//				cout << "※";
//
//			}
//			if (ir.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
//			{
//				COORD pos = ir.Event.MouseEvent.dwMousePosition;
//				gotoxy4s(pos.X / 2, pos.Y);
//				cout << "  ";
//			}
//
//		}
//	}
//
//}

// 4. 移动蛇
// 5. 吃食物，变长
// 6. 二维数组存地图，即要解决的规划问题




