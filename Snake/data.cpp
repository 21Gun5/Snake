#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <string>
#include "data.h"
#include "func.h"
using namespace std;

int g_SleepTime = 300;
int g_Speed = 5;
int g_foodCount = 0;
int g_LevelBarrsize = 0;
bool g_isRunning = false;
int g_SnaCount;
int g_BarCount;
vector<string> g_Maps;
vector<string> g_Games;
int g_MAP[MAP_X][MAP_Y];
int g_BarrMAP[MAP_X_WALL][MAP_Y] = { 0 };