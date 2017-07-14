#include<windows.h> 

#include<stdlib.h> 

#include <mmsystem.h>

#pragma comment (lib,"Winmm.lib")

typedef struct//存储选中区域坐标的结构体
{
	LONG lx;//棋子左上角横坐标
	LONG ly;//棋子左上角纵坐标
	LONG rx;//棋子右下角横坐标
	LONG ry;//棋子右下角纵坐标
}NextChessPlace;

typedef struct//为了进行悔棋操作,用来存储棋子的相关信息
{
	LONG lx;//上一步棋子的左上角的横坐标
	LONG ly;//上一步棋子的左上角的纵坐标
	LONG rx;//上一步棋子的右下角的横坐标
	LONG ry;//上一步棋子的右下角的纵坐标
	LONG number;//棋子的编号
	int color;//棋子的颜色
	int eat;//如果发生吃棋行为,被吃棋子的编号
	int eatcolor;//如果发生吃棋行为,被吃棋子的颜色
}RegretChess;

typedef struct Chess {
	LONG lx;//左上角X坐标
	LONG ly;//左上角Y坐标
	LONG rx;//右下角X坐标
	LONG ry;//右下角Y坐标
	int color;//0代表黑色,1代表红色,-1代表棋子被吃了。
	int level;//兵为0,炮为1,车为2,马为3,相为4,士为5,帅为6。
}CHESS[32];

#define IniLx 30//棋盘左上角横坐标
#define IniLy 8//棋盘左上角纵坐标
#define IniRx 90//棋盘右下角横坐标
#define IniRy 68//棋盘右下角纵坐标

#define COLOR_CHESS RGB(177,127,75)//棋子背景颜色

#define COLOR_REDCHESS RGB(238,44,44)//红棋的字体颜色

#define COLOR_BLACKCHESS RGB(0,0,0)//黑棋的字体颜色

#define COLOR_BOUNDARY	RGB(205, 55, 0)//选中棋子时,出现的红色边框颜色

#define CHESS_LENGTH 60//每格棋盘的边长

#define MAX_X 600//背景分辨率
#define MAX_Y 611//背景分辨率

#define BITMAP_FILE_BK "back.bmp"//背景图片文件名

CHESS chess[32];//32个棋子
/*左上角第一个棋子的坐标是（30,8）（90,68）*/

LONG recordChess;//记录选中的棋子

RegretChess temprecord0;//悔棋时上一步棋子的坐标,记录黑棋
RegretChess temprecord1;//悔棋时上一步棋子的坐标,记录红棋

NextChessPlace Ncp;//记录选中区域的结构体变量

int order;//记录下棋者颜色,0代表黑色,1为红色

/*ui.c*/
BOOL WindwowRegister(HINSTANCE hinstance);

HWND WindowCreate(HINSTANCE hinstance);

LONG CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM iParam);

LONG CreateIniGame();

LONG PaintGame(HWND hwnd);

void ReSizeGameWnd(HWND hwnd);

void OnKeyDown(DWORD vk);

DWORD WINAPI PlayMusic(LPVOID IpParam);

DWORD WINAPI ChooseCHESS(LPVOID IpParam);

DWORD WINAPI DownCHESS(LPVOID IpParam);

DWORD WINAPI RegretCHESS(LPVOID IpParam);

DWORD WINAPI CheckCHESS(LPVOID IpParam);

/*ChessMove.c*/
void CreateChess();

void NextChess(LONG x, LONG y);

BOOL ChessRuler(LONG x, LONG y);

int isChess(LONG lx, LONG ly, LONG rx, LONG ry);

void EatChess(LONG lx, LONG ly, LONG rx, LONG ry);

void MoveChess();

BOOL GetMoveChessPlace(LONG x, LONG y);

void GetChessInformation(LONG x, LONG y);

void Regretchess();

void SaveChess();

BOOL GameOver();

/*ChessRuler.c*/
BOOL BlackKingRuler();

BOOL RedKingRuler();

BOOL BlackRetinueRuler();

BOOL RedRetinueRuler();

BOOL BlackElephantRuler();

BOOL RedElephantRuler();

BOOL HouseRuler();

BOOL CarRuler();

BOOL CannonRuler();

int isFreeLine();

BOOL BlackSoldiersRuler();

BOOL RedSoldiersRuler();

BOOL RedKingWillDie();

BOOL BlackKingWillDie();

int isFreeLineWD(LONG x1, LONG y1, LONG x2, LONG y2
	, LONG lx, LONG ly, LONG rx, LONG ry);

BOOL HouseRulerWD(LONG x1, LONG y1, LONG x2, LONG y2
	, LONG lx, LONG ly, LONG rx, LONG ry);