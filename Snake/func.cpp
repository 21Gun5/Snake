#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <io.h>
#include <time.h>
#include <iomanip>
#include <conio.h>
#include "data.h"
#include "func.h"
#include "food.h"
#include "snake.h"
#include "barrier.h"

using namespace std;

void DrawWelcome()
{
	/*
	1. 打印欢迎界面
	2. 包括图案和提示信息
	*/

	 //打印图案
	Gotoxy(MAP_X / 2 - 25, MAP_Y / 2 - 15);
	cout << " .M\"\"\"dgd       db      `7MN.   `7MF'`7MMF' `YMM' `7MM\"\"\"YMM " << endl;
	Gotoxy(MAP_X / 2 - 25, MAP_Y / 2 - 14);
	cout << ",MI    \"Y      ;MM:       MMN.    M    MM   .M'     MM    `7 " << endl;
	Gotoxy(MAP_X / 2 - 25, MAP_Y / 2 - 13);
	cout << "`MMb.         ,V^MM.      M YMb   M    MM .d\"       MM   d   " << endl;
	Gotoxy(MAP_X / 2 - 25, MAP_Y / 2 - 12);
	cout << "  `YMMNq.    ,M  `MM      M  `MN. M    MMMMM.       MMmmMM   " << endl;
	Gotoxy(MAP_X / 2 - 25, MAP_Y / 2 - 11);
	cout << ".     `MM    AbmmmqMA     M   `MM.M    MM  VMA      MM   Y  ," << endl;
	Gotoxy(MAP_X / 2 - 25, MAP_Y / 2 - 10);
	cout << "Mb     dM   A'     VML    M     YMM    MM   `MM.    MM     ,M" << endl;
	Gotoxy(MAP_X / 2 - 25, MAP_Y / 2 - 9);
	cout << "P\"Ybmmd\"  .AMA.   .AMMA..JML.    YM  .JMML.   MMb..JMMmmmmMMM" << endl;

	//提示信息
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 6);
	cout << "1. 新游戏" << endl;
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 4);
	cout << "2. 读取游戏" << endl;
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 2);
	cout << "3. 退出游戏" << endl;
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 -0);
	cout << "请输入选择-> ";
	SetCursorState(true);			//用户输入时，光标可见
}

void DrawMapBorder()
{
	/*
	1. 打印地图边界
	*/

	system("cls");						//换页则清屏
	for (int x = 0; x < MAP_X; x += 2)	//要x+=2，因xy方向大小不同
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			if (g_MAP[x][y] == 边界)
			{
				Gotoxy(x, y);
				cout << "※";			//占2字符
			}
		}
	}
}

void GameOver(int score)
{
	/*
	1. 游戏结束后的扫尾工作
	2. 关闭bgm文件
	3. 游戏结束的提示信息及最终分数
	*/

	//关闭音乐文件
	mciSendString("close bgm", NULL, 0, NULL);	//close关闭而非stop停止
	
	//提示信息
	setColor(12, 0);
	Gotoxy(MAP_X / 2 - 20, MAP_Y / 2 - 5);
	cout << "GAME OVER! " << endl;
	Gotoxy(MAP_X / 2 - 20, MAP_Y / 2 - 3);
	cout << "Scores: " << score - 3 << endl;	//蛇身初始3节

	return;
}

void DrawGameInfo(int score, int barrSize,int blood)
{
	/*
	1. 运行状态
	2. 分数、生命值等
	*/

	//运行or暂停状态
	setColor(12, 0);
	Gotoxy(MAP_X_WALL + 2, 1);
	cout << "RUNNING" << endl;//正在运行的状态标识
	Gotoxy(MAP_X_WALL + 2, 2);
	cout << "q: 暂停游戏" << endl;
	setColor(7, 0);

	//分数等信息
	g_Speed = 5 + (300 - g_SleepTime) / 25;
	Gotoxy(MAP_X - 22 + 14, 6);
	cout << "  ";
	Gotoxy(MAP_X - 22 + 14, 4);
	cout << "  ";
	Gotoxy(MAP_X - 22, 5);
	cout << "当前分数: " << setw(2) << (score - 3) * 5 << endl;//-3：原始蛇长为3；*5，吃一个5分
	Gotoxy(MAP_X - 22, 7);
	cout << "当前生命: " << setw(2) << blood << endl;
	Gotoxy(MAP_X - 22, 9);
	cout << "障碍个数: " << setw(2) << barrSize << endl;
	Gotoxy(MAP_X - 22, 11);
	cout << "当前速度: " << setw(2)<< g_Speed << endl;			//用setw，避免10到9，0仍在
}

void DrawGameHelp()
{
	//打印游戏帮助
	Gotoxy(MAP_X - 22 + 2, 18);
	cout << "操作说明：" << endl;
	Gotoxy(MAP_X - 22, 20);
	cout << "W: 上    S: 下" << endl;
	Gotoxy(MAP_X - 22, 22);
	cout << "A: 左    D: 右" << endl;
	Gotoxy(MAP_X - 22, 24);
	cout << "+:加速  -:减速" << endl;
}

void SetCursorState(bool b)
{
	/*
	1. 设置光标状态
	2. 用户输入前显示坐标，输入后隐藏
	*/

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);	//获取控制台光标信息
	CursorInfo.bVisible = b;					//显示/隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);	//设置控制台光标状态
}

void GameInit()
{
	/*
	1. 游戏开始前的初始化工作（对应扫尾工作
	2. 地图、光标等
	*/

	//设置地图
	for (int x = 0; x < MAP_X; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			//地图边界
			if (x == 0 || x == MAP_X - 2 || x == MAP_X_WALL||	//三竖边
				y == 0 || y == MAP_Y - 1  ||					//两横边
				(x > MAP_X_WALL && y == MAP_Y / 2))				//帮助信息与游戏信息分割线
			{
				g_MAP[x][y] = 边界;
			}
		}
	}

	//隐藏光标
	SetCursorState(false);

	//初始化随机数种子
	srand((unsigned int)time(0));

	//播放背景音乐（可循环
	PlayBGM();
}

void GotoxyFor2(int x, int y)
{
	/*
	1. 移动光标到指定位置
	2. 适用于蛇、食物、障碍这样的2单位的字符
	*/

	COORD cur;
	cur.X = x * 2;//here上下与左右速度不匹配
	//cur.X = x;
	cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}

void Gotoxy(int x, int y)
{
	/*
	1. 移动光标到指定位置
	2. 适用于普通的1单位字符
	*/

	COORD cur;
	cur.X = x;
	cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}

void setColor(unsigned short ForeColor, unsigned short BackGroundColor)
{
	/*
	设置颜色
	*/

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);					//获取当前窗口句柄
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
	errno_t err = fopen_s(&pFile, "conf\\game\\game.i", "wb");
	//写入当前生命值
	fwrite(&snake.m_Blood, sizeof(int), 1, pFile);
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
	errno_t err = fopen_s(&pFile, "conf\\game\\game.i", "rb");

	//读取生命值 
	fread(&snake.m_Blood, sizeof(int), 1, pFile);
	//读取当前睡眠时间，以保证速度在读取时也不变
	fread(&g_SleepTime, sizeof(int), 1, pFile);
	//写入障碍物数量和蛇的数量
	fread(&g_SnaCount, sizeof(int), 1, pFile);
	fread(&g_BarCount, sizeof(int), 1, pFile);
	//读取障碍物
	COORD tmp;
	for (int i = 0; i < g_BarCount; i++)
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





int SelectAction()
{
	/*
	1. 选择新游戏 or 读取游戏 or 退出游戏
	*/

	int input = _getch()-48;	//无回显接收；-48保证在0-9，而非ASCII
	SetCursorState(false);	//输入完隐藏光标

	switch (input)
	{
	case 新游戏:
	{
		g_isRunning = true;
		break;
	}
	case 读取游戏:
	{
		g_isRunning = true;
		break;
	}
	case 退出游戏:
	{
		Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 + 3);
		cout << "Bye! " << endl;
		break;
	}
	default:
		Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 + 3);
		cout << "输入错误";
		break;
	}
	return input;
}

int SelectWhoMap()
{
	/*
	1. 选择系统地图 or 用户自定义地图
	*/

	//打印提示信息
	system("cls");				//换页则清屏
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 6);
	cout << "请选择地图：" << endl;
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 4);
	cout << "1. 系统默认" << endl;
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 2);
	cout << "2. 玩家提供" << endl;
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2);
	cout << "请输入选择-> ";
	SetCursorState(true);		//用户输入前显示光标

	int input = _getch()-48;	//控制其0-9，而非ASCII
	SetCursorState(false);		//输入结束后隐藏光标

	return input;
}

void SelectLevel()
{
	/*
	1. 选择等级，只适用于系统地图
	2. 睡眠时间、障碍物数量决定难度等级
	*/

	//打印提示信息
	system("cls");				//换页则清屏
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 6);
	cout << "游戏难度：" << endl;
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 4);
	cout << "1. 简单" << endl;
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 2);
	cout << "2. 一般" << endl;
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2);
	cout << "3. 困难" << endl;
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 + 2);
	cout << "请输入选择-> ";
	SetCursorState(true);		//显示光标

	int input = _getch()-48;	//避免ASCII
	SetCursorState(false);		//隐藏光标

	//难度与障碍物数量成正比、与睡眠时间成反比
	switch (input)
	{
	case 简单:
		g_LevelBarrsize = 10;
		g_SleepTime = 400;
		break;
	case 一般:
		g_LevelBarrsize = 20;
		g_SleepTime = 300;
		break;
	case 困难:
		g_LevelBarrsize = 40;
		g_SleepTime = 200;
		break;
	default:
		break;
	}
}

int SelectWhenMap()
{
	/*
	1. 选择新旧地图，只适用于用户自定义地图
	2. 新建地图 or 之前建的老地图
	*/

	//提示信息
	system("cls");
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 6);
	cout << "地图选择" << endl;
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 4);
	cout << "1. 新建地图" << endl;
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 2);
	cout << "2. 已有地图" << endl;
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 );
	cout << "请输入选择-> ";
	SetCursorState(true);//显示光标

	int input = _getch()-48;
	SetCursorState(false);//隐藏光标

	return input;
}

string SetMap()
{
	/*
	1. 用户自定义地图并保存
	2. 实际上是设置障碍物排布
	2. 利用鼠标事件
	3. 由二维数组作为屏幕与文件的中介
	*/

	DrawMapBorder();		//首先打印地图边界

	//提示信息
	setColor(12, 0);
	Gotoxy(MAP_X - 20, 4);
	cout << "编辑地图" << endl;
	Gotoxy(MAP_X - 24, 6);
	cout << "左键单击：创建障碍" << endl;
	Gotoxy(MAP_X - 24, 8);
	cout << "右键单击：消除障碍" << endl;
	Gotoxy(MAP_X - 24, 10);
	cout << "界外双击：退出编辑" << endl;
	setColor(7, 0);

	//鼠标事件相关
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD ir = {};
	DWORD dwCount = 0;
	SetConsoleMode(hInput, ENABLE_MOUSE_INPUT);

	vector<COORD> BarrTmp;//障碍物数组
	int barrTmpSize = 0;

	//捕获鼠标事件并反馈给屏幕
	while (true)
	{
		ReadConsoleInput(hInput, &ir, 1, &dwCount);
		if (ir.EventType == MOUSE_EVENT)
		{
			if (ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;//获取按键的位置
				if (pos.X > 0 && pos.X < MAP_X_WALL && pos.Y >0 && pos.Y < MAP_Y)
				{

					g_BarrMAP[pos.X][pos.Y] = 1;
					GotoxyFor2(pos.X / 2, pos.Y);//在这/2真是妙的一匹，5/2*2=4，保证这x方向占两个单位的字符，x只能是偶数，这样能减少出错，妙！
					cout << "※";
				}
			}
			if (ir.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;
				if (pos.X > 0 && pos.X < MAP_X_WALL && pos.Y >0 && pos.Y < MAP_Y)
				{

					g_BarrMAP[pos.X][pos.Y] = 0;
					GotoxyFor2(pos.X / 2, pos.Y);
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

	//将屏幕状态存入二维数组
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
				COORD tmp = { t / 2,j };//，因为打印的时候还要*2，故再除二
				BarrTmp.push_back(tmp);
				barrTmpSize++;
			}
		}
	}

	//提示信息

	string str;
	system("cls");
	setColor(12, 0);
	Gotoxy(MAP_X - 24, 12);
	cout << "请输入地图名字" << endl;
	Gotoxy(MAP_X - 24, 14);
	cin >> str;
	setColor(7, 0);

	string str1 = str + ".i";
	string str2 = "conf\\map\\" + str1;
	const char* filename = str2.c_str();




	//将数组相关信息写入文件
	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, filename, "wb");
	//errno_t err = fopen_s(&pFile, "conf\\map.i", "wb");
	fwrite(&barrTmpSize, sizeof(int), 1, pFile);//写入障碍物数量
	for (int i = 0; i < BarrTmp.size(); i++)	//遍历写入障碍物
	{
		fwrite(&BarrTmp[i], sizeof(COORD), 1, pFile);
	}
	fclose(pFile);

	return str1;
}

void LoadMap(CBarrier& barrier,string str)
{
	/*
	1. 导入用户自定义的地图
	2. 接受者为障碍物对象
	*/
	str = "conf\\map\\" + str;
	const char* filename = str.c_str();//here


	COORD tmp;
	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, filename, "rb");//here
	//errno_t err = fopen_s(&pFile, "conf\\map.i", "rb");
	fread(&barrier.m_size, sizeof(int), 1, pFile);	//读取障碍物数量
	for (int i = 0; i < barrier.m_size; i++)		//遍历读取障碍物
	{
		fread(&tmp, sizeof(COORD), 1, pFile);
		barrier.m_BarrArr.push_back(tmp);			//借用tmp变量，不可直接读入
	}
	fclose(pFile);
}

//here
string ShowMaps()
{
	//目标文件夹路径
	std::string inPath = "conf/map/*.i";//遍历文件夹下的所有.jpg文件
	//用于查找的句柄
	long handle;
	_finddata_t fileinfo;
	//第一次查找
	handle = _findfirst(inPath.c_str(), &fileinfo);
	if (handle == -1)
		return 0;
	do
	{
		g_Maps.push_back(fileinfo.name);
		//找到的文件的文件名
		//cout << fileinfo.name;
		//printf("%s\n", fileinfo.name);

	} while (!_findnext(handle, &fileinfo));

	_findclose(handle);


	system("cls");
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 8);
	cout << "请选择地图" << endl;

	int i = 0;
	for (; i < g_Maps.size(); i++)
	{
		//提示信息
		Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 6 + i);
		cout << i + 1 << ". " << g_Maps[i] << endl;
		//printf("%d. %s\n", i+1, g_MAP[i]);
		//cout << g_Maps[i].substr() << endl;
	}
	Gotoxy(MAP_X / 2 - 10, MAP_Y / 2 - 6 + i);
	cout << "请输入选择-> ";

	int input = _getch() - 48;

	return g_Maps[input - 1];

}



void PlayBGM()
{
	/*
	1. 播放背景音乐（可循环)
	2. 打开游戏播放，蛇死亡停止
	3. 暂停时停止，恢复时播放
	*/

	// 打开音频文件（死亡时关闭
	mciSendString("open conf/BGM.mp3 alias bgm", NULL, 0, NULL);//别名不可大写
	mciSendString("play bgm repeat", NULL, 0, NULL);			// 循环播放,适用于.mp3格式
}
