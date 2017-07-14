#include "ChineseChess.h"

/*******************************************/
//全局变量
HWND hwndBackground;//背景图片

RECT rectBoundary;//边界坐标
/*******************************************/

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstanc, LPSTR lpCmdLine, int nShowCmd)

{
	BOOL  fGotMessage;

	MSG msg;

	if (WindwowRegister(hinstance)) {
		hwndBackground = WindowCreate(hinstance);
	}
	else {
		return 0;
	}

	while ((fGotMessage = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0
		&& fGotMessage != -1)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

BOOL WindwowRegister(HINSTANCE hinstance)
{
	WNDCLASS wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;

	wc.cbClsExtra = 0;

	wc.cbWndExtra = 0;

	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	wc.hCursor = LoadCursor(NULL, IDC_CROSS);

	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	wc.hInstance = hinstance;

	wc.lpfnWndProc = (WNDPROC)WindowProc;

	wc.lpszClassName = TEXT("中国象棋");

	wc.lpszMenuName = NULL;

	if (!RegisterClass(&wc))

	{

		MessageBox(NULL, TEXT("注册失败"), TEXT("警告框"), MB_ICONERROR);

		return FALSE;

	}
	return TRUE;
}

HWND WindowCreate(HINSTANCE hinstance)
{
	HWND hwnd;

	TCHAR szClassName[] = TEXT("中国象棋");

	hwnd = CreateWindow(szClassName, szClassName,

		WS_OVERLAPPEDWINDOW,

		CW_USEDEFAULT, CW_USEDEFAULT,

		CW_USEDEFAULT, CW_USEDEFAULT,

		NULL, NULL, hinstance, NULL);

	if (!hwnd)
	{
		// 窗口创建失败，消息框提示，并退出。
		MessageBox(NULL, "创建窗口失败", "错误！", MB_ICONERROR | MB_OK);
		return NULL;
	}

	ShowWindow(hwnd, SW_SHOW);

	UpdateWindow(hwnd);

	return hwnd;
}

LONG CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM iParam)
{
	RECT rectNew;
	POINT pos;
	
	switch (msg)
	{
	
	case WM_CREATE:
		CreateIniGame();
		ReSizeGameWnd(hwnd);
		break;

	case WM_PAINT:
		PaintGame(hwnd);
		break;

	case WM_MOVING:
		break;

	case WM_SIZE:
		ReSizeGameWnd(hwnd);
		break;

	case WM_KEYDOWN:
		OnKeyDown(wParam);
		PaintGame(hwnd);
		break;

	case WM_LBUTTONDOWN:
		pos.x = LOWORD(iParam);
		pos.y = HIWORD(iParam);

		/*先获得棋子的相关信息,再对棋子的移动进行判断*/
		if (recordChess == -1)
		{
			GetChessInformation(pos.x, pos.y);
			PaintGame(hwnd);
			//下面这个IF循环是为了使红黑双方能交替下棋且不会干扰对方而设立
			if (order % 2 == chess[recordChess]->color&&recordChess != -1)
			{
				order++;
			}
			else
			{
				recordChess = -1;
			}

		}
		else
		{
			//获得了棋子的信息后
			NextChess(pos.x, pos.y);
			PaintGame(hwnd);
			//如果将军了时,播放音乐
			if (RedKingWillDie() == TRUE)
			{
				CreateThread(NULL, 0, CheckCHESS, NULL, 0, NULL);
			}
			if (BlackKingWillDie() == TRUE)
			{
				CreateThread(NULL, 0, CheckCHESS, NULL, 0, NULL);
			}
		}

		GameOver();

		break;

	case WM_TIMER:
		break;

	case WM_DESTROY:
		ExitProcess(0);
		break;

	default:
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, iParam);

}

LONG PaintGame(HWND hwnd)
{
	HPEN hpen;
	HPEN hOldPen;
	HPEN hPenBoundary;

	HBRUSH hbrushChess;
	HBRUSH hOldBrush;

	HFONT hFont, hOldFont;
	HFONT hBfont, hRfont;

	RECT rect;

	HDC hdc, hdcmem;

	BITMAP bmap;

	GetClientRect(hwnd, &rect);
	hdc = GetDC(hwnd);
	hdcmem = CreateCompatibleDC(hdc);
	

	hbrushChess = CreateSolidBrush(COLOR_CHESS);
	hpen = CreatePen(PS_NULL, 0, COLOR_BLACKCHESS);
	hPenBoundary = CreatePen(PS_SOLID, 3, COLOR_BOUNDARY);
	hBfont = CreatePen(PS_INSIDEFRAME, 5, COLOR_BLACKCHESS);
	hRfont = CreatePen(PS_INSIDEFRAME, 5, COLOR_REDCHESS);
	//画棋盘
	HANDLE hbitmap = LoadImage(NULL, BITMAP_FILE_BK,
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (hbitmap == NULL)
	{
		MessageBox(hwnd, "bmp file not find", "ERROR!",
			MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}

	GetObject(hbitmap, sizeof(BITMAP), &bmap);

	SelectObject(hdcmem, hbitmap);

	//画棋子,并写字,并画出选中特效
	/*-------------------每个小格为（60,60），棋盘左上角（60,38）-------------------*/

	hFont = CreateFont(IniLx, 15, 0, 0, FW_BLACK, 0, 0, 0, GB2312_CHARSET
		, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));

	hOldBrush = (HBRUSH)SelectObject(hdcmem, hbrushChess);
	hOldPen = (HPEN)SelectObject(hdcmem, hpen);

	for (int i = 0; i < 32; ++i)
	{
		if (chess[i]->color != -1)
		{

			Ellipse(hdcmem, chess[i]->lx, chess[i]->ly, chess[i]->rx, chess[i]->ry);

			// 将这个FONT对象放入DC中
			if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))
			{
				CHAR szSourceInfo[10];
				switch (chess[i]->level)
				{
				case 0:
					if (chess[i]->color == 0)
					{
						wsprintf(szSourceInfo, "卒", 0);
					}
					else
					{
						wsprintf(szSourceInfo, "兵", 0);
					}
					break;
				case 1:
					wsprintf(szSourceInfo, "炮", 0);
					break;
				case 2:
					wsprintf(szSourceInfo, "车", 0);
					break;
				case 3:
					wsprintf(szSourceInfo, "马", 0);
					break;
				case 4:
					wsprintf(szSourceInfo, "象", 0);
					break;
				case 5:
					wsprintf(szSourceInfo, "士", 0);
					break;
				case 6:
					if (chess[i]->color == 0)
					{
						wsprintf(szSourceInfo, "将", 0);
					}
					else
					{
						wsprintf(szSourceInfo, "帅", 0);
					}
					break;
				default:
					MessageBox(NULL, "没有符合等级的棋子", "错误！", MB_ICONERROR | MB_OK);
					break;
				}
				// 设置输出颜色
				if (chess[i]->color == 1) {
					SetTextColor(hdcmem, COLOR_REDCHESS);
				}
				else {
					SetTextColor(hdcmem, COLOR_BLACKCHESS);
				}
				SetBkMode(hdcmem, TRANSPARENT);//设置输出字背景透明

				TextOut(hdcmem, chess[i]->lx + 15, chess[i]->ly + 15, szSourceInfo, lstrlen(szSourceInfo)); // 输出字符串。

				SelectObject(hdcmem, hOldFont);// 输出完成，将原来的字体对象放回DC中
			}
		}
	}

	//画选中了一个棋子的特效
	if (recordChess != -1)
	{
		SelectObject(hdcmem, hPenBoundary);
		SelectObject(hdcmem, GetStockObject(NULL_BRUSH));

		Ellipse(hdcmem,
			chess[recordChess]->lx + 5,
			chess[recordChess]->ly + 5,
			chess[recordChess]->rx - 5,
			chess[recordChess]->ry - 5);
	}

	//画出了图片
	BitBlt(hdc, 0, 0, MAX_X, MAX_Y, hdcmem, 0, 0, SRCCOPY);

	DeleteObject(hdcmem);

	DeleteObject(hbrushChess);

	DeleteObject(hpen);

	DeleteObject(hBfont);

	DeleteObject(hRfont);

	DeleteObject(hbitmap);

	DeleteObject(hPenBoundary);

	ReleaseDC(hwnd, hdc);
	return 0;

}

void ReSizeGameWnd(HWND hwnd)
{
	POINT ptLeftTop;		// 左上角
	POINT ptRightBottom;	// 右下角
	RECT rectWindow;

	// 设置
	rectBoundary.left = 10;
	rectBoundary.top = 10;
	rectBoundary.right = 620;
	rectBoundary.bottom = 655;

	// 计算上下左右角的位置
	ptLeftTop.x = rectBoundary.left;
	ptLeftTop.y = rectBoundary.top;
	ptRightBottom.x = rectBoundary.right;
	ptRightBottom.y = rectBoundary.bottom;
	ClientToScreen(hwnd, &ptLeftTop);
	ClientToScreen(hwnd, &ptRightBottom);

	GetWindowRect(hwnd, &rectWindow);
	// 计算好了，设置窗口大小。
	MoveWindow(hwnd,
		rectWindow.left,
		rectWindow.top,
		rectBoundary.right,
		rectBoundary.bottom,
		TRUE);
}

LONG CreateIniGame()
{
	order = 0;

	temprecord0.eat = -1;
	temprecord1.eat = -1;

	CreateThread(NULL, 0, PlayMusic, NULL, 0, NULL);

	CreateChess();

	return 0;
}

void OnKeyDown(DWORD vk)
{
	switch (vk) // virtual key value
	{
	case VK_LEFT:
		break;
	case VK_RIGHT:
		break;
	case VK_UP:
		break;
	case VK_DOWN:
		break;
	case 'S':
		//按下S键,可以重新开始游戏
			if (IDYES == MessageBox(NULL, "是否要游戏重新开始", "中国象棋", MB_YESNO))
			{
				CreateIniGame();
				order = 0;
			}
		break;
	case 'R':
		//按下R键，可以进行悔棋操作
		if (IDYES == MessageBox(NULL, "是否要悔棋", "中国象棋", MB_YESNO))
		{
			Regretchess();
		}
		break;
	default:
		break;
	}
}

DWORD WINAPI PlayMusic(LPVOID IpParam)//播放背景音乐的声音
{
	PlaySound(TEXT("墨明棋妙 - 二十二桥枫别雨.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	return 0;
}

DWORD WINAPI ChooseCHESS(LPVOID IpParam)//多线程播放选子的声音
{
	mciSendString("close Choose", 0, 0, 0);
	mciSendString(TEXT("open 选子.wav alias Choose"), NULL, 0, NULL);
	mciSendString("play Choose", 0, 0, 0);
	return 0;
}

DWORD WINAPI DownCHESS(LPVOID IpParam)//多线程播放落子的声音
{
	mciSendString("close Down", 0, 0, 0);
	mciSendString(TEXT("open 落子.wav alias Down"), NULL, 0, NULL);
	mciSendString("play Down", 0, 0, 0);
	return 0;
}

DWORD WINAPI RegretCHESS(LPVOID IpParam)////多线程播放悔棋的声音
{
	mciSendString("close Regret", 0, 0, 0);
	mciSendString(TEXT("open 悔棋.wav alias Regret"), NULL, 0, NULL);
	mciSendString("play Regret", 0, 0, 0);
	return 0;
}

DWORD WINAPI CheckCHESS(LPVOID IpParam)//多线程播放将军的声音
{
	mciSendString("close Check", 0, 0, 0);
	mciSendString(TEXT("open 将军.wav alias Check"), NULL, 0, NULL);
	mciSendString("play Check", 0, 0, 0);
	return 0;
}