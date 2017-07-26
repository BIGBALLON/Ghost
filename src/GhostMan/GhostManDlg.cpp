
// GhostManDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GhostMan.h"
#include "GhostManDlg.h"
#include "afxdialogex.h"
#include <queue>
#include <stack>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



int g_maze[MAXX][MAXY] = {
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4, 4, 2, 4, 4, 4, 4, 2, 2, -1, 4, 4, 4, 4,
	-1, 1, 1, 1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, -1, 1, 1, 1, 1, -1, 4, 4, 2, 2, 4, 4, 4, 2, 2, 4, 4, -1, 4, 4,
	-1, 1, 1, 1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, 4, 4, 4, 4, 2, 2, 4, 4, 2, 2, 4, 4, 4, 4,
	-1, 1, 1, 1, -1, 1, 1, 1, 1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, -1, 4, 4, 4, -1, 4, 2, 2, 4, 2, 2, 4, 4, -1, 4,
	-1, 1, -1, -1, -1, -1, -1, 1, 1, -1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, -1, 1, 1, 1, 1, -1, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 4, 4, 4, 4,
	-1, 1, -1, 1, 1, 1, -1, 1, 1, -1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, -1, -1, -1, 1, -1, -1, 4, -1, 4, 4, -1, 4, 4, 2, 2, 4, 4, 4, 4, 4,
	-1, 1, -1, 1, 1, 1, -1, 1, 1, -1, -1, -1, 1, 1, 1, -1, 1, 1, 1, 1, -1, 1, 1, 1, 1, -1, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 4, 4, 4, 4,
	-1, 1, -1, 1, 1, 1, -1, 1, 1, 1, 1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, 1, 1, 1, 1, -1, 4, 4, -1, 4, 4, -1, 4, 2, 2, 2, 4, 4, 4, 4,
	-1, 1, -1, 1, 1, 1, -1, 1, 1, 1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, 4, 4, 4, 4, 4, 4, 4, 2, 2, 3, 4, 4, 3, 3,
	-1, 1, -1, 1, 1, 1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, -1, 4, 4, 3, 2, 2, 3, 3, 3, 3, 3,
	-1, 1, -1, 1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, 4, -1, 4, 4, 3, 3, 3, 2, 2, 3, 3, 3, 3, 3,
	-1, 1, 1, 1, 1, 1, 1, 1, 1, -1, -1, -1, -1, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1, 1, -1, -1, 4, 4, 4, 3, 3, 3, 2, 2, 2, 3, 3, 3, 3, 3,
	-1, 1, -1, 1, 1, 1, 1, 1, 1, -1, 1, 1, -1, 1, 1, -1, 1, 1, 1, 1, -1, 1, 1, 1, 1, -1, 4, 4, 3, 3, 3, 2, 2, 2, 3, 3, 3, 3, 3, 3,
	-1, 1, -1, 1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, -1, 1, 1, 1, 1, -1, 4, 3, 3, 3, 3, 2, 2, 3, 3, 3, 3, -1, 3, 3,
	-1, 1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, -1, 1, 1, -1, 1, 1, 1, 1, -1, 1, 1, 1, 1, -1, 4, 3, 3, 3, 3, 2, 2, 3, -1, 3, 3, 3, 3, 3,
	-1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, 1, -1, 1, 1, -1, 1, 1, 1, 1, -1, 1, 1, 1, 1, -1, 4, 3, 3, 3, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
	-1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, 1, -1, 1, 1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, -1, 3, 3, 3,
	-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, -1, 3, 3, 3, 3, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
	-1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, 1, -1, 1, 1, -1, 1, 1, 1, 1, -1, 1, 1, 1, 1, -1, 3, 3, 3, 3, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 3, 3, 3, 3, 3, 2, 2, 3, 3, 3, 3, 3, 3, 3
};

int g_SaMaze[MAXX][MAXY] = {
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 2, 2, 2, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

int g_SaNewMaze[MAXX][MAXY] = {
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 2, 2, 2, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

int g_Squared[3][3] = {
	{ 1, 2, 3 },
	{ 4, 5, 6 },
	{ 7, 8, 0 },
};

int g_Derrick[7][7] = {
	{ 0, 0, 1, 0, 1, 0, 0 },
	{ 0, 0, 1, 0, 1, 0, 0 },
	{ 3, 2, 3, 2, 3, 1, 3 },
	{ 0, 0, 2, 0, 2, 0, 0 },
	{ 3, 1, 3, 2, 1, 3, 2 },
	{ 0, 0, 2, 0, 1, 0, 0 },
	{ 0, 0, 2, 0, 3, 0, 0 },
};

int g_NewDerrick[7][7] = {
	{ 0, 0, 1, 0, 1, 0, 0 },
	{ 0, 0, 1, 0, 1, 0, 0 },
	{ 3, 2, 3, 2, 3, 1, 3 },
	{ 0, 0, 2, 0, 2, 0, 0 },
	{ 3, 1, 2, 2, 2, 3, 1 },
	{ 0, 0, 2, 0, 1, 0, 0 },
	{ 0, 0, 3, 0, 3, 0, 0 },
};

char ans[100];
Point S[MAXX][MAXY];
int g_NewMaze[MAXX][MAXY];		
int vis[MAXX][MAXY];			//访问标记
int Path_Len = 0;				//路径长度
int finded = false;				//是否找到路径 
unsigned long long Time = 0;	//所花时间
int Deep = 0;					//所走的深度
stack<pair<int, int> > Path;	//存放路径
int Out_Path[MAXX*MAXY][2];		//用久存放路径
int Best_Path[MAXX * MAXY][2];	//存储路径 
int buff[55];
char op[] = "rdlu";
//IDA_Path 用于存放路径序列，存放的是 char 型字符 rdlu
char IDA_Path[2333];
int ok;
int limit;

stack<Point> sta;
int sx, sy, ex, ey;

IDA_S s;
SAPoint e1, e2, p[1005], m[20];
CPoint PResult(20,10);
const double EPS = 1e-2;
const double INF = 1e20;
double x, y;
int cnt;
/************************************************/

int dir_x[] = { 0, 1, 0, -1 };	//x方向的移动
int dir_y[] = { 1, 0, -1, 0 };	//y方向的移动
//从左到右依次是 (0,1) (0,-1) (1,0), (-1,0)
//分别对应        右     左      下     上
//不管怎样如果是对应地图，都按照上面这样规定
/************************************************/

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};


void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGhostManDlg 对话框



CGhostManDlg::CGhostManDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGhostManDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_nWidth = 15;
	m_nHeight = 15;
	m_nStartX = 0;
	m_nStartY = 0;

	m_bSetStart = FALSE;
	m_bSetEnd = FALSE;

	m_bHaveAStart = FALSE;
	m_bHaveAEnd = FALSE;

	m_nAvailableStartX = -1;
	m_nAvailableStartY = -1;

	m_nAvailableEndX = -1;
	m_nAvailableEndY = -1;

	m_bInternalShow = FALSE;
	m_bByStep = FALSE;
	m_bClickStep = FALSE;
	m_bFirstStep = FALSE;

	m_bHaveAResult = FALSE;
	m_bHaveARoad = FALSE;
	m_bleftButtonDown = FALSE;
	m_bNeedRepaint = FALSE;
	m_bInitGhostMan = TRUE;
	m_nAlgorithmIndex = 0;
	m_nExeCount = 0;

	m_nOriGridBottom = 0;
	m_nOriGridTop = 0;
	m_nOriGridLeft = 0;
	m_nOriGridRight = 0;

	m_nCurGridLeft = 0;
	m_nCurGridBottom = 0;
	m_nCurGridTop = 0;
	m_nCurGridRight = 0;
	m_nCurPandaIndex = 0;

	m_nIDAGridStartX = 0;
	m_nIDAGridStartY = 0;

	m_nIDACurGridX = 0;
	m_nIDACurGridY = 0;

	m_nHidedPandaIndex = 0;
	m_nFlickerIndex = 0; 
	m_bInitSquared = FALSE;

	memcpy(g_NewMaze, g_maze, sizeof(int)*MAXX*MAXY);
}

void CGhostManDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_SETSTART, m_btnSetStart);
	DDX_Control(pDX, IDC_STATIC_SETEND, m_btnSetEnd);
	DDX_Control(pDX, IDC_STATIC_MIN, m_btnMin);
	DDX_Control(pDX, IDC_STATIC_CLOSE, m_btnClose);
	DDX_Control(pDX, IDC_STATIC_ASTAR, m_btnAStar);
	DDX_Control(pDX, IDC_STATIC_BFS, m_btnBFS);
	DDX_Control(pDX, IDC_STATIC_DFS, m_btnDFS);
	DDX_Control(pDX, IDC_STATIC_IDASTAR, m_btnIDAStar);
	DDX_Control(pDX, IDC_STATIC_ACO, m_btnSA);
	DDX_Control(pDX, IDC_STATIC_INIT, m_btnInit);
	DDX_Control(pDX, IDC_STATIC_EXEC, m_btnExec);
	DDX_Control(pDX, IDC_STATIC_STEP, m_btnStep);
	DDX_Control(pDX, IDC_STATIC_DYNAMIC, m_btnDynamic);
	DDX_Control(pDX, IDC_STATIC_STATIC, m_btnST);
	DDX_Control(pDX, IDC_STATIC_PANDA1, m_btnPanda1);
	DDX_Control(pDX, IDC_STATIC_PANDA2, m_btnPanda2);
	DDX_Control(pDX, IDC_STATIC_PANDA3, m_btnPanda3);
	DDX_Control(pDX, IDC_STATIC_PANDA4, m_btnPanda4);
	DDX_Control(pDX, IDC_STATIC_PANDA5, m_btnPanda5);
	DDX_Control(pDX, IDC_STATIC_PANDA6, m_btnPanda6);
	DDX_Control(pDX, IDC_STATIC_PANDA7, m_btnPanda7);
	DDX_Control(pDX, IDC_STATIC_PANDA8, m_btnPanda8);
	DDX_Control(pDX, IDC_STATIC_PANDA9, m_btnPanda9);
}

BEGIN_MESSAGE_MAP(CGhostManDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_MOVE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_MENU_EXIT, &CGhostManDlg::OnMenuExit)
	ON_STN_CLICKED(IDC_STATIC_SETSTART, &CGhostManDlg::OnStnClickedStaticSetstart)
	ON_STN_CLICKED(IDC_STATIC_SETEND, &CGhostManDlg::OnStnClickedStaticSetend)
	ON_STN_CLICKED(IDC_STATIC_CLOSE, &CGhostManDlg::OnStnClickedStaticClose)
	ON_STN_CLICKED(IDC_STATIC_MIN, &CGhostManDlg::OnStnClickedStaticMin)
	ON_STN_CLICKED(IDC_STATIC_MAX, &CGhostManDlg::OnStnClickedStaticMax)
	ON_STN_CLICKED(IDC_STATIC_ASTAR, &CGhostManDlg::OnStnClickedStaticAstar)
	ON_STN_CLICKED(IDC_STATIC_DYNAMIC, &CGhostManDlg::OnStnClickedStaticDynamic)
	ON_STN_CLICKED(IDC_STATIC_INIT, &CGhostManDlg::OnStnClickedStaticInit)
	ON_STN_CLICKED(IDC_STATIC_EXEC, &CGhostManDlg::OnStnClickedStaticExec)
	ON_STN_CLICKED(IDC_STATIC_STEP, &CGhostManDlg::OnStnClickedStaticStep)
	ON_STN_CLICKED(IDC_STATIC_STATIC, &CGhostManDlg::OnStnClickedStaticStatic)
	ON_STN_CLICKED(IDC_STATIC_BFS, &CGhostManDlg::OnStnClickedStaticBfs)
	ON_STN_CLICKED(IDC_STATIC_DFS, &CGhostManDlg::OnStnClickedStaticDfs)
	ON_STN_CLICKED(IDC_STATIC_IDASTAR, &CGhostManDlg::OnStnClickedStaticIdastar)
	ON_STN_CLICKED(IDC_STATIC_ACO, &CGhostManDlg::OnStnClickedStaticSA)
	ON_MESSAGE(WM_REPAINT_GRID, &CGhostManDlg::OnRepaintGrid)
	ON_MESSAGE(WM_PAINT_PANDA,&CGhostManDlg::OnPaintPanda)
END_MESSAGE_MAP()


// CGhostManDlg 消息处理程序

BOOL CGhostManDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

//	SetWindowPos(NULL, 0, 0, 100, 50, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);
	GetDlgItem(IDC_STATIC_PIC)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_MAX)->EnableWindow(FALSE);

	for (int i = 1; i < 10; i++)
	{
		GetDlgItem(1033 + i)->ShowWindow(SW_HIDE);
	}

	CRect rc;
	GetDlgItem(IDC_STATIC_PIC)->GetWindowRect(rc);
	ScreenToClient(rc);//转化为对话框上的相对位置  
	m_nOriGridTop = rc.top;
	m_nOriGridBottom = rc.bottom;
	m_nOriGridLeft = rc.left;
	m_nOriGridRight = rc.right;

	m_nCurGridTop = m_nOriGridTop;
	m_nCurGridBottom = m_nOriGridBottom;
	m_nCurGridLeft = m_nOriGridLeft;
	m_nCurGridRight = m_nOriGridRight;
	
	CRect rect;
	GetDlgItem(IDC_STATIC_PANDA3)->GetWindowRect(rect);
	ScreenToClient(rect);

	m_nIDAGridStartX = rect.right + 69;
	m_nIDAGridStartY = rect.top;

	for (int i = 1; i < 10; i++)
	{
		GetDlgItem(1033 + i)->GetWindowRect(m_rcPanda[i - 1]);
		ScreenToClient(m_rcPanda[i - 1]);
	}

	SetTimer(IDT_DELAY_DRAWGRID, 30, NULL);
	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGhostManDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGhostManDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		if (m_nAlgorithmIndex <= 3)
		{
			DrawGrid();
			DrawCurMazeColor();
		}
		else
		{
	//		DrawInitDerrick();
		}
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGhostManDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGhostManDlg::OnMenuExit()
{
	// TODO:  在此添加命令处理程序代码
	SendMessage(WM_CLOSE);
}

void CGhostManDlg::DrawGrid()
{
	CClientDC dc(this); //使用这个可以更改颜色和线条  
	//获得线的颜色颜色  
//	color = m_btTableLineColor.Color;//已经在初始化函数里面赋值  

	//获得线的风格  
//	int iDrawType = 0;
//	iDrawType = atoi(szLineTypeDraw);

	//设置线的画笔"风格"和"颜色"还有"粗细"  
	CPen pen(PS_SOLID, 1, RGB(255,255,255)); //画笔  
	CPen* pOldPen = dc.SelectObject(&pen);//画笔和画线区连接  

	CRect rect;
	//以下两句讲获得控件在屏幕中的位置  
	CWnd* pWnd = GetDlgItem(IDC_STATIC_PIC);
	if (pWnd == NULL)
		return;
	pWnd->GetWindowRect(&rect);  //获取控件相对于屏幕的位置,这个控件必须隐藏  
	ScreenToClient(rect);//转化为对话框上的相对位置  

	CRect rc;
	GetWindowRect(rc);
	if (m_bInitGhostMan)
	{
		rect.bottom += 2;
		rect.right -= 5;
		GetDlgItem(IDC_STATIC_PIC)->MoveWindow(rect);

		m_bInitGhostMan = FALSE;
	}
	else
	{

	}
	

	m_nStartX = rect.left;
	m_nStartY = rect.top;

	//开始画线  
	//TOP   

	dc.MoveTo(rect.left, rect.top); // [0,0]  
	dc.LineTo(rect.right, rect.top);

	//LEFT   
	dc.MoveTo(rect.left, rect.top);//从0开始为起始坐标  
	dc.LineTo(rect.left, rect.bottom);

	int xValue = 1;
	int iCount = 20;
	//画中间6条横行  
	for (int i = 1; i <= iCount; i++)
	{
		dc.MoveTo(rect.left, rect.top + xValue + m_nHeight*i); // [0,0]  
		dc.LineTo(rect.right, rect.top + xValue + m_nHeight*i);
		xValue = i + 1;
	}

	xValue = 1;
	iCount = 40;
	for (int i = 1; i <= iCount; i++)
	{
		dc.MoveTo(rect.left + xValue + m_nWidth*i, rect.top); // [0,0]  
		dc.LineTo(rect.left + xValue + m_nWidth*i, rect.bottom);
		xValue = i + 1;
	}
	//画笔刷新  
	dc.SelectObject(pOldPen);  //[可以不需要]  
	UpdateData(FALSE);
	
}

void CGhostManDlg::InitBFStatus()
{
	memset(S, 0, sizeof(S));
	memset(vis, 0, sizeof(vis));
}
void CGhostManDlg::InitDFStatus()
{
	finded = false;
	while (!sta.empty()){
		sta.pop();
	}
	memset(vis, 0, sizeof(vis));
}

void CGhostManDlg::InitAstartatus()
{
	memset(S, 0, sizeof(S));
	memset(vis, 0, sizeof(vis));
}
void CGhostManDlg::InitIDAstarstatus()
{
	memset(s.maze, 0, sizeof(s.maze));
	ok = 0; limit = 1;
	for (int i = 0; i < 3; ++i){
		for (int j = 0; j < 3; ++j){
			s.maze[i][j] = g_Squared[i][j];
			if (!g_Squared[i][j]){
				s.x = i;
				s.y = j;
			}
		}
	}
}

void CGhostManDlg::InitStatus()			//初始化保留了以前有的起点和终点
{
	m_bSetStart = FALSE;
	m_bSetEnd = FALSE;
	m_bInternalShow = FALSE;
	m_bByStep = FALSE;
	m_bClickStep = FALSE;
	m_bFirstStep = FALSE;
	m_bHaveARoad = FALSE;
}

void CGhostManDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (point.x < 775 && point.y <100)
	{ 
		this->m_bleftButtonDown = TRUE;
		this->m_mousePoint = CPoint(point);
	}
	int x = (point.x - m_nStartX) / (m_nWidth + 1);
	int y = (point.y - m_nStartY) / (m_nHeight + 1);

	if (x >= MAXY || x < 0 || y >= MAXX || y < 0)
	{
		return;
	}
	CClientDC dc(this);
	
	if (m_nAlgorithmIndex == 4)
	{ 
	}
	else if (m_nAlgorithmIndex <= 3)
	{
		CRect rect;
		GetDlgItem(IDC_STATIC_PIC)->GetWindowRect(&rect); //screen坐标系  
		ScreenToClient(&rect);

		if (m_bSetEnd)
		{
			if (g_NewMaze[y][x] == -1)
			{
				MessageBox(L"Don't Choose A obstacle", L"Error");
				return;
			}
			dc.FillSolidRect(m_nStartX + x*(m_nWidth + 1) + 1, m_nStartY + y*(m_nHeight + 1) + 1, m_nWidth, m_nHeight, RGB(191, 63, 170));
			m_bSetEnd = FALSE;
			m_bHaveAEnd = TRUE;

			m_nAvailableEndX = x;
			m_nAvailableEndY = y;
			ex = y, ey = x;

			m_btnSetEnd.m_nClicked = 0;
			HINSTANCE hIns = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_BITMAP_SETEND_NORMAL), RT_GROUP_ICON);
			HBITMAP   hBmp = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BITMAP_SETEND_NORMAL));
			m_btnSetEnd.SetBitmap(hBmp);
			return;
		}
		else if (m_bSetStart)
		{
			if (g_NewMaze[y][x] == -1)
			{
				MessageBox(L"Don't Choose A obstacle", L"Error");
				return;
			}
			dc.FillSolidRect(m_nStartX + x*(m_nWidth + 1) + 1, m_nStartY + y*(m_nHeight + 1) + 1, m_nWidth, m_nHeight, RGB(191, 63, 63));
			m_bSetStart = FALSE;
			m_bHaveAStart = TRUE;
			m_nAvailableStartX = x;
			m_nAvailableStartY = y;

			sx = y, sy = x;

			m_btnSetStart.m_nClicked = 0;
			HINSTANCE hIns = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_BITMAP_SETSTART_NORMAL), RT_GROUP_ICON);
			HBITMAP   hBmp = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BITMAP_SETSTART_NORMAL));
			m_btnSetStart.SetBitmap(hBmp);

			return;
		}

		if ((m_nAvailableStartX == x && m_nAvailableStartY == y) || (m_nAvailableEndX == x && m_nAvailableEndY == y))
		{
			MessageBox(L"Don't Touch me", L"Error");
			return;
		}
		switch (g_NewMaze[y][x])
		{
		case -1:
			g_NewMaze[y][x] = 1;
			dc.FillSolidRect(m_nStartX + x*(m_nWidth + 1) + 1, m_nStartY + y*(m_nHeight + 1) + 1, m_nWidth, m_nHeight, RGB(244, 241, 241));
			break;
		case 1:
			g_NewMaze[y][x] = 4;
			dc.FillSolidRect(m_nStartX + x*(m_nWidth + 1) + 1, m_nStartY + y*(m_nHeight + 1) + 1, m_nWidth, m_nHeight, RGB(191, 225, 184));
			break;
		case 4:
			g_NewMaze[y][x] = 3;
			dc.FillSolidRect(m_nStartX + x*(m_nWidth + 1) + 1, m_nStartY + y*(m_nHeight + 1) + 1, m_nWidth, m_nHeight, RGB(230, 230, 179));
			break;
		case 3:
			g_NewMaze[y][x] = 2;
			dc.FillSolidRect(m_nStartX + x*(m_nWidth + 1) + 1, m_nStartY + y*(m_nHeight + 1) + 1, m_nWidth, m_nHeight, RGB(140, 191, 217));
			break;
		case 2:
			g_NewMaze[y][x] = -1;
			dc.FillSolidRect(m_nStartX + x*(m_nWidth + 1) + 1, m_nStartY + y*(m_nHeight + 1) + 1, m_nWidth, m_nHeight, RGB(139, 174, 133));
			break;
		}

		if (m_bHaveARoad)
		{
			DrawCurMazeColor();
			DrawGrid();
			OnStnClickedStaticExec();
		}
	}
	else if (m_nAlgorithmIndex == 5)
	{
		switch (g_SaNewMaze[y][x])
		{
		case 1:
			g_SaNewMaze[y][x] = 2;
			dc.FillSolidRect(m_nStartX + x*(m_nWidth + 1) + 1,
				m_nStartY + y*(m_nHeight + 1) + 1, m_nWidth, m_nHeight, RGB(255, 0, 0));
			break;
		case 2:
			g_SaNewMaze[y][x] = 1;
			dc.FillSolidRect(m_nStartX + x*(m_nWidth + 1) + 1,
				m_nStartY + y*(m_nHeight + 1) + 1, m_nWidth, m_nHeight, RGB(205, 191, 179));
			break;
		}

		if (m_bHaveAResult)
		{
			Final_SA();
			SetTimer(IDT_DELAY_FLICKER, 100, NULL);
		}

	}
	

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CGhostManDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	this->m_bleftButtonDown = FALSE;
	if (m_nAlgorithmIndex <= 3)
	{ 
		DrawGrid();
		DrawCurMazeColor();
	}
	else if (m_nAlgorithmIndex == 5)
	{
		DrawNewSAMaze();
	}
	
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CGhostManDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	if (this->m_bleftButtonDown)
	{
		/// 鼠标左键按下时，可以拖动窗体  
		CPoint pointChanged = point - (this->m_mousePoint);
		CRect rect;
		this->GetWindowRect(&rect);
		this->SetWindowPos(NULL, rect.left + pointChanged.x, rect.top + pointChanged.y, 
			rect.Width(), rect.Height(), 0);
	}
	CDialogEx::OnMouseMove(nFlags, point);
}

void CGhostManDlg::OnMouseLeave()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	this->m_bleftButtonDown = FALSE;
	CDialogEx::OnMouseLeave();
}

void CGhostManDlg::DrawAColor(int nx, int ny,COLORREF color)
{
	CClientDC dc(this);
	dc.FillSolidRect(m_nStartX + nx*(m_nWidth + 1) + 1, m_nStartY + ny*(m_nHeight + 1) + 1, m_nWidth, m_nHeight, color);
}

void CGhostManDlg::DrawInitMazeColor()
{
	
	for (int i = 0; i < MAXY; i++)
	{
		for (int j = 0; j < MAXX; j++)
		{
			switch (g_maze[j][i])
			{
			case 1:
				DrawAColor(i, j, RGB(244, 241, 241));
					break; 
			case -1:
				DrawAColor(i, j, RGB(139, 174, 133));
					break;
			case 2:
				DrawAColor(i, j, RGB(140, 191, 217));
					break;
			case 3:
				DrawAColor(i, j, RGB(230, 230, 179));
					break;
			case 4:
				DrawAColor(i, j, RGB(191, 225, 184));
					break;
			}
		}
	}
	CClientDC dc(this);
	if (m_bHaveAStart)
	{
		dc.FillSolidRect(m_nStartX + m_nAvailableStartX*(m_nWidth + 1) + 1, m_nStartY + m_nAvailableStartY*(m_nHeight + 1) + 1, m_nWidth, m_nHeight, RGB(191, 63, 63));
		m_bSetStart = FALSE;
		m_bHaveAStart = TRUE;
	}
	if (m_bHaveAEnd)
	{
		dc.FillSolidRect(m_nStartX + m_nAvailableEndX*(m_nWidth + 1) + 1, m_nStartY + m_nAvailableEndY*(m_nHeight + 1) + 1, m_nWidth, m_nHeight, RGB(191, 63, 170));
		m_bSetEnd = FALSE;
		m_bHaveAEnd = TRUE;
	}
}
void CGhostManDlg::DrawInitSAMaze()
{
	for (int i = 0; i < MAXY; i++)
	{
		for (int j = 0; j < MAXX; j++)
		{
			switch (g_SaMaze[j][i])
			{
			case 1:
				DrawAColor(i, j, RGB(205, 191, 179));
				break;
			case 2:
				DrawAColor(i, j, RGB(255, 0, 0));
				break;
			}
		}
	}
}

void CGhostManDlg::DrawNewSAMaze()
{
	for (int i = 0; i < MAXY; i++)
	{
		for (int j = 0; j < MAXX; j++)
		{
			switch (g_SaNewMaze[j][i])
			{
			case 1:
				DrawAColor(i, j, RGB(205, 191, 179));
				break;
			case 2:
				DrawAColor(i, j, RGB(255, 0, 0));
				break;
			}
		}
	}
}



void CGhostManDlg::DrawCurMazeColor()
{
	for (int i = 0; i < MAXY; i++)
	{
		for (int j = 0; j < MAXX; j++)
		{
			switch (g_NewMaze[j][i])
			{
			case 1:
				DrawAColor(i, j, RGB(244, 241, 241));
				break;
			case -1:
				DrawAColor(i, j, RGB(139, 174, 133));
				break;
			case 2:
				DrawAColor(i, j, RGB(140, 191, 217));
				break;
			case 3:
				DrawAColor(i, j, RGB(230, 230, 179));
				break;
			case 4:
				DrawAColor(i, j, RGB(191, 225, 184));
				break;
			}
		}
	}
	CClientDC dc(this);
	if (m_bHaveAStart)
	{
		dc.FillSolidRect(m_nStartX + m_nAvailableStartX*(m_nWidth + 1) + 1, m_nStartY + m_nAvailableStartY*(m_nHeight + 1) + 1, m_nWidth, m_nHeight, RGB(191, 63, 63));
		m_bSetStart = FALSE;
		m_bHaveAStart = TRUE;
	}
	if (m_bHaveAEnd)
	{
		dc.FillSolidRect(m_nStartX + m_nAvailableEndX*(m_nWidth + 1) + 1, m_nStartY + m_nAvailableEndY*(m_nHeight + 1) + 1, m_nWidth, m_nHeight, RGB(191, 63, 170));
		m_bSetEnd = FALSE;
		m_bHaveAEnd = TRUE;
	}
	if (m_bHaveARoad)
	{
		CPoint Start;
		CPoint Next;

		Next = GetMazeCenter(Out_Path[0][0], Out_Path[0][1]);

		CClientDC dc(this);
		CPen pen(PS_SOLID, 5, RGB(186, 156, 202));
		dc.SelectObject(&pen);

		for (int i = 1; i <= Path_Len; ++i){
			Start = GetMazeCenter(Out_Path[i][0], Out_Path[i][1]);

			dc.MoveTo(Next.x, Next.y);
			dc.LineTo(Start.x, Start.y);

			Next = Start;
		}
	}
}

void CGhostManDlg::OnStnClickedStaticSetstart()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_nAlgorithmIndex >= 4)
	{
		MessageBox(L"当前算法不要求设置起点", L"Error");
		return;
	}
	DrawGrid();
	DrawCurMazeColor();
	HINSTANCE hIns = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_BITMAP_SETSTART_CLICK), RT_GROUP_ICON);
	HBITMAP   hBmp = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BITMAP_SETSTART_CLICK));
	m_btnSetStart.SetBitmap(hBmp);
	m_btnSetStart.m_nClicked = 1;

	if (m_bHaveAStart)
	{
		CClientDC dc(this);
		switch (g_NewMaze[m_nAvailableStartY][m_nAvailableStartX])
		{
		case 1:
			DrawAColor(m_nAvailableStartX, m_nAvailableStartY, RGB(244, 241, 241));
			break;
		case -1:
			DrawAColor(m_nAvailableStartX, m_nAvailableStartY, RGB(139, 174, 133));
			break;
		case 2:
			DrawAColor(m_nAvailableStartX, m_nAvailableStartY, RGB(140, 191, 217));
			break;
		case 3:
			DrawAColor(m_nAvailableStartX, m_nAvailableStartY, RGB(230, 230, 179));
			break;
		case 4:
			DrawAColor(m_nAvailableStartX, m_nAvailableStartY, RGB(191, 225, 184));
			break;
		}
		m_bHaveAStart = FALSE;
	}
	m_bSetStart = TRUE;
}


void CGhostManDlg::OnStnClickedStaticSetend()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_nAlgorithmIndex >= 4)
	{
		MessageBox(L"当前算法不要求设置终点", L"Error");
		return;
	}
	DrawGrid();
	DrawCurMazeColor();
	HINSTANCE hIns = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_BITMAP_SETEND_CLICK), RT_GROUP_ICON);
	HBITMAP   hBmp = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BITMAP_SETEND_CLICK));
	m_btnSetEnd.SetBitmap(hBmp);
	m_btnSetEnd.m_nClicked = 1;

	if (m_bHaveAEnd)
	{
		CClientDC dc(this);
		switch (g_NewMaze[m_nAvailableEndY][m_nAvailableEndX])
		{
		case 1:
			DrawAColor(m_nAvailableEndX, m_nAvailableEndY, RGB(244, 241, 241));
			break;
		case -1:
			DrawAColor(m_nAvailableEndX, m_nAvailableEndY, RGB(139, 174, 133));
			break;
		case 2:
			DrawAColor(m_nAvailableEndX, m_nAvailableEndY, RGB(140, 191, 217));
			break;
		case 3:
			DrawAColor(m_nAvailableEndX, m_nAvailableEndY, RGB(230, 230, 179));
			break;
		case 4:
			DrawAColor(m_nAvailableEndX, m_nAvailableEndY, RGB(191, 225, 184));
			break;
		}
		m_bHaveAEnd = FALSE;
	}
	m_bSetEnd = TRUE;
}

bool CGhostManDlg::Check(int x, int y){
	if (x < 0 || y < 0 || x >= MAXX || y >= MAXY){		//地图越界
		return false;
	}
	if (g_NewMaze[x][y] == wall || vis[x][y] == visited){		//墙壁检测
		return false;
	}
	return true;
}


bool CGhostManDlg::BFS(){
	InitBFStatus();
	queue<Point> q;
	S[sx][sy].time = 0;
	S[sx][sy].x = sx;
	S[sx][sy].y = sy;
	vis[sx][sy] = visited;
	q.push(Point(sx, sy, 0, 0));
	while (!q.empty()){
		Point u, v;
		u = q.front();
		q.pop();
		if (u.x == ex && u.y == ey){
			Path_Len = u.deep;
			Time = u.time;
			Deep = u.deep;
			Get_Path();
			//ShowResult(Time, Deep, 0);
			return true;
		}
		for (int i = 0; i < 4; ++i){
			v = u;
			v.x += dir_x[i];
			v.y += dir_y[i];
			if (!Check(v.x, v.y)){
				continue;
			}
			S[v.x][v.y].x = v.x;
			S[v.x][v.y].y = v.y;
			S[v.x][v.y].pre_x = u.x;
			S[v.x][v.y].pre_y = u.y;
			v.deep += 1;
			if (g_NewMaze[v.x][v.y] == road || g_NewMaze[v.x][v.y] == grass){
				v.time += 1;
			}
			else if (g_NewMaze[v.x][v.y] == water){
				v.time += 2;
			}
			else if (g_NewMaze[v.x][v.y] == swamp){
				v.time += 3;
			}
			vis[v.x][v.y] = visited;
			q.push(v);
		}
	}

	return false;
}

void CGhostManDlg::Final_BFS()
{
	if (BFS())
	{
		m_bHaveARoad = TRUE;
		CPoint Start;
		CPoint Next;

		Next = GetMazeCenter(Out_Path[0][0], Out_Path[0][1]);

		CClientDC dc(this);
		CPen pen(PS_SOLID, 5, RGB(186, 156, 202));
		dc.SelectObject(&pen);

		for (int i = 1; i <= Path_Len; ++i){
			Start = GetMazeCenter(Out_Path[i][0], Out_Path[i][1]);
			dc.MoveTo(Next.x, Next.y);
			dc.LineTo(Start.x, Start.y);
			Next = Start;
		}
	}
	else
	{
		MessageBox(L"没卵用", L"Error");
	}
}

void CGhostManDlg::Final_DFS()
{
	InitDFStatus();
	Out_Path[0][0] = sx;
	Out_Path[0][1] = sy;
	vis[sx][sy] = visited;
	DFS();
	if (finded){
	//	printf("time = %d\ndeep = %d\n", Time, Deep);
	//	printf("start at (%d,%d)\n", sx, sy);
		CPoint Start;
		CPoint Next;

		Next = GetMazeCenter(sx, sy);

		CClientDC dc(this);
		CPen pen(PS_SOLID, 5, RGB(186, 156, 202));
		dc.SelectObject(&pen);

		for (int i = 1; i <= Path_Len; ++i){
			Start = GetMazeCenter(Out_Path[i][0], Out_Path[i][1]);
			dc.MoveTo(Next.x, Next.y);
			dc.LineTo(Start.x, Start.y);
			Next = Start;
		}
 	}
}

void CGhostManDlg::Final_ASTAR()
{
	if (Astar())
	{
		m_bHaveARoad = TRUE;

		CPoint Start;
		CPoint Next;

		Next = GetMazeCenter(Out_Path[0][0],Out_Path[0][1]);

		CClientDC dc(this);
		CPen pen(PS_SOLID, 5, RGB(186, 156, 202));
		dc.SelectObject(&pen);

		for (int i = 1; i <= Path_Len; ++i){
			Start = GetMazeCenter(Out_Path[i][0], Out_Path[i][1]);

			dc.MoveTo(Next.x, Next.y);
			dc.LineTo(Start.x, Start.y);

			Next = Start;
		}
	}
	else
	{
		MessageBox(L"没卵用", L"Error");
	}
}
void CGhostManDlg::Final_IDAStar()
{
}


void CGhostManDlg::Get_Path(){
	while ( !Path.empty() ){
		Path.pop();
	}
	int xx = ex, yy = ey;
	while (true){
		pair<int, int> t;
		t.first = xx;
		t.second = yy;
		Path.push(t);
		if (xx == sx && yy == sy){
			break;
		}
		int t1 = xx, t2 = yy;
		xx = S[t1][t2].pre_x;
		yy = S[t1][t2].pre_y;
	}
	for (int i = 0; i <= Path_Len; ++i )
	{
		pair<int, int> t;
		t = Path.top();
		Path.pop();
		Out_Path[i][0] = t.first;
		Out_Path[i][1] = t.second;
	}
}

CPoint CGhostManDlg::GetMazeCenter(int x, int y)
{
	CPoint p;
	int nx = 0;
	nx = m_nStartX + y * (m_nWidth + 1) + 1;	//这是计算第 x+1 格子的起点x坐标
	nx += m_nWidth / 2;							//算出中心点坐标

	int ny = m_nStartY + x * (m_nHeight + 1) + 1;	//这是计算第 y+1 格子的起点y坐标
	ny += m_nHeight / 2;

	p.x = nx;
	p.y = ny;
	return p;
}

void CGhostManDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
		case IDT_DELAY_DRAWGRID:
		{
			InitDC();
			DrawDC();
			DrawGrid();
			DrawInitMazeColor();

			KillTimer(IDT_DELAY_DRAWGRID);
			break;
		}
		case IDT_DELAY_CLOSEGRID:
		{
			if (m_bInitSquared)
			{
				m_nCurGridTop += 5;
				m_nCurGridBottom -= 5;

				if (m_nCurGridBottom > m_nCurGridTop - 5)
				{
					if (!GetDlgItem(IDC_STATIC_TOP)->IsWindowVisible())
					{
						GetDlgItem(IDC_STATIC_TOP)->ShowWindow(SW_SHOW);
						GetDlgItem(IDC_STATIC_BOTTOM)->ShowWindow(SW_SHOW);
					}



					GetDlgItem(IDC_STATIC_TOP)->MoveWindow(m_nCurGridLeft, m_nOriGridTop,
						m_nOriGridRight - m_nOriGridLeft, m_nCurGridTop - m_nOriGridTop);
					CDC* pDC = GetDlgItem(IDC_STATIC_TOP)->GetDC();
					pDC->BitBlt(0, 0, m_nOriGridRight - m_nOriGridLeft, m_nCurGridTop - m_nOriGridTop,
						&m_Dc, m_nCurGridLeft, m_nOriGridTop, SRCCOPY);
					GetDlgItem(IDC_STATIC_BOTTOM)->MoveWindow(m_nCurGridLeft, m_nCurGridBottom,
						m_nOriGridRight - m_nOriGridLeft, m_nOriGridBottom - m_nCurGridBottom + 2);

					pDC = GetDlgItem(IDC_STATIC_BOTTOM)->GetDC();
					pDC->BitBlt(0, 0, m_nOriGridRight - m_nOriGridLeft, m_nOriGridBottom - m_nCurGridBottom + 5,
						&m_Dc, m_nCurGridLeft, m_nCurGridBottom, SRCCOPY);
					pDC = GetDC();
					pDC->BitBlt(m_nCurGridLeft, m_nCurGridTop, m_nOriGridRight - m_nOriGridLeft, m_nCurGridBottom - m_nCurGridTop,
						&m_GridDc, m_nCurGridLeft, m_nCurGridTop, SRCCOPY);
				}
				else
				{
					m_bInitSquared = FALSE;
					m_nCurGridTop = m_nOriGridTop;
					m_nCurGridBottom = m_nOriGridBottom;
					GetDlgItem(IDC_STATIC_TOP)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_STATIC_BOTTOM)->ShowWindow(SW_HIDE);

					GetDlgItem(IDC_STATIC_TOP)->MoveWindow(m_nCurGridLeft, m_nOriGridTop, 0, 0);
					GetDlgItem(IDC_STATIC_BOTTOM)->MoveWindow(m_nCurGridLeft, m_nOriGridBottom, 0, 0);

					CDC* pDC = GetDC();
					pDC->BitBlt(m_nStartX, m_nStartY, m_nOriGridRight - m_nOriGridLeft, m_nCurGridBottom - m_nOriGridTop + 5,
						&m_Dc, m_nCurGridLeft, m_nCurGridBottom, SRCCOPY);
					SetTimer(IDT_DELAY_DRAWIDAPANDA, 200, NULL);
					SetTimer(IDT_DELAY_DRAWIDAGRID, 200, NULL);
					KillTimer(IDT_DELAY_CLOSEGRID);
				}
			}
			
			break;
		}
		case IDT_DELAY_DRAWIDAPANDA:
		{
			GetDlgItem(IDC_STATIC_TOP)->MoveWindow(m_nStartX, m_nStartY, 0, 0);
			GetDlgItem(IDC_STATIC_BOTTOM)->MoveWindow(m_nStartX, m_nOriGridBottom, 0, 0);
			MovePandaToInit();
			m_nCurPandaIndex++;
			if (m_nCurPandaIndex >= 1 && m_nCurPandaIndex <= 5)
			{
				int nBase = IDC_STATIC_PANDA1 - 1;
				if (*((int*)g_Squared + m_nCurPandaIndex - 1 ) != 0)
				{
					
					HINSTANCE hIns = AfxFindResourceHandle(
						MAKEINTRESOURCE(215 + *((int*)g_Squared + m_nCurPandaIndex - 1)), RT_GROUP_ICON);
					HBITMAP   hBmp = ::LoadBitmap(hIns,
						MAKEINTRESOURCE(215 + *((int*)g_Squared + m_nCurPandaIndex - 1)));
					((CStatic*)GetDlgItem(nBase + m_nCurPandaIndex))->SetBitmap(hBmp);
					GetDlgItem(nBase + m_nCurPandaIndex)->ShowWindow(SW_SHOW);
					if (m_nCurPandaIndex == 5)
						return;
				}
				else
				{
					m_nHidedPandaIndex = m_nCurPandaIndex - 1;
				}
	
				if (*((int*)g_Squared + 9 - m_nCurPandaIndex) != 0)
				{
					HINSTANCE hIns = AfxFindResourceHandle(
						MAKEINTRESOURCE(215 + *((int*)g_Squared + 9 - m_nCurPandaIndex)), RT_GROUP_ICON);
					HBITMAP   hBmp = ::LoadBitmap(hIns,
						MAKEINTRESOURCE(215 + *((int*)g_Squared + 9 - m_nCurPandaIndex)));
					((CStatic*)GetDlgItem(nBase + 10 - m_nCurPandaIndex))->SetBitmap(hBmp);
					GetDlgItem(nBase + 10 - m_nCurPandaIndex)->ShowWindow(SW_SHOW);
				}
				else
				{
					m_nHidedPandaIndex = 9 - m_nCurPandaIndex;
				}
			}
			else
			{
				m_nCurPandaIndex = 0;
				KillTimer(IDT_DELAY_DRAWIDAPANDA);
			}

			break;
			
		}
		case IDT_DELAY_DRAWIDAGRID:
		{
			if (m_nIDACurGridX >= 7 || m_nIDACurGridY >= 7)
			{
				m_nIDACurGridX = m_nIDACurGridY = 0;
				KillTimer(IDT_DELAY_DRAWIDAGRID);
			}
			
			CClientDC dc(this);
			switch (g_Derrick[2][m_nIDACurGridY])
			{
			case 1:
				{
					dc.FillSolidRect(m_nIDAGridStartX + m_nIDACurGridY * 41,
						m_nIDAGridStartY + 2 * 41, 41, 41, RGB(0, 255, 0));
					break; 
				}
			case 2:
				{
					dc.FillSolidRect(m_nIDAGridStartX + m_nIDACurGridY * 41,
						m_nIDAGridStartY + 2 * 41, 41, 41, RGB(7, 158, 239));
					break;
				}
			case 3:
				{
					dc.FillSolidRect(m_nIDAGridStartX + m_nIDACurGridY * 41,
						m_nIDAGridStartY + 2*41, 41, 41, RGB(255, 153, 0));
					break;
				}
			}
			switch (g_Derrick[4][m_nIDACurGridY])
			{
				case 1:
				{
					dc.FillSolidRect(m_nIDAGridStartX + m_nIDACurGridY * 41,
						m_nIDAGridStartY + 4 * 41, 41, 41, RGB(0, 255, 0));
					break;
				}
				case 2:
				{
					dc.FillSolidRect(m_nIDAGridStartX + m_nIDACurGridY * 41,
						m_nIDAGridStartY + 4 * 41, 41, 41, RGB(7, 158, 239));
					break;
				}
				case 3:
				{
					dc.FillSolidRect(m_nIDAGridStartX + m_nIDACurGridY * 41,
						m_nIDAGridStartY + 4 * 41, 41, 41, RGB(255, 153, 0));
					break;
				}
			}
			switch (g_Derrick[m_nIDACurGridX][2])
			{
				case 1:
				{
					dc.FillSolidRect(m_nIDAGridStartX + 2 * 41,
						m_nIDAGridStartY + m_nIDACurGridX * 41, 41, 41, RGB(0, 255, 0));
					break;
				}
				case 2:
				{
					dc.FillSolidRect(m_nIDAGridStartX + 2 * 41,
						m_nIDAGridStartY + m_nIDACurGridX * 41, 41, 41, RGB(7, 158, 239));
					break;
				}
				case 3:
				{
					dc.FillSolidRect(m_nIDAGridStartX + 2 * 41,
						m_nIDAGridStartY + m_nIDACurGridX * 41, 41, 41, RGB(255, 153, 0));
					break;
				}
			}
			switch (g_Derrick[m_nIDACurGridX][4])
			{
				case 1:
				{
					dc.FillSolidRect(m_nIDAGridStartX + 4 * 41,
						m_nIDAGridStartY + m_nIDACurGridX * 41, 41, 41, RGB(0, 255, 0));
					break;
				}
				case 2:
				{
					dc.FillSolidRect(m_nIDAGridStartX + 4 * 41,
						m_nIDAGridStartY + m_nIDACurGridX * 41, 41, 41, RGB(7, 158, 239));
					break;
				}
				case 3:
				{
					dc.FillSolidRect(m_nIDAGridStartX + 4 * 41,
						m_nIDAGridStartY + m_nIDACurGridX * 41, 41, 41, RGB(255, 153, 0));
					break;
				}
			}
			m_nIDACurGridX++;
			m_nIDACurGridY++;

			break;
		}
		case IDT_DELAY_REPAINT:
		{
			m_bNeedRepaint = FALSE;
			switch (m_nAlgorithmIndex)
			{
				case 1:
					OnStnClickedStaticAstar();
					break;
				case 2:
					OnStnClickedStaticBfs();
					break;
				case 3:
					OnStnClickedStaticDfs();
					break;
				case 5:
					OnStnClickedStaticSA();
					break;
			}
			KillTimer(IDT_DELAY_REPAINT);
			break;
		}
		case IDT_DELAY_FLICKER:
		{
			m_nFlickerTimer += 100;
			CClientDC dc(this);
			if (m_nFlickerTimer <= 2000)
			{
				switch (m_nFlickerIndex % 3)
				{
				case 0:
					dc.FillSolidRect(m_nStartX + PResult.x*(m_nWidth + 1) + 1, 
						m_nStartY + PResult.y*(m_nHeight + 1) + 1, m_nWidth, m_nHeight, RGB(0, 255, 0));
					break;
				case 1:
					dc.FillSolidRect(m_nStartX + PResult.x*(m_nWidth + 1) + 1,
						m_nStartY + PResult.y*(m_nHeight + 1) + 1, m_nWidth, m_nHeight, RGB(0, 0, 255));
					break;
				case 2:
					dc.FillSolidRect(m_nStartX + PResult.x*(m_nWidth + 1) + 1,
						m_nStartY + PResult.y*(m_nHeight + 1) + 1, m_nWidth, m_nHeight, RGB(0, 255, 255));
					break;
				}
				m_nFlickerIndex++;
			}
			else
			{
				m_nFlickerIndex = 0;
				m_nFlickerTimer = 0;
				KillTimer(IDT_DELAY_FLICKER);
			}
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


DWORD CGhostManDlg::ExpandAstarFunction(LPARAM lParam)
{
	CGhostManDlg* dlg = (CGhostManDlg*)lParam;
	if (dlg->ExAstar())
	{
		dlg->m_bHaveARoad = TRUE;
		CPoint Start;
		CPoint Next;

		Next = dlg->GetMazeCenter(Out_Path[0][0], Out_Path[0][1]);

		CClientDC dc(dlg);
		CPen pen(PS_SOLID, 5, RGB(186, 156, 202));
		dc.SelectObject(&pen);

		for (int i = 1; i <= Path_Len; ++i){
			Start = dlg->GetMazeCenter(Out_Path[i][0],Out_Path[i][1]);
			dc.MoveTo(Next.x, Next.y);
			dc.LineTo(Start.x, Start.y);
			Next = Start;

		}
	}

	dlg->m_bFirstStep = FALSE;
	dlg->m_bByStep = FALSE;
	dlg->m_bClickStep = FALSE;

	return 0;
}

DWORD CGhostManDlg::ExpandBFSFunction(LPARAM lParam)
{
	CGhostManDlg* dlg = (CGhostManDlg*)lParam;
	if (dlg->ExBFS())
	{
		dlg->m_bHaveARoad = TRUE;
		CPoint Start;
		CPoint Next;

		Next = dlg->GetMazeCenter(Out_Path[0][0], Out_Path[0][1]);

		CClientDC dc(dlg);
		CPen pen(PS_SOLID, 5, RGB(186, 156, 202));
		dc.SelectObject(&pen);

		for (int i = 1; i <= Path_Len; ++i){
			Start = dlg->GetMazeCenter(Out_Path[i][0], Out_Path[i][1]);
			dc.MoveTo(Next.x, Next.y);
			dc.LineTo(Start.x, Start.y);
			Next = Start;

		}
	}

	dlg->m_bFirstStep = FALSE;
	dlg->m_bByStep = FALSE;
	dlg->m_bClickStep = FALSE;

	return 0;
}
DWORD CGhostManDlg::ExpandIDAStarFunction(LPARAM lParam)
{
	CGhostManDlg* dlg = (CGhostManDlg*)lParam;
	int nBase = IDC_STATIC_PANDA1;
	int k = 0;
	dlg->InitDerrick();
	if (!dlg->IDA_check(s)){
	}
	else{
		if (!dlg->IDA_star(s))
		{
			return -1;
		}

		int nBase = IDC_STATIC_PANDA1;
		for (int i = 0; i < limit; ++i){

			switch (IDA_Path[i])
			{
			case 'r':
			{
				((CStatic*)dlg->GetDlgItem(nBase + dlg->m_nHidedPandaIndex))->ShowWindow(SW_SHOW);
				HINSTANCE hIns = AfxFindResourceHandle(
					MAKEINTRESOURCE(215 + *((int*)g_Squared + dlg->m_nHidedPandaIndex + 1)), RT_GROUP_ICON);
				HBITMAP   hBmp = ::LoadBitmap(hIns,
					MAKEINTRESOURCE(215 + *((int*)g_Squared + dlg->m_nHidedPandaIndex + 1)));
				((CStatic*)dlg->GetDlgItem(nBase + dlg->m_nHidedPandaIndex))->SetBitmap(hBmp);
				((CStatic*)dlg->GetDlgItem(nBase + dlg->m_nHidedPandaIndex + 1))->ShowWindow(SW_HIDE);

				int n = 0;
				n = *((int*)g_Squared + dlg->m_nHidedPandaIndex + 1);
				*((int*)g_Squared + dlg->m_nHidedPandaIndex + 1) = *((int*)g_Squared + dlg->m_nHidedPandaIndex);
				*((int*)g_Squared + dlg->m_nHidedPandaIndex) = n;
				dlg->m_nHidedPandaIndex += 1;

				break;
			}
			case 'd':
			{
				((CStatic*)dlg->GetDlgItem(nBase + dlg->m_nHidedPandaIndex))->ShowWindow(SW_SHOW);
				HINSTANCE hIns = AfxFindResourceHandle(
					MAKEINTRESOURCE(215 + *((int*)g_Squared + dlg->m_nHidedPandaIndex + 3)), RT_GROUP_ICON);
				HBITMAP   hBmp = ::LoadBitmap(hIns,
					MAKEINTRESOURCE(215 + *((int*)g_Squared + dlg->m_nHidedPandaIndex + 3)));
				((CStatic*)dlg->GetDlgItem(nBase + dlg->m_nHidedPandaIndex))->SetBitmap(hBmp);
				((CStatic*)dlg->GetDlgItem(nBase + dlg->m_nHidedPandaIndex + 3))->ShowWindow(SW_HIDE);

				int n = 0;
				n = *((int*)g_Squared + dlg->m_nHidedPandaIndex + 3);
				*((int*)g_Squared + dlg->m_nHidedPandaIndex + 3) = *((int*)g_Squared + dlg->m_nHidedPandaIndex);
				*((int*)g_Squared + dlg->m_nHidedPandaIndex) = n;

				dlg->m_nHidedPandaIndex += 3;
				break;
			}
			case 'l':
			{
				((CStatic*)dlg->GetDlgItem(nBase + dlg->m_nHidedPandaIndex))->ShowWindow(SW_SHOW);
				HINSTANCE hIns = AfxFindResourceHandle(
					MAKEINTRESOURCE(215 + *((int*)g_Squared + dlg->m_nHidedPandaIndex - 1)), RT_GROUP_ICON);
				HBITMAP   hBmp = ::LoadBitmap(hIns,
					MAKEINTRESOURCE(215 + *((int*)g_Squared + dlg->m_nHidedPandaIndex - 1)));
				((CStatic*)dlg->GetDlgItem(nBase + dlg->m_nHidedPandaIndex))->SetBitmap(hBmp);
				((CStatic*)dlg->GetDlgItem(nBase + dlg->m_nHidedPandaIndex - 1))->ShowWindow(SW_HIDE);
				int n = 0;
				n = *((int*)g_Squared + dlg->m_nHidedPandaIndex - 1);
				*((int*)g_Squared + dlg->m_nHidedPandaIndex - 1) = *((int*)g_Squared + dlg->m_nHidedPandaIndex);
				*((int*)g_Squared + dlg->m_nHidedPandaIndex) = n;

				dlg->m_nHidedPandaIndex -= 1;
				break;
			}
			case 'u':
			{
				((CStatic*)dlg->GetDlgItem(nBase + dlg->m_nHidedPandaIndex))->ShowWindow(SW_SHOW);
				HINSTANCE hIns = AfxFindResourceHandle(
					MAKEINTRESOURCE(215 + *((int*)g_Squared + dlg->m_nHidedPandaIndex - 3)), RT_GROUP_ICON);
				HBITMAP   hBmp = ::LoadBitmap(hIns,
					MAKEINTRESOURCE(215 + *((int*)g_Squared + dlg->m_nHidedPandaIndex - 3)));
				((CStatic*)dlg->GetDlgItem(nBase + dlg->m_nHidedPandaIndex))->SetBitmap(hBmp);
				((CStatic*)dlg->GetDlgItem(nBase + dlg->m_nHidedPandaIndex - 3))->ShowWindow(SW_HIDE);

				int n = 0;
				n = *((int*)g_Squared + dlg->m_nHidedPandaIndex - 3);
				*((int*)g_Squared + dlg->m_nHidedPandaIndex - 3) = *((int*)g_Squared + dlg->m_nHidedPandaIndex);
				*((int*)g_Squared + dlg->m_nHidedPandaIndex) = n;
				dlg->m_nHidedPandaIndex -= 3;
				break;
			}
			}
			dlg->Invalidate();
			Sleep(300);
		}

		dlg->m_btnPanda9.ShowWindow(SW_HIDE);
		dlg->PostMessage(WM_PAINT_PANDA);
	}
	return 0;
}

DWORD CGhostManDlg::ExpandDFSFunction(LPARAM lParam)
{
	CGhostManDlg* dlg = (CGhostManDlg*)lParam;
	if (dlg->ExDFS())
	{
		dlg->m_bHaveARoad = TRUE;
		CPoint Start;
		CPoint Next;

		Next = dlg->GetMazeCenter(sx, sy);

		CClientDC dc(dlg);
		CPen pen(PS_SOLID, 5, RGB(186, 156, 202));
		dc.SelectObject(&pen);

		for (int i = 1; i <= Path_Len; ++i){
			Start = dlg->GetMazeCenter(Out_Path[i][0], Out_Path[i][1]);
			dc.MoveTo(Next.x, Next.y);
			dc.LineTo(Start.x, Start.y);
			Next = Start;
		}
	}

	dlg->m_bFirstStep = FALSE;
	dlg->m_bByStep = FALSE;
	dlg->m_bClickStep = FALSE;

	return 0;
}

DWORD CGhostManDlg::RandIDAGridFunction(LPARAM lParam)
{
	CGhostManDlg* dlg = (CGhostManDlg*)lParam;
	dlg->RandIDAGrid();
	dlg->m_bInitSquared = TRUE;

	return 0;
}

bool CGhostManDlg::ExBFS()
{
	InitBFStatus();
	queue<Point> q;
	S[sx][sy].time = 0;
	S[sx][sy].x = sx;
	S[sx][sy].y = sy;
	vis[sx][sy] = visited;
	q.push(Point(sx, sy, 0, 0));

	while (!q.empty()){
		Point u, v;
		u = q.front();
		//u为当前点，置为黄色
		if ((u.x == sx && u.y == sy) || (u.x == ex && u.y == ey))
		{
		}
		else
		{
			CClientDC dc(this);
			dc.FillSolidRect(m_nStartX + u.y*(m_nWidth + 1) + 1,
				m_nStartY + u.x*(m_nHeight + 1) + 1, m_nWidth, m_nHeight, RGB(215, 233, 124));
			if (m_bInternalShow) Sleep(50);
		}
		
		q.pop();
		if (u.x == ex && u.y == ey){
			Path_Len = u.deep;
			Time = u.time;
			Deep = u.deep;
			Get_Path();
			//ShowResult(Time, Deep, 0);
			return true;
		}
		for (int i = 0; i < 4; ++i){
			v = u;
			v.x += dir_x[i];
			v.y += dir_y[i];
			if (!Check(v.x, v.y)){
				continue;
			}
			S[v.x][v.y].x = v.x;
			S[v.x][v.y].y = v.y;
			S[v.x][v.y].pre_x = u.x;
			S[v.x][v.y].pre_y = u.y;
			v.deep += 1;
			if (g_NewMaze[v.x][v.y] == road || g_NewMaze[v.x][v.y] == grass){
				v.time += 1;
			}
			else if (g_NewMaze[v.x][v.y] == water){
				v.time += 2;
			}
			else if (g_NewMaze[v.x][v.y] == swamp){
				v.time += 3;
			}
			vis[v.x][v.y] = visited;
			q.push(v);
			if ((v.x == sx && v.y == sy) || (v.x == ex && v.y == ey))
			{
			}
			else{
				CClientDC dc(this);
				dc.FillSolidRect(m_nStartX + v.y*(m_nWidth + 1) + 1,
					m_nStartY + v.x*(m_nHeight + 1) + 1, m_nWidth, m_nHeight, RGB(102, 137, 205));
				if (m_bInternalShow) Sleep(50);
			}

			//把4个点置为蓝色
			
		}
		if (m_bByStep)
		{
			while (1)
			{
				if (m_bClickStep)
				{
					m_bClickStep = FALSE;
					break;
				}
				else
				{
				}
			}
		}
		if ((u.x == sx && u.y == sy) || (u.x == ex && u.y == ey))
		{
		}
		else
		{
			CClientDC dc(this);
			dc.FillSolidRect(m_nStartX + u.y*(m_nWidth + 1) + 1,
				m_nStartY + u.x*(m_nHeight + 1) + 1, m_nWidth, m_nHeight, RGB(205, 191, 179));
			
			if(m_bInternalShow) Sleep(50);
		}
		//把u点置为棕色
	}

	return false;
}

int CGhostManDlg::h(Point p)
{
	return (abs(p.x - ex) + abs(p.y - ey));
}

bool CGhostManDlg::ExAstar(){
	InitAstartatus();
	priority_queue<Point> pq;
	vis[sx][sy] = visited;
	if (sx == ex && sy == ey){	//如果起点和终点重合 
		return true;
	}
	S[sx][sy].x = sx;
	S[sx][sy].y = sy;
	Point t(sx, sy, 0, 0);
	t.g = 0;
	t.h = h(t);
	t.f = t.h + t.g;
	pq.push(t);
	Point u, v;
	while (!pq.empty()){
		u = pq.top();
		pq.pop();
		if (u.x == ex && u.y == ey){
			Path_Len = u.deep;
			Time = u.time;
			Deep = u.deep;
			Get_Path();
			//ShowResult(Time, Deep, 0);
			return true;
		}
		//u为当前点，置为黄色
		if ((u.x == sx && u.y == sy) || (u.x == ex && u.y == ey))
		{
		}
		else
		{
			CClientDC dc(this);
			dc.FillSolidRect(m_nStartX + u.y*(m_nWidth + 1) + 1,
				m_nStartY + u.x*(m_nHeight + 1) + 1, m_nWidth, m_nHeight, RGB(215, 233, 124));
			if (m_bInternalShow) Sleep(50);
		}
		for (int i = 0; i < 4; ++i){
			v = u;
			v.x += dir_x[i];
			v.y += dir_y[i];
			if (!Check(v.x, v.y)) continue;
			vis[v.x][v.y] = visited;
			S[v.x][v.y].x = v.x;
			S[v.x][v.y].y = v.y;
			S[v.x][v.y].pre_x = u.x;
			S[v.x][v.y].pre_y = u.y;
			if (g_NewMaze[v.x][v.y] == road || g_NewMaze[v.x][v.y] == grass){
				v.time += 1;
				v.g += 1;
			}
			else if (g_NewMaze[v.x][v.y] == water){
				v.time += 2;
				v.g += 2;
			}
			else if (g_NewMaze[v.x][v.y] == swamp){
				v.time += 3;
				v.g += 3;
			}
			v.h = h(v);
			v.f = v.g + v.h;
			v.deep++;
			pq.push(v);
			if ((v.x == sx && v.y == sy) || (v.x == ex && v.y == ey))
			{
			}
			else{
				CClientDC dc(this);
				dc.FillSolidRect(m_nStartX + v.y*(m_nWidth + 1) + 1,
					m_nStartY + v.x*(m_nHeight + 1) + 1, m_nWidth, m_nHeight, RGB(102, 137, 205));
				if (m_bInternalShow) Sleep(50);
			}
		}
		if (m_bByStep)
		{
			while (1)
			{
				if (m_bClickStep)
				{
					m_bClickStep = FALSE;
					break;
				}
				else
				{
				}
			}
		}
		if ((u.x == sx && u.y == sy) || (u.x == ex && u.y == ey))
		{
		}
		else{
			CClientDC dc(this);
			dc.FillSolidRect(m_nStartX + u.y*(m_nWidth + 1) + 1,
				m_nStartY + u.x*(m_nHeight + 1) + 1, m_nWidth, m_nHeight, RGB(205, 191, 179));

			if (m_bInternalShow) Sleep(50);
		}
	}
	return false;
}


bool CGhostManDlg::Astar(){
	InitAstartatus();
	priority_queue<Point> pq;
	vis[sx][sy] = visited;
	if (sx == ex && sy == ey){	//如果起点和终点重合 
		return true;
	}
	S[sx][sy].x = sx;
	S[sx][sy].y = sy;
	Point t(sx, sy, 0, 0);
	t.g = 0;
	t.h = h(t);
	t.f = t.h + t.g;
	pq.push(t);
	Point u, v;
	while (!pq.empty()){
		u = pq.top();
		pq.pop();
		if (u.x == ex && u.y == ey){
			Path_Len = u.deep;
			Time = u.time;
			Deep = u.deep;
			Get_Path();
			return true;
		}
		for (int i = 0; i < 4; ++i){
			v = u;
			v.x += dir_x[i];
			v.y += dir_y[i];
			if (!Check(v.x, v.y)) continue;
			vis[v.x][v.y] = visited;
			S[v.x][v.y].x = v.x;
			S[v.x][v.y].y = v.y;
			S[v.x][v.y].pre_x = u.x;
			S[v.x][v.y].pre_y = u.y;
			if (g_NewMaze[v.x][v.y] == road || g_NewMaze[v.x][v.y] == grass){
				v.time += 1;
				v.g += 1;
			}
			else if (g_NewMaze[v.x][v.y] == water){
				v.time += 2;
				v.g += 2;
			}
			else if (g_NewMaze[v.x][v.y] == swamp){
				v.time += 3;
				v.g += 3;
			}
			v.h = h(v);
			v.f = v.g + v.h;
			v.deep++;
			pq.push(v);
		}
	}
	return false;
}


void CGhostManDlg::OnStnClickedStaticClose()
{
	// TODO:  在此添加控件通知处理程序代码
	HINSTANCE hIns = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_BITMAP_CLOSE_CLICK), RT_GROUP_ICON);
	HBITMAP   hBmp = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BITMAP_CLOSE_CLICK));
	m_btnClose.SetBitmap(hBmp);

	Sleep(300);
	PostMessage(WM_CLOSE);
}


void CGhostManDlg::OnStnClickedStaticMin()
{
	// TODO:  在此添加控件通知处理程序代码
	HINSTANCE hIns = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_BITMAP_MIN_CLICK), RT_GROUP_ICON);
	HBITMAP   hBmp = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BITMAP_MIN_CLICK));
	m_btnMin.SetBitmap(hBmp);

	Sleep(300);
	PostMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
}


void CGhostManDlg::OnStnClickedStaticMax()
{
	// TODO:  在此添加控件通知处理程序代码
	PostMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);//最大化
}

void CGhostManDlg::OnStnClickedStaticDynamic()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_nAlgorithmIndex >= 4)
	{
		MessageBox(L"当前算法不支持动态执行", L"Error");
		return;
	}
	if (m_bByStep)
	{
		m_bInternalShow = TRUE;
		m_bFirstStep = FALSE;
		m_bByStep = FALSE;		//单步线程下次就不需要再次等待单步按钮响应
		m_bClickStep = TRUE;	//激发单步线程的等待状态，让单步执行的线程得以执行
		return;
	}

	m_bInternalShow = TRUE;

	switch (m_nAlgorithmIndex)
	{
		case 1:
		{
			CloseHandle(CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ExpandAstarFunction,
				this, NULL, NULL));
			break;
		}
		case 2:
		{
			CloseHandle(CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ExpandBFSFunction,
				this, NULL, NULL));
			break;
		}
		case 3:
		{
			CloseHandle(CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ExpandDFSFunction,
				this, NULL, NULL));
			break;
		}
		default:
		{
			MessageBox(L"Please Choose An algorithm", L"Error");
			break;
		}
	}
}


void CGhostManDlg::OnStnClickedStaticInit()
{
	// TODO:  在此添加控件通知处理程序代码
	InitStatus();
	InitBFStatus();
	InitDFStatus();
	InitAstartatus();
	memcpy(g_NewMaze, g_maze, sizeof(int)*MAXX*MAXY);

	if (m_nAlgorithmIndex <= 3)
	{
		DrawGrid();
		DrawCurMazeColor();
	}
	else if (m_nAlgorithmIndex == 5)
	{
		DrawGrid();
		DrawInitSAMaze();
	}
	
}


void CGhostManDlg::OnStnClickedStaticExec()
{
	// TODO:  在此添加控件通知处理程序代码

	if (m_nAlgorithmIndex <= 3)
	{
		m_bHaveAResult = FALSE;
		if (!m_bHaveAStart)
		{
			MessageBox(L"Please Choose A StartPoint", L"Error");
			return;
		}
		if (!m_bHaveAEnd)
		{
			MessageBox(L"Please Choose A EndPoint", L"Error");
			return;
		}
		m_bHaveARoad = FALSE;

		DrawCurMazeColor();
		DrawGrid();
	}
	else if (m_nAlgorithmIndex >= 4)
	{
		m_bHaveAResult = FALSE;
		m_bHaveARoad = FALSE;
	}
	
	switch (m_nAlgorithmIndex)
	{
		case 1:
		{
			Final_ASTAR();
			break;
		}
		case 2:
		{
			Final_BFS();
			break;
		}
		case 3:
		{
			Final_DFS();
			break;
		}
		case 4:
		{
		//	Final_IDAStar();
			CloseHandle(CreateThread(0, 0, 
				(LPTHREAD_START_ROUTINE)ExpandIDAStarFunction, this, 0, 0));
			break;
		}
		case 5:
		{
			Final_SA();
			break;
		}
		default:
		{
			MessageBox(L"Please Choose An algorithm", L"Error");
			break;
		}
	}
	
}

void CGhostManDlg::Final_SA()
{
	cnt = 0;
	x = 20, y = 40;
	e1 = SAPoint(0, 0);
	e2 = SAPoint(x, y);
	for (int i = 0; i < MAXX; ++i){
		for (int j = 0; j < MAXY; ++j){
			if (g_SaNewMaze[i][j] == 2){
				p[cnt].x = i;
				p[cnt++].y = j;
			}
		}
	}
	SA(max(x, y));
	m_bHaveAResult = TRUE;
	SetTimer(IDT_DELAY_FLICKER, 100, NULL);
}
void CGhostManDlg::OnStnClickedStaticStep()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_nAlgorithmIndex >= 4)
	{
		MessageBox(L"当前算法不支持单步执行", L"Error");
		return;
	}
	if (!m_bFirstStep)		//第一次进入单步
	{
		m_bFirstStep = TRUE;
		m_bByStep = TRUE;

		switch (m_nAlgorithmIndex)
		{
			case 1:
			{
				CloseHandle(CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ExpandAstarFunction,
					this, NULL, NULL));
				break;
			}
			case 2:
			{
				CloseHandle(CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ExpandBFSFunction,
					this, NULL, NULL));
				break;
			}
			case 3:
			{
				CloseHandle(CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ExpandDFSFunction,
					this, NULL, NULL));
				break;
			}
			default:
			{
				MessageBox(L"Please Choose An algorithm", L"Error");
				m_bFirstStep = FALSE;
				break;
			}
		}
	}
	else
	{
		if (m_nAlgorithmIndex == 0)
		{
			MessageBox(L"Please Choose An algorithm", L"Error");
		}
	}
	m_bClickStep = TRUE;
	

}


void CGhostManDlg::OnStnClickedStaticStatic()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_nAlgorithmIndex >= 4)
	{
		MessageBox(L"当前算法不支持静态执行", L"Error");
		return;
	}
	DrawCurMazeColor();
	DrawGrid();
	if (m_bByStep)
	{
		m_bFirstStep = FALSE;
		m_bByStep = FALSE;		//单步线程下次就不需要再次等待单步按钮响应
		m_bClickStep = TRUE;	//激发单步线程的等待状态，让单步执行的线程得以执行
		return;
	}

	m_bInternalShow = FALSE;
	switch (m_nAlgorithmIndex)
	{
		case 1:
		{
			CloseHandle(CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ExpandAstarFunction,
				this, NULL, NULL));
			break;
		}
		case 2:
		{
			CloseHandle(CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ExpandBFSFunction,
				this, NULL, NULL));
			break;
		}
		case 3:
		{
			CloseHandle(CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ExpandDFSFunction,
				this, NULL, NULL));
			break;
		}
		default:
		{
			MessageBox(L"Please Choose An algorithm", L"Error");
			break;
		}
	}
}

void CGhostManDlg::OnStnClickedStaticAstar()
{
	// TODO:  在此添加控件通知处理程序代码
//	MovePandaToZero();

	for (int i = 1; i < 10; i++)
	{
		GetDlgItem(1033 + i)->ShowWindow(SW_HIDE);
	}
	m_nIDACurGridX = m_nIDACurGridY = 0;
	m_nCurPandaIndex = 0;
	KillTimer(IDT_DELAY_DRAWIDAGRID);
	KillTimer(IDT_DELAY_DRAWIDAPANDA);
	if (!GetDlgItem(IDC_STATIC_INTRODUCTION)->IsWindowVisible())
	{
		GetDlgItem(IDC_STATIC_INTRODUCTION)->ShowWindow(SW_SHOW);
	}
	OnStnClickedStaticInit();
	ClearAlgorithmCursor();
	m_btnAStar.m_nClicked = 0;
	HINSTANCE hIns = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_BITMAP_ASTAR_CLICK), RT_GROUP_ICON);
	HBITMAP   hBmp = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BITMAP_ASTAR_CLICK));
	m_btnAStar.SetBitmap(hBmp);

	m_btnAStar.m_nClicked = 1;
	m_nAlgorithmIndex = 1;
	
	if (m_bNeedRepaint)
		SetTimer(IDT_DELAY_REPAINT, 30, NULL);

}

void CGhostManDlg::OnStnClickedStaticBfs()
{
	// TODO:  在此添加控件通知处理程序代码
	for (int i = 1; i < 10; i++)
	{
		GetDlgItem(1033 + i)->ShowWindow(SW_HIDE);
	}
	m_nIDACurGridX = m_nIDACurGridY = 0;
	m_nCurPandaIndex = 0;
	KillTimer(IDT_DELAY_DRAWIDAGRID);
	KillTimer(IDT_DELAY_DRAWIDAPANDA);
	if (!GetDlgItem(IDC_STATIC_INTRODUCTION)->IsWindowVisible())
	{
		GetDlgItem(IDC_STATIC_INTRODUCTION)->ShowWindow(SW_SHOW);
	}
	OnStnClickedStaticInit();
	ClearAlgorithmCursor();
	HINSTANCE hIns = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_BITMAP_BFS_CLICK), RT_GROUP_ICON);
	HBITMAP   hBmp = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BITMAP_BFS_CLICK));

	m_btnBFS.SetBitmap(hBmp);
	m_btnBFS.m_nClicked = 1;
	m_nAlgorithmIndex = 2;

	if (m_bNeedRepaint)
		SetTimer(IDT_DELAY_REPAINT, 30, NULL);
}


void CGhostManDlg::OnStnClickedStaticDfs()
{
	// TODO:  在此添加控件通知处理程序代码
	for (int i = 1; i < 10; i++)
	{
		GetDlgItem(1033 + i)->ShowWindow(SW_HIDE);
	}
	m_nIDACurGridX = m_nIDACurGridY = 0;
	m_nCurPandaIndex = 0;
	KillTimer(IDT_DELAY_DRAWIDAGRID);
	KillTimer(IDT_DELAY_DRAWIDAPANDA);

	if (!GetDlgItem(IDC_STATIC_INTRODUCTION)->IsWindowVisible())
	{
		GetDlgItem(IDC_STATIC_INTRODUCTION)->ShowWindow(SW_SHOW);
	}
	OnStnClickedStaticInit();
	ClearAlgorithmCursor();
	m_btnDFS.m_nClicked = 1;

	HINSTANCE hIns = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_BITMAP_DFS_CLICK), RT_GROUP_ICON);
	HBITMAP   hBmp = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BITMAP_DFS_CLICK));
	m_btnDFS.SetBitmap(hBmp);
	m_nAlgorithmIndex = 3;

	if (m_bNeedRepaint)
		SetTimer(IDT_DELAY_REPAINT, 30, NULL);
}


void CGhostManDlg::OnStnClickedStaticIdastar()
{
	// TODO:  在此添加控件通知处理程序代码
	m_bNeedRepaint = TRUE;
	CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)RandIDAGridFunction, this, 0, 0));

	for (int i = 1; i <= 9;i++)
	{
		GetDlgItem(1033 + i)->ShowWindow(SW_HIDE);
	}
	GetDlgItem(IDC_STATIC_INTRODUCTION)->ShowWindow(SW_HIDE);
	ClearAlgorithmCursor();

	HINSTANCE hIns = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_BITMAP_IDASTAR_CLICK), RT_GROUP_ICON);
	HBITMAP   hBmp = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BITMAP_IDASTAR_CLICK));
	m_btnIDAStar.SetBitmap(hBmp);
	m_btnIDAStar.m_nClicked = 1;
	m_nAlgorithmIndex = 4;

	SetTimer(IDT_DELAY_CLOSEGRID, 10, NULL);
}


void CGhostManDlg::OnStnClickedStaticSA()
{
	// TODO:  在此添加控件通知处理程序代码
	m_btnSA.m_nClicked = 1;
	m_nAlgorithmIndex = 5;
	for (int i = 1; i <= 9; i++)
	{
		GetDlgItem(1033 + i)->ShowWindow(SW_HIDE);
	}
	m_nIDACurGridX = m_nIDACurGridY = 0;
	m_nCurPandaIndex = 0;
	KillTimer(IDT_DELAY_DRAWIDAGRID);
	KillTimer(IDT_DELAY_DRAWIDAPANDA);

	GetDlgItem(IDC_STATIC_INTRODUCTION)->ShowWindow(SW_HIDE);
	ClearAlgorithmCursor();
	OnStnClickedStaticInit();

	HINSTANCE hIns = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_BITMAP_SA_CLICK), RT_GROUP_ICON);
	HBITMAP   hBmp = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BITMAP_SA_CLICK));
	m_btnSA.SetBitmap(hBmp);
	m_btnSA.m_nClicked = 1;

	if (m_bNeedRepaint)
		SetTimer(IDT_DELAY_REPAINT, 30, NULL);
	
}

void CGhostManDlg::ClearAlgorithmCursor()
{
	m_btnAStar.m_nClicked = 0;
	HINSTANCE hIns = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_BITMAP_ASTAR_NORMAL), RT_GROUP_ICON);
	HBITMAP   hBmp = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BITMAP_ASTAR_NORMAL));
	m_btnAStar.SetBitmap(hBmp);

	m_btnBFS.m_nClicked = 0;
	hIns = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_BITMAP_BFS_NORMAL), RT_GROUP_ICON);
	hBmp = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BITMAP_BFS_NORMAL));
	m_btnBFS.SetBitmap(hBmp);

	m_btnDFS.m_nClicked = 0;
	hIns = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_BITMAP_DFS_NORMAL), RT_GROUP_ICON);
	hBmp = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BITMAP_DFS_NORMAL));
	m_btnDFS.SetBitmap(hBmp);

	m_btnIDAStar.m_nClicked = 0;
	hIns = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_BITMAP_IDASTAR_NORMAL), RT_GROUP_ICON);
	hBmp = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BITMAP_IDASTAR_NORMAL));
	m_btnIDAStar.SetBitmap(hBmp);

	m_btnSA.m_nClicked = 0;
	hIns = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_BITMAP_SA_NORMAL), RT_GROUP_ICON);
	hBmp = ::LoadBitmap(hIns, MAKEINTRESOURCE(IDB_BITMAP_SA_NORMAL));
	m_btnSA.SetBitmap(hBmp);
}

void CGhostManDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	if (m_nAlgorithmIndex <= 3)
	{
		DrawGrid();
		DrawCurMazeColor();
	}

	// TODO:  在此处添加消息处理程序代码
}


BOOL CGhostManDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

//	return CDialogEx::OnEraseBkgnd(pDC);
	return TRUE;
}


void CGhostManDlg::InitDC()
{
	if (m_Dc.GetSafeHdc() != NULL)
	{
		m_Dc.DeleteDC();
	}
	if (m_BitMap.GetSafeHandle() != NULL)
	{
		m_BitMap.DeleteObject();
	}

	CDC* pNewDc = this->GetDC();
	m_Dc.CreateCompatibleDC(pNewDc);

	CRect rc;
	GetWindowRect(rc);
	ScreenToClient(rc);

	m_BitMap.CreateCompatibleBitmap(pNewDc, rc.Width(), rc.Height());
	m_Dc.SelectObject(&m_BitMap);
	ReleaseDC(pNewDc);

}

void CGhostManDlg::DrawDC()
{
	CRect rect;
	//以下两句讲获得控件在屏幕中的位置  
	GetDlgItem(IDC_STATIC_PIC)->GetWindowRect(&rect);//获取控件相对于屏幕的位置,这个控件必须隐藏  
	ScreenToClient(rect);//转化为对话框上的相对位置  

	CDC* pDc = GetDC();
	m_Dc.BitBlt(rect.left, rect.top, rect.Width()+5, rect.Height()+5, pDc, rect.left, rect.top, SRCCOPY);
}

bool CGhostManDlg::DFS(){ //由于矩阵是公用的就不需要传参数了,这里传入的参数为起点坐标 
	Out_Path[0][0] = sx;
	Out_Path[0][1] = sy;
	Point p(sx, sy, 0, 0);
	Point  u, v;
	sta.push(p);
	vis[sx][sy] = visited;
	while (!sta.empty()){
		u = sta.top();
		if (u.x == ex && u.y == ey){
			finded = 1;
			Path_Len = v.deep;
			Time = v.time;
			Deep = v.deep;
			break;
		}
		int i = 0;
		for (i = 0; i < 4; ++i){
			v = u;
			v.x += dir_x[i];
			v.y += dir_y[i];
			v.deep += 1;
			if (!Check(v.x, v.y)){
				continue;
			}
			if (g_NewMaze[v.x][v.y] == road || g_NewMaze[v.x][v.y] == grass){
				v.time++;
			}
			else if (g_NewMaze[v.x][v.y] == water){
				v.time += 2;
			}
			else if (g_NewMaze[v.x][v.y] == swamp){
				v.time += 3;
			}
			vis[v.x][v.y] = visited;
			sta.push(v);
			Out_Path[v.deep][0] = v.x;
			Out_Path[v.deep][1] = v.y;
			break;
		}
		if (i == 4) sta.pop();
	}
	if (finded){
		return true;
	}
	else{
		return false;
	}
}
bool CGhostManDlg::ExDFS(){ //由于矩阵是公用的就不需要传参数了,这里传入的参数为起点坐标 
	Out_Path[0][0] = sx;
	Out_Path[0][1] = sy;
	Point p(sx, sy, 0, 0);
	Point  u, v;
	sta.push(p);
	vis[sx][sy] = visited;
	while (!sta.empty()){
		u = sta.top();
		if (u.x == ex && u.y == ey){
			finded = 1;
			Path_Len = v.deep;
			Time = v.time;
			Deep = v.deep;
			break;
		}
		if ((u.x == sx && u.y == sy) || (u.x == ex && u.y == ey))
		{
		}
		else
		{
			CClientDC dc(this);
			dc.FillSolidRect(m_nStartX + u.y*(m_nWidth + 1) + 1,
				m_nStartY + u.x*(m_nHeight + 1) + 1, m_nWidth, m_nHeight, RGB(215, 233, 124));
			if (m_bInternalShow) Sleep(50);
		}
		int i = 0;
		for (i = 0; i < 4; ++i){
			v = u;
			v.x += dir_x[i];
			v.y += dir_y[i];
			v.deep += 1;
			if (!Check(v.x, v.y)){
				continue;
			}
			if (g_NewMaze[v.x][v.y] == road || g_NewMaze[v.x][v.y] == grass){
				v.time++;
			}
			else if (g_NewMaze[v.x][v.y] == water){
				v.time += 2;
			}
			else if (g_NewMaze[v.x][v.y] == swamp){
				v.time += 3;
			}
			vis[v.x][v.y] = visited;
			sta.push(v);
			Out_Path[v.deep][0] = v.x;
			Out_Path[v.deep][1] = v.y;

			if ((v.x == sx && v.y == sy) || (v.x == ex && v.y == ey))
			{
			}
			else{
				CClientDC dc(this);
				dc.FillSolidRect(m_nStartX + v.y*(m_nWidth + 1) + 1,
					m_nStartY + v.x*(m_nHeight + 1) + 1, m_nWidth, m_nHeight, RGB(102, 137, 205));
				if (m_bInternalShow) Sleep(50);
			}
			break;
		}
		if ((u.x == sx && u.y == sy) || (u.x == ex && u.y == ey))
		{
		}
		else{
			CClientDC dc(this);
			dc.FillSolidRect(m_nStartX + u.y*(m_nWidth + 1) + 1,
				m_nStartY + u.x*(m_nHeight + 1) + 1, m_nWidth, m_nHeight, RGB(205, 191, 179));

			if (m_bInternalShow) Sleep(50);
		}
		if (i == 4) sta.pop();
		if (m_bByStep)
		{
			while (1)
			{
				if (m_bClickStep)
				{
					m_bClickStep = FALSE;
					break;
				}
				else
				{
				}
			}
		}
	}
	if (finded){
		return true;
	}
	else{
		return false;
	}
}

void CGhostManDlg::RandIDAGrid()
{
	
	for (int i = 0; i < 9; i++)
	{
		*((int*)g_Squared + i) = -1;
	}
	srand((unsigned int)time(0));

	int* pSquared = (int*)g_Squared;
	int nTemp = 0;

	while (1)
	{
		for (int i = 0; i < 9; i++)
		{
			nTemp = rand() % 9;
			while (!CheckNum(nTemp, i))
			{
				nTemp = rand() % 9;
			}
			*(pSquared + i) = nTemp;
		}
		InitIDAstarstatus();
		if (IDA_check(s))
		{
			break;
		}
	}
	
	
}

bool CGhostManDlg::CheckNum(int nNum, int nIndex)
{
	for (int i = 0; i < nIndex;i++)
	{
		if (nNum == *((int*)g_Squared + i))
			return false;
	}
	return true;
}

void CGhostManDlg::MovePandaToZero()
{
	for (int i = 1; i < 10; i++)
	{
		GetDlgItem(1033 + i)->MoveWindow(m_rcPanda[0].left, m_rcPanda[0].top,0,0);
	}
}
void CGhostManDlg::MovePandaToInit()
{
	for (int i = 1; i < 10; i++)
	{
		GetDlgItem(1033 + i)->MoveWindow(m_rcPanda[i-1]);
	}
}

LRESULT CGhostManDlg::OnRepaintGrid(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

int CGhostManDlg::IDA_h(IDA_S s){
	int ans = 0, i, j;
	for (i = 0; i < 3; ++i){
		for (j = 0; j < 3; ++j){
			if (s.maze[i][j]){
				ans += abs(i - (s.maze[i][j] - 1) / 3) + abs(j - (s.maze[i][j] - 1) % 3);
			}
		}
	}
	return ans;
}

int CGhostManDlg::IDA_dfs(IDA_S s){
	s.h = IDA_h(s);
	if (s.h == 0){
		ok = 1;
		return s.step;
	}
	//如果步数不够，结束此次搜索，返回一个最低可能的步数 
	if (s.h + s.step > limit) return s.h + s.step;
	int minn = 0x7fffffff;
	IDA_S v;
	for (int i = 0; i < 4; ++i){
		if (abs(i - s.pre) == 2) continue;
		v = s;
		v.x += dir_x[i];
		v.y += dir_y[i];
		v.step += 1;
		v.pre = i;
		if (v.x < 0 || v.y < 0 || v.x >= 3 || v.y >= 3){
			continue;
		}
		buff[s.step] = i;
		swap(v.maze[s.x][s.y], v.maze[v.x][v.y]);
		int tmp = IDA_dfs(v);
		if (ok) return tmp;
		minn = min(tmp, minn);
	}
	return minn;
}


//IDA* 主程序 
bool CGhostManDlg::IDA_star(IDA_S s){
	ok = 0, limit = 0;
	for (int i = 0; i < 3; ++i){
		for (int j = 0; j < 3; ++j){
			s.maze[i][j] = g_Squared[i][j];
			if (!g_Squared[i][j]){
				s.x = i;
				s.y = j;
			}
		}
	}
	s.pre = -233;
	clr(buff, -1);
	s.h = IDA_h(s);
	if (s.h == 0){
//		puts("已经是最终状态了，不需要移动");
		MessageBox(L"无需移动", L"Error");
	}
	if (!IDA_check(s)){
		MessageBox(L"此图无解", L"Error");
		return false;
	}
	while (ok == 0 && limit <= 30){
		limit = IDA_dfs(s);
	}
	if (ok == 1){
		for (int i = 0; i < limit; ++i){
			IDA_Path[i] = op[buff[i]];
		}
		return true;
	}
	else{
		return false;
	}
	return false;
}

//奇偶性状态检查，用于剪枝，提高算法效率 
bool CGhostManDlg::IDA_check(IDA_S s){
	int a[9], k = 0, i, j;
	for (i = 0; i < 3; ++i){
		for (j = 0; j < 3; ++j){
			a[k++] = s.maze[i][j];
		}
	}
	int sum = 0;
	for (i = 0; i < 9; ++i){
		for (j = i + 1; j < 9; ++j){
			if (a[j] && a[i] && a[i] > a[j]){
				++sum;
			}
		}
	}
	return !(sum & 1);
}

LRESULT CGhostManDlg::OnPaintPanda(WPARAM wParam, LPARAM lParam)
{

	DrawInitDerrick();
	Sleep(300);
	CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ExpandDerrickIDAFunction, this, 0, 0));
	return 0;
}

void CGhostManDlg::DrawInitDerrick()
{


	CClientDC dc(this);

	for (int j = 0; j < 7;j++)
	{
		switch (g_Derrick[2][j])
		{
			case 1:
			{
				dc.FillSolidRect(m_nIDAGridStartX + j * 41,
					m_nIDAGridStartY + 2 * 41, 41, 41, RGB(0, 255, 0));
				break;
			}
			case 2:
			{
				dc.FillSolidRect(m_nIDAGridStartX + j * 41,
					m_nIDAGridStartY + 2 * 41, 41, 41, RGB(7, 158, 239));
				break;
			}
			case 3:
			{
				dc.FillSolidRect(m_nIDAGridStartX + j * 41,
					m_nIDAGridStartY + 2 * 41, 41, 41, RGB(255, 153, 0));
				break;
			}
		}
		switch (g_Derrick[4][j])
		{
			case 1:
			{
				dc.FillSolidRect(m_nIDAGridStartX + j * 41,
					m_nIDAGridStartY + 4 * 41, 41, 41, RGB(0, 255, 0));
				break;
			}
			case 2:
			{
				dc.FillSolidRect(m_nIDAGridStartX + j * 41,
					m_nIDAGridStartY + 4 * 41, 41, 41, RGB(7, 158, 239));
				break;
			}
			case 3:
			{
				dc.FillSolidRect(m_nIDAGridStartX + j * 41,
					m_nIDAGridStartY + 4 * 41, 41, 41, RGB(255, 153, 0));
				break;
			}
		}
	}

	for (int i = 0; i < 7; i++)
	{
		switch (g_Derrick[i][2])
		{
			case 1:
			{
				dc.FillSolidRect(m_nIDAGridStartX + 2 * 41,
					m_nIDAGridStartY + i * 41, 41, 41, RGB(0, 255, 0));
				break;
			}
			case 2:
			{
				dc.FillSolidRect(m_nIDAGridStartX + 2 * 41,
					m_nIDAGridStartY + i * 41, 41, 41, RGB(7, 158, 239));
				break;
			}
			case 3:
			{
				dc.FillSolidRect(m_nIDAGridStartX + 2 * 41,
					m_nIDAGridStartY + i * 41, 41, 41, RGB(255, 153, 0));
				break;
			}
		}
		switch (g_Derrick[i][4])
		{
			case 1:
			{
				dc.FillSolidRect(m_nIDAGridStartX + 4 * 41,
					m_nIDAGridStartY + i * 41, 41, 41, RGB(0, 255, 0));
				break;
			}
			case 2:
			{
				dc.FillSolidRect(m_nIDAGridStartX + 4 * 41,
					m_nIDAGridStartY + i * 41, 41, 41, RGB(7, 158, 239));
				break;
			}
			case 3:
			{
				dc.FillSolidRect(m_nIDAGridStartX + 4 * 41,
					m_nIDAGridStartY + i * 41, 41, 41, RGB(255, 153, 0));
				break;
			}
		}

	}
	
}
void CGhostManDlg::DrawCurDerrick()
{
	CClientDC dc(this);

	for (int j = 0; j < 7; j++)
	{
		switch (g_NewDerrick[2][j])
		{
		case 1:
		{
			dc.FillSolidRect(m_nIDAGridStartX + j * 41,
				m_nIDAGridStartY + 2 * 41, 41, 41, RGB(0, 255, 0));
			break;
		}
		case 2:
		{
			dc.FillSolidRect(m_nIDAGridStartX + j * 41,
				m_nIDAGridStartY + 2 * 41, 41, 41, RGB(7, 158, 239));
			break;
		}
		case 3:
		{
			dc.FillSolidRect(m_nIDAGridStartX + j * 41,
				m_nIDAGridStartY + 2 * 41, 41, 41, RGB(255, 153, 0));
			break;
		}
		}
		switch (g_NewDerrick[4][j])
		{
		case 1:
		{
			dc.FillSolidRect(m_nIDAGridStartX + j * 41,
				m_nIDAGridStartY + 4 * 41, 41, 41, RGB(0, 255, 0));
			break;
		}
		case 2:
		{
			dc.FillSolidRect(m_nIDAGridStartX + j * 41,
				m_nIDAGridStartY + 4 * 41, 41, 41, RGB(7, 158, 239));
			break;
		}
		case 3:
		{
			dc.FillSolidRect(m_nIDAGridStartX + j * 41,
				m_nIDAGridStartY + 4 * 41, 41, 41, RGB(255, 153, 0));
			break;
		}
		}
	}

	for (int i = 0; i < 7; i++)
	{
		switch (g_NewDerrick[i][2])
		{
		case 1:
		{
			dc.FillSolidRect(m_nIDAGridStartX + 2 * 41,
				m_nIDAGridStartY + i * 41, 41, 41, RGB(0, 255, 0));
			break;
		}
		case 2:
		{
			dc.FillSolidRect(m_nIDAGridStartX + 2 * 41,
				m_nIDAGridStartY + i * 41, 41, 41, RGB(7, 158, 239));
			break;
		}
		case 3:
		{
			dc.FillSolidRect(m_nIDAGridStartX + 2 * 41,
				m_nIDAGridStartY + i * 41, 41, 41, RGB(255, 153, 0));
			break;
		}
		}
		switch (g_NewDerrick[i][4])
		{
		case 1:
		{
			dc.FillSolidRect(m_nIDAGridStartX + 4 * 41,
				m_nIDAGridStartY + i * 41, 41, 41, RGB(0, 255, 0));
			break;
		}
		case 2:
		{
			dc.FillSolidRect(m_nIDAGridStartX + 4 * 41,
				m_nIDAGridStartY + i * 41, 41, 41, RGB(7, 158, 239));
			break;
		}
		case 3:
		{
			dc.FillSolidRect(m_nIDAGridStartX + 4 * 41,
				m_nIDAGridStartY + i * 41, 41, 41, RGB(255, 153, 0));
			break;
		}
		}

	}
}
void CGhostManDlg::InitDerrick()
{
	memcpy(g_NewDerrick, g_Derrick, sizeof(g_Derrick));
}

void CGhostManDlg::rota_A(){
	int t = g_NewDerrick[0][2];
	for (int i = 0; i < 6; ++i){
		g_NewDerrick[i][2] = g_NewDerrick[i + 1][2];
	}
	g_NewDerrick[6][2] = t;
}

void CGhostManDlg::rota_F(){
	int t = g_NewDerrick[6][2];
	for (int i = 6; i >= 1; --i){
		g_NewDerrick[i][2] = g_NewDerrick[i - 1][2];
	}
	g_NewDerrick[0][2] = t;
}

void CGhostManDlg::rota_B(){
	int t = g_NewDerrick[0][4];
	for (int i = 0; i < 6; ++i){
		g_NewDerrick[i][4] = g_NewDerrick[i + 1][4];
	}
	g_NewDerrick[6][4] = t;
}

void CGhostManDlg::rota_E(){
	int t = g_NewDerrick[6][4];
	for (int i = 6; i >= 1; --i){
		g_NewDerrick[i][4] = g_NewDerrick[i - 1][4];
	}
	g_NewDerrick[0][4] = t;
}

void CGhostManDlg::rota_C(){
	int t = g_NewDerrick[2][6];
	for (int i = 6; i >= 1; --i){
		g_NewDerrick[2][i] = g_NewDerrick[2][i - 1];
	}
	g_NewDerrick[2][0] = t;
}

void CGhostManDlg::rota_H(){
	int t = g_NewDerrick[2][0];
	for (int i = 0; i < 6; ++i){
		g_NewDerrick[2][i] = g_NewDerrick[2][i + 1];
	}
	g_NewDerrick[2][6] = t;
}

void CGhostManDlg::rota_D(){
	int t = g_NewDerrick[4][6];
	for (int i = 6; i >= 1; --i){
		g_NewDerrick[4][i] = g_NewDerrick[4][i - 1];
	}
	g_NewDerrick[4][0] = t;
}

void CGhostManDlg::rota_G(){
	int t = g_NewDerrick[4][0];
	for (int i = 0; i < 6; ++i){
		g_NewDerrick[4][i] = g_NewDerrick[4][i + 1];
	}
	g_NewDerrick[4][6] = t;
}

int CGhostManDlg::Derrick_h(){
	int a[4] = { 0 };
	for (int i = 2; i <= 4; ++i){
		a[g_NewDerrick[2][i]]++;
	}
	a[g_NewDerrick[3][2]]++;
	a[g_NewDerrick[3][4]]++;
	for (int i = 2; i <= 4; ++i){
		a[g_NewDerrick[4][i]]++;
	}
	sort(a, a + 4);
	return 8 - a[3];
}

bool CGhostManDlg::Derrick_check(){
	if (g_NewDerrick[2][2] != g_NewDerrick[2][3]) return false;
	if (g_NewDerrick[2][3] != g_NewDerrick[2][4]) return false;
	if (g_NewDerrick[3][2] != g_NewDerrick[3][4]) return false;
	if (g_NewDerrick[4][2] != g_NewDerrick[4][3]) return false;
	if (g_NewDerrick[4][3] != g_NewDerrick[4][4]) return false;
	if (g_NewDerrick[2][2] != g_NewDerrick[3][2]) return false;
	if (g_NewDerrick[3][2] != g_NewDerrick[4][2]) return false;
	if (g_NewDerrick[2][3] != g_NewDerrick[4][3]) return false;
	if (g_NewDerrick[2][4] != g_NewDerrick[3][4]) return false;
	if (g_NewDerrick[3][4] != g_NewDerrick[4][4]) return false;
	return true;
}

bool CGhostManDlg::Derrick_dfs(int d){

	if (d == limit){
		return Derrick_check();
	}
	if (Derrick_h() + d > limit){
		return false;
	}

	rota_A();
	ans[d] = 'A';
	if (Derrick_dfs(d + 1)){
		return true;
	}
	rota_F();

	rota_B();
	ans[d] = 'B';
	if (Derrick_dfs(d + 1)){
		return true;
	}
	rota_E();

	rota_C();
	ans[d] = 'C';
	if (Derrick_dfs(d + 1)){
		return true;
	}
	rota_H();

	rota_D();
	ans[d] = 'D';
	if (Derrick_dfs(d + 1)){
		return true;
	}
	rota_G();

	rota_E();
	ans[d] = 'E';
	if (Derrick_dfs(d + 1)){
		return true;
	}
	rota_B();

	rota_F();
	ans[d] = 'F';
	if (Derrick_dfs(d + 1)){
		return true;
	}
	rota_A();

	rota_G();
	ans[d] = 'G';
	if (Derrick_dfs(d + 1)){
		return true;
	}
	rota_D();
	rota_H();
	ans[d] = 'H';
	if (Derrick_dfs(d + 1)){
		return true;
	}
	rota_C();

	return false;
}

void CGhostManDlg::Derrick_IDAstar(){
	limit = 1;
	while (true){
		if (Derrick_dfs(0)){
			break;
		}
		limit++;
	}
}

DWORD CGhostManDlg::ExpandDerrickIDAFunction(LPARAM lParam)
{
	CGhostManDlg* dlg = (CGhostManDlg*)lParam;
	dlg->Derrick_IDAstar();
	dlg->InitDerrick();
	for (int i = 0; i < limit; ++i)
	{
		switch (ans[i])
		{
			case 'A':
			{
				dlg->rota_A();
				break;
			}
			case 'B':
			{
				dlg->rota_B();
				break;
			}
			case 'C':
			{
				dlg->rota_C();
				break;
			}
			case 'D':
			{
				dlg->rota_D();
				break;
			}
			case 'E':
			{
				dlg->rota_E();
				break;
			}
			case 'F':
			{
				dlg->rota_F();
				break;
			}
			case 'G':
			{
				dlg->rota_G();
				break;
			}
			case 'H':
			{
				dlg->rota_H();
				break;
			}
		}
		dlg->DrawCurDerrick();
		Sleep(500);
	}
	return 0;
}

double CGhostManDlg::SA_dis(SAPoint a, SAPoint b){
	return sqrt((a.x - b.x) * (a.x - b.x)
		+ (a.y - b.y) * (a.y - b.y));
}
double CGhostManDlg::SA_check(SAPoint t){
	double d = INF;
	for (int i = 0; i < cnt; ++i){
		d = min(d, SA_dis(t, p[i]));
	}
	return d;
}

double CGhostManDlg::SA_Rand(){
	return rand() % (1000 + 1) / (1.0 * 1000.0);
}

SAPoint CGhostManDlg::SA_gen_p(SAPoint a, SAPoint b){
	SAPoint t = SAPoint(a.x + (b.x - a.x) * SA_Rand(),
		a.y + (b.y - a.y) * SA_Rand());
	t.v = SA_check(t);
	return t;
}

void CGhostManDlg::SA(double T){
	for (int i = 0; i < NUM; ++i){
		m[i] = SA_gen_p(e1, e2);
	}

	while (T > EPS){
		for (int i = 0; i < NUM; ++i){
			for (int j = 0; j < NUM; ++j){
				SAPoint t = SA_gen_p(SAPoint(max(m[i].x - T, 0.0), max(m[i].y - T, 0.0)),
					SAPoint(min(m[i].x + T, x), min(m[i].y + T, y)));
				if (t.v > m[i].v){
					m[i] = t;
				}
			}
		}
		T *= 0.9;
	}
	double ans = 0.0;
	int id = 0;
	for (int i = 0; i < NUM; ++i){
		if (m[i].v > ans){
			ans = m[i].v;
			id = i;
		}
	}
	PResult.x = (int)(m[id].y);
	PResult.y =  (int)(m[id].x);
}
