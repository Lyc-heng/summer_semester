#include "ChineseChess.h"

/*******************************************/
//ȫ�ֱ���
HWND hwndBackground;//����ͼƬ

RECT rectBoundary;//�߽�����
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

	wc.lpszClassName = TEXT("�й�����");

	wc.lpszMenuName = NULL;

	if (!RegisterClass(&wc))

	{

		MessageBox(NULL, TEXT("ע��ʧ��"), TEXT("�����"), MB_ICONERROR);

		return FALSE;

	}
	return TRUE;
}

HWND WindowCreate(HINSTANCE hinstance)
{
	HWND hwnd;

	TCHAR szClassName[] = TEXT("�й�����");

	hwnd = CreateWindow(szClassName, szClassName,

		WS_OVERLAPPEDWINDOW,

		CW_USEDEFAULT, CW_USEDEFAULT,

		CW_USEDEFAULT, CW_USEDEFAULT,

		NULL, NULL, hinstance, NULL);

	if (!hwnd)
	{
		// ���ڴ���ʧ�ܣ���Ϣ����ʾ�����˳���
		MessageBox(NULL, "��������ʧ��", "����", MB_ICONERROR | MB_OK);
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

		/*�Ȼ�����ӵ������Ϣ,�ٶ����ӵ��ƶ������ж�*/
		if (recordChess == -1)
		{
			GetChessInformation(pos.x, pos.y);
			PaintGame(hwnd);
			//�������IFѭ����Ϊ��ʹ���˫���ܽ��������Ҳ�����ŶԷ�������
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
			//��������ӵ���Ϣ��
			NextChess(pos.x, pos.y);
			PaintGame(hwnd);
			//���������ʱ,��������
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
	//������
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

	//������,��д��,������ѡ����Ч
	/*-------------------ÿ��С��Ϊ��60,60�����������Ͻǣ�60,38��-------------------*/

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

			// �����FONT�������DC��
			if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))
			{
				CHAR szSourceInfo[10];
				switch (chess[i]->level)
				{
				case 0:
					if (chess[i]->color == 0)
					{
						wsprintf(szSourceInfo, "��", 0);
					}
					else
					{
						wsprintf(szSourceInfo, "��", 0);
					}
					break;
				case 1:
					wsprintf(szSourceInfo, "��", 0);
					break;
				case 2:
					wsprintf(szSourceInfo, "��", 0);
					break;
				case 3:
					wsprintf(szSourceInfo, "��", 0);
					break;
				case 4:
					wsprintf(szSourceInfo, "��", 0);
					break;
				case 5:
					wsprintf(szSourceInfo, "ʿ", 0);
					break;
				case 6:
					if (chess[i]->color == 0)
					{
						wsprintf(szSourceInfo, "��", 0);
					}
					else
					{
						wsprintf(szSourceInfo, "˧", 0);
					}
					break;
				default:
					MessageBox(NULL, "û�з��ϵȼ�������", "����", MB_ICONERROR | MB_OK);
					break;
				}
				// ���������ɫ
				if (chess[i]->color == 1) {
					SetTextColor(hdcmem, COLOR_REDCHESS);
				}
				else {
					SetTextColor(hdcmem, COLOR_BLACKCHESS);
				}
				SetBkMode(hdcmem, TRANSPARENT);//��������ֱ���͸��

				TextOut(hdcmem, chess[i]->lx + 15, chess[i]->ly + 15, szSourceInfo, lstrlen(szSourceInfo)); // ����ַ�����

				SelectObject(hdcmem, hOldFont);// �����ɣ���ԭ�����������Ż�DC��
			}
		}
	}

	//��ѡ����һ�����ӵ���Ч
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

	//������ͼƬ
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
	POINT ptLeftTop;		// ���Ͻ�
	POINT ptRightBottom;	// ���½�
	RECT rectWindow;

	// ����
	rectBoundary.left = 10;
	rectBoundary.top = 10;
	rectBoundary.right = 620;
	rectBoundary.bottom = 655;

	// �����������ҽǵ�λ��
	ptLeftTop.x = rectBoundary.left;
	ptLeftTop.y = rectBoundary.top;
	ptRightBottom.x = rectBoundary.right;
	ptRightBottom.y = rectBoundary.bottom;
	ClientToScreen(hwnd, &ptLeftTop);
	ClientToScreen(hwnd, &ptRightBottom);

	GetWindowRect(hwnd, &rectWindow);
	// ������ˣ����ô��ڴ�С��
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
		//����S��,�������¿�ʼ��Ϸ
			if (IDYES == MessageBox(NULL, "�Ƿ�Ҫ��Ϸ���¿�ʼ", "�й�����", MB_YESNO))
			{
				CreateIniGame();
				order = 0;
			}
		break;
	case 'R':
		//����R�������Խ��л������
		if (IDYES == MessageBox(NULL, "�Ƿ�Ҫ����", "�й�����", MB_YESNO))
		{
			Regretchess();
		}
		break;
	default:
		break;
	}
}

DWORD WINAPI PlayMusic(LPVOID IpParam)//���ű������ֵ�����
{
	PlaySound(TEXT("ī������ - ��ʮ���ŷ����.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	return 0;
}

DWORD WINAPI ChooseCHESS(LPVOID IpParam)//���̲߳���ѡ�ӵ�����
{
	mciSendString("close Choose", 0, 0, 0);
	mciSendString(TEXT("open ѡ��.wav alias Choose"), NULL, 0, NULL);
	mciSendString("play Choose", 0, 0, 0);
	return 0;
}

DWORD WINAPI DownCHESS(LPVOID IpParam)//���̲߳������ӵ�����
{
	mciSendString("close Down", 0, 0, 0);
	mciSendString(TEXT("open ����.wav alias Down"), NULL, 0, NULL);
	mciSendString("play Down", 0, 0, 0);
	return 0;
}

DWORD WINAPI RegretCHESS(LPVOID IpParam)////���̲߳��Ż��������
{
	mciSendString("close Regret", 0, 0, 0);
	mciSendString(TEXT("open ����.wav alias Regret"), NULL, 0, NULL);
	mciSendString("play Regret", 0, 0, 0);
	return 0;
}

DWORD WINAPI CheckCHESS(LPVOID IpParam)//���̲߳��Ž���������
{
	mciSendString("close Check", 0, 0, 0);
	mciSendString(TEXT("open ����.wav alias Check"), NULL, 0, NULL);
	mciSendString("play Check", 0, 0, 0);
	return 0;
}