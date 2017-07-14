#include<windows.h> 

#include<stdlib.h> 

#include <mmsystem.h>

#pragma comment (lib,"Winmm.lib")

typedef struct//�洢ѡ����������Ľṹ��
{
	LONG lx;//�������ϽǺ�����
	LONG ly;//�������Ͻ�������
	LONG rx;//�������½Ǻ�����
	LONG ry;//�������½�������
}NextChessPlace;

typedef struct//Ϊ�˽��л������,�����洢���ӵ������Ϣ
{
	LONG lx;//��һ�����ӵ����Ͻǵĺ�����
	LONG ly;//��һ�����ӵ����Ͻǵ�������
	LONG rx;//��һ�����ӵ����½ǵĺ�����
	LONG ry;//��һ�����ӵ����½ǵ�������
	LONG number;//���ӵı��
	int color;//���ӵ���ɫ
	int eat;//�������������Ϊ,�������ӵı��
	int eatcolor;//�������������Ϊ,�������ӵ���ɫ
}RegretChess;

typedef struct Chess {
	LONG lx;//���Ͻ�X����
	LONG ly;//���Ͻ�Y����
	LONG rx;//���½�X����
	LONG ry;//���½�Y����
	int color;//0�����ɫ,1�����ɫ,-1�������ӱ����ˡ�
	int level;//��Ϊ0,��Ϊ1,��Ϊ2,��Ϊ3,��Ϊ4,ʿΪ5,˧Ϊ6��
}CHESS[32];

#define IniLx 30//�������ϽǺ�����
#define IniLy 8//�������Ͻ�������
#define IniRx 90//�������½Ǻ�����
#define IniRy 68//�������½�������

#define COLOR_CHESS RGB(177,127,75)//���ӱ�����ɫ

#define COLOR_REDCHESS RGB(238,44,44)//�����������ɫ

#define COLOR_BLACKCHESS RGB(0,0,0)//�����������ɫ

#define COLOR_BOUNDARY	RGB(205, 55, 0)//ѡ������ʱ,���ֵĺ�ɫ�߿���ɫ

#define CHESS_LENGTH 60//ÿ�����̵ı߳�

#define MAX_X 600//�����ֱ���
#define MAX_Y 611//�����ֱ���

#define BITMAP_FILE_BK "back.bmp"//����ͼƬ�ļ���

CHESS chess[32];//32������
/*���Ͻǵ�һ�����ӵ������ǣ�30,8����90,68��*/

LONG recordChess;//��¼ѡ�е�����

RegretChess temprecord0;//����ʱ��һ�����ӵ�����,��¼����
RegretChess temprecord1;//����ʱ��һ�����ӵ�����,��¼����

NextChessPlace Ncp;//��¼ѡ������Ľṹ�����

int order;//��¼��������ɫ,0�����ɫ,1Ϊ��ɫ

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