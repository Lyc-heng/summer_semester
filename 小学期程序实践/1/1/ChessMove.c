#include "ChineseChess.h"

/*关于象棋移动、悔棋的相关操作*/
void CreateChess() //对32个棋子初始化
{
	int i;
	/*红兵初始化*/
	for (i = 0; i < 5; ++i)
	{
		chess[i]->lx = IniLx + 2 * i * CHESS_LENGTH;
		chess[i]->ly = IniLy + CHESS_LENGTH * 3;
		chess[i]->rx = IniRx + 2 * i * CHESS_LENGTH;
		chess[i]->ry = IniRy + CHESS_LENGTH * 3;
		chess[i]->color = 1;
		chess[i]->level = 0;
	}
	/*红炮初始化*/
	chess[5]->lx = IniLx + CHESS_LENGTH;
	chess[5]->ly = IniLy + CHESS_LENGTH * 2;
	chess[5]->rx = IniRx + CHESS_LENGTH;
	chess[5]->ry = IniRy + CHESS_LENGTH * 2;
	chess[5]->color = 1;
	chess[5]->level = 1;
	chess[6]->lx = IniLx + CHESS_LENGTH * 7;
	chess[6]->ly = IniLy + CHESS_LENGTH * 2;
	chess[6]->rx = IniRx + CHESS_LENGTH * 7;
	chess[6]->ry = IniRy + CHESS_LENGTH * 2;
	chess[6]->color = 1;
	chess[6]->level = 1;
	/*红车初始化*/
	chess[7]->lx = IniLx;
	chess[7]->ly = IniLy;
	chess[7]->rx = IniRx;
	chess[7]->ry = IniRy;
	chess[7]->color = 1;
	chess[7]->level = 2;
	chess[8]->lx = IniLx + CHESS_LENGTH * 8;
	chess[8]->ly = IniLy;
	chess[8]->rx = IniRx + CHESS_LENGTH * 8;
	chess[8]->ry = IniRy;
	chess[8]->color = 1;
	chess[8]->level = 2;
	/*红马初始化*/
	chess[9]->lx = IniLx + CHESS_LENGTH * 1;
	chess[9]->ly = IniLy;
	chess[9]->rx = IniRx + CHESS_LENGTH * 1;
	chess[9]->ry = IniRy;
	chess[9]->color = 1;
	chess[9]->level = 3;
	chess[10]->lx = IniLx + CHESS_LENGTH * 7;
	chess[10]->ly = IniLy;
	chess[10]->rx = IniRx + CHESS_LENGTH * 7;
	chess[10]->ry = IniRy;
	chess[10]->color = 1;
	chess[10]->level = 3;
	/*红象初始化*/
	chess[11]->lx = IniLx + CHESS_LENGTH * 2;
	chess[11]->ly = IniLy;
	chess[11]->rx = IniRx + CHESS_LENGTH * 2;
	chess[11]->ry = IniRy;
	chess[11]->color = 1;
	chess[11]->level = 4;
	chess[12]->lx = IniLx + CHESS_LENGTH * 6;
	chess[12]->ly = IniLy;
	chess[12]->rx = IniRx + CHESS_LENGTH * 6;
	chess[12]->ry = IniRy;
	chess[12]->color = 1;
	chess[12]->level = 4;
	/*红士初始化*/
	chess[13]->lx = IniLx + CHESS_LENGTH * 3;
	chess[13]->ly = IniLy;
	chess[13]->rx = IniRx + CHESS_LENGTH * 3;
	chess[13]->ry = IniRy;
	chess[13]->color = 1;
	chess[13]->level = 5;
	chess[14]->lx = IniLx + CHESS_LENGTH * 5;
	chess[14]->ly = IniLy;
	chess[14]->rx = IniRx + CHESS_LENGTH * 5;
	chess[14]->ry = IniRy;
	chess[14]->color = 1;
	chess[14]->level = 5;
	/*红帅初始化*/
	chess[15]->lx = IniLx + CHESS_LENGTH * 4;
	chess[15]->ly = IniLy;
	chess[15]->rx = IniRx + CHESS_LENGTH * 4;
	chess[15]->ry = IniRy;
	chess[15]->color = 1;
	chess[15]->level = 6;
	/*红方初始化完毕现在开始黑方初始化*/

	/*黑兵初始化*/
	int j = 0;
	for (i = 16; i < 21; ++i)
	{
		chess[i]->lx = IniLx + 2 * j * CHESS_LENGTH;
		chess[i]->ly = IniLy + CHESS_LENGTH * 6;
		chess[i]->rx = IniRx + 2 * j * CHESS_LENGTH;
		chess[i]->ry = IniRy + CHESS_LENGTH * 6;
		chess[i]->color = 0;
		chess[i]->level = 0;
		j++;
	}
	/*黑炮初始化*/
	chess[21]->lx = IniLx + CHESS_LENGTH * 1;
	chess[21]->ly = IniLy + CHESS_LENGTH * 7;
	chess[21]->rx = IniRx + CHESS_LENGTH * 1;
	chess[21]->ry = IniRy + CHESS_LENGTH * 7;
	chess[21]->color = 0;
	chess[21]->level = 1;
	chess[22]->lx = IniLx + CHESS_LENGTH * 7;
	chess[22]->ly = IniLy + CHESS_LENGTH * 7;
	chess[22]->rx = IniRx + CHESS_LENGTH * 7;
	chess[22]->ry = IniRy + CHESS_LENGTH * 7;
	chess[22]->color = 0;
	chess[22]->level = 1;
	/*初始化车*/
	chess[23]->lx = IniLx;
	chess[23]->ly = IniLy + CHESS_LENGTH * 9;
	chess[23]->rx = IniRx;
	chess[23]->ry = IniRy + CHESS_LENGTH * 9;
	chess[23]->color = 0;
	chess[23]->level = 2;
	chess[24]->lx = IniLx + CHESS_LENGTH * 8;
	chess[24]->ly = IniLy + CHESS_LENGTH * 9;
	chess[24]->rx = IniRx + CHESS_LENGTH * 8;
	chess[24]->ry = IniRy + CHESS_LENGTH * 9;
	chess[24]->color = 0;
	chess[24]->level = 2;
	/*初始化马*/
	chess[25]->lx = IniLx + CHESS_LENGTH * 1;
	chess[25]->ly = IniLy + CHESS_LENGTH * 9;
	chess[25]->rx = IniRx + CHESS_LENGTH * 1;
	chess[25]->ry = IniRy + CHESS_LENGTH * 9;
	chess[25]->color = 0;
	chess[25]->level = 3;
	chess[26]->lx = IniLx + CHESS_LENGTH * 7;
	chess[26]->ly = IniLy + CHESS_LENGTH * 9;
	chess[26]->rx = IniRx + CHESS_LENGTH * 7;
	chess[26]->ry = IniRy + CHESS_LENGTH * 9;
	chess[26]->color = 0;
	chess[26]->level = 3;
	/*初始化象*/
	chess[27]->lx = IniLx + CHESS_LENGTH * 2;
	chess[27]->ly = IniLy + CHESS_LENGTH * 9;
	chess[27]->rx = IniRx + CHESS_LENGTH * 2;
	chess[27]->ry = IniRy + CHESS_LENGTH * 9;
	chess[27]->color = 0;
	chess[27]->level = 4;
	chess[28]->lx = IniLx + CHESS_LENGTH * 6;
	chess[28]->ly = IniLy + CHESS_LENGTH * 9;
	chess[28]->rx = IniRx + CHESS_LENGTH * 6;
	chess[28]->ry = IniRy + CHESS_LENGTH * 9;
	chess[28]->color = 0;
	chess[28]->level = 4;
	/*初始化士*/
	chess[29]->lx = IniLx + CHESS_LENGTH * 3;
	chess[29]->ly = IniLy + CHESS_LENGTH * 9;
	chess[29]->rx = IniRx + CHESS_LENGTH * 3;
	chess[29]->ry = IniRy + CHESS_LENGTH * 9;
	chess[29]->color = 0;
	chess[29]->level = 5;
	chess[IniLx]->lx = IniLx + CHESS_LENGTH * 5;
	chess[IniLx]->ly = IniLy + CHESS_LENGTH * 9;
	chess[IniLx]->rx = IniRx + CHESS_LENGTH * 5;
	chess[IniLx]->ry = IniRy + CHESS_LENGTH * 9;
	chess[IniLx]->color = 0;
	chess[IniLx]->level = 5;
	/*将的初始化*/
	chess[31]->lx = IniLx + CHESS_LENGTH * 4;
	chess[31]->ly = IniLy + CHESS_LENGTH * 9;
	chess[31]->rx = IniRx + CHESS_LENGTH * 4;
	chess[31]->ry = IniRy + CHESS_LENGTH * 9;
	chess[31]->color = 0;
	chess[31]->level = 6;
	/*对记录选中棋子的变量初始化*/
	recordChess = -1;
}

void NextChess(LONG x, LONG y)//对棋子移动继续判断的函数
{
	if (GetMoveChessPlace(x, y)) {
		//0代表要移动去的位置为棋子,1为有敌军棋子,2为有友军棋子
		switch (isChess(Ncp.lx, Ncp.ly, Ncp.rx, Ncp.ry))
		{
		case 0:
			if (ChessRuler(x, y) == TRUE)
			{
				SaveChess();//移动前先将现在位置保存下来
				MoveChess();
			}
			break;
		case 1:
			if (ChessRuler(x, y) == TRUE)
			{
				SaveChess();//移动前先将现在位置保存下来
				EatChess(Ncp.lx, Ncp.ly, Ncp.rx, Ncp.ry);
				MoveChess();
			}
			//单独对炮和车进行判断
			if (isFreeLine() == 2 && chess[recordChess]->level == 1)
			{
				SaveChess();//移动前先将现在位置保存下来
				EatChess(Ncp.lx, Ncp.ly, Ncp.rx, Ncp.ry);
				MoveChess();
			}
			if (isFreeLine() == 1 && chess[recordChess]->level == 2)
			{
				SaveChess();//移动前先将现在位置保存下来
				EatChess(Ncp.lx, Ncp.ly, Ncp.rx, Ncp.ry);
				MoveChess();
			}
			break;
		case 3:
			GetChessInformation(Ncp.lx + 1, Ncp.ly + 1);
			break;
		default:
			break;
		}
	}
}

BOOL ChessRuler(LONG x, LONG y)//对棋子这样的走法是否符合规则进行判断
{
	switch (chess[recordChess]->level)
	{
	case 0:
		if (chess[recordChess]->color == 0 && BlackSoldiersRuler() != FALSE) {
			return TRUE;
		}

		if (chess[recordChess]->color == 1 && RedSoldiersRuler() != FALSE)
		{
			return TRUE;
		}
		break;
	case 1:
		if (CannonRuler() == TRUE)
		{
			return TRUE;
		}
		break;
	case 2:
		if (CarRuler() == TRUE)
		{
			return TRUE;
		}
		break;
	case 3:
		if (HouseRuler() == TRUE)
		{
			return TRUE;
		}
		break;
	case 4:
		if (chess[recordChess]->color == 0 && BlackElephantRuler() == TRUE)
		{
			return TRUE;
		}
		if (chess[recordChess]->color == 1 && RedElephantRuler() == TRUE)
		{
			return TRUE;
		}
		break;
	case 5:
		if (chess[recordChess]->color == 0 && BlackRetinueRuler() == TRUE)
		{
			return TRUE;
		}
		if (chess[recordChess]->color == 1 && RedRetinueRuler() == TRUE)
		{
			return TRUE;
		}
		break;
	case 6:
		if (chess[recordChess]->color == 0 && BlackKingRuler() == TRUE)
		{
			return TRUE;
		}
		if (chess[recordChess]->color == 1 && RedKingRuler() == TRUE)
		{
			return TRUE;
		}
		break;
	}
	return FALSE;
}

int isChess(LONG lx, LONG ly, LONG rx, LONG ry)//判断下的位置有没有棋子
{
	for (int i = 0; i < 32; ++i)
	{
		if (chess[i]->lx == lx
			&&chess[i]->ly == ly
			&&chess[i]->rx == rx
			&&chess[i]->ry == ry
			&&chess[i]->color != -1)
		{
			if (chess[i]->color == chess[recordChess]->color)
			{
				return 3;//有且为友军
			}
			else
			{
				return 1;//有且为敌军
			}
		}
	}
	return 0;//没有
}

void EatChess(LONG lx, LONG ly, LONG rx, LONG ry)//吃棋,将被吃棋子颜色变为-1
{
	for (int i = 0; i < 32; ++i)
	{
		if (chess[i]->lx == lx
			&&chess[i]->ly == ly
			&&chess[i]->rx == rx
			&&chess[i]->ry == ry
			&&chess[i]->color != -1)
		{
			//以下这个If循环时为悔棋步骤设立
			if ((order-1) % 2 == 0)
			{
				temprecord0.eat = i;
				temprecord0.eatcolor = chess[i]->color;
				
			}
			else
			{
				temprecord1.eat = i;
				temprecord1.eatcolor = chess[i]->color;
				
			}
			chess[i]->color = -1;
		}
	}
}

void MoveChess()//移动棋子的函数
{

	chess[recordChess]->lx = Ncp.lx;
	chess[recordChess]->ly = Ncp.ly;
	chess[recordChess]->rx = Ncp.rx;
	chess[recordChess]->ry = Ncp.ry;

	recordChess = -1;
	//落棋子的声音
	CreateThread(NULL, 0, DownCHESS, NULL, 0, NULL);
}

BOOL GetMoveChessPlace(LONG x, LONG y)//得到想下的位置的坐标属于哪个小格
{
	int i;
	int j;
	if (x > 30 && y > 8 && x < 570 && y < 608)
	{
		for (i = 0; i < 9; ++i)
		{
			for (j = 0; j < 10; ++j)
			{
				if (x > IniLx + CHESS_LENGTH * i
					&&y > IniLy + CHESS_LENGTH * j
					&&x < IniRx + CHESS_LENGTH * i
					&&IniRy + CHESS_LENGTH * j)
				{
					Ncp.lx = IniLx + CHESS_LENGTH * i;
					Ncp.ly = IniLy + CHESS_LENGTH * j;
					Ncp.rx = IniRx + CHESS_LENGTH * i;
					Ncp.ry = IniRy + CHESS_LENGTH * j;
				}
			}
		}
		return TRUE;
	}
	else
	{
		MessageBox(NULL, "您必须下在棋盘内", "Warning", MB_OK | MB_ICONERROR);
	}

	return FALSE;
}

void GetChessInformation(LONG x, LONG y)//得到选中的棋子的编号
{
	int flag = 0;

	for (int i = 0; i < 32 && flag == 0; ++i)
	{
		if (chess[i]->color != -1 && chess[i]->lx<x&&chess[i]->ly<y&&chess[i]->rx>x&&chess[i]->ry>y)
		{
			flag = 1;
			recordChess = i;
			//选中棋子的声音
			CreateThread(NULL, 0, ChooseCHESS, NULL, 0, NULL);
		}
	}
}

void Regretchess()
{
	if (order >= 2)//只有当进行了两步以上的操作时才能执行悔棋操作
	{
		//恢复黑棋
		chess[temprecord0.number]->lx = temprecord0.lx;
		chess[temprecord0.number]->ly = temprecord0.ly;
		chess[temprecord0.number]->rx = temprecord0.rx;
		chess[temprecord0.number]->ry = temprecord0.ry;
		chess[temprecord0.number]->color = temprecord0.color;

		if (temprecord0.eat != -1)//黑棋在前两步棋中发生了吃棋操作
		{
			chess[temprecord0.eat]->color = temprecord0.eatcolor;
		}

		//恢复红棋
		chess[temprecord1.number]->lx = temprecord1.lx;
		chess[temprecord1.number]->ly = temprecord1.ly;
		chess[temprecord1.number]->rx = temprecord1.rx;
		chess[temprecord1.number]->ry = temprecord1.ry;
		chess[temprecord1.number]->color = temprecord1.color;

		if (temprecord1.eat != -1)//红棋在前两步进行了吃棋操作
		{
			chess[temprecord1.eat]->color = temprecord1.eatcolor;
		}
		/*悔棋时的声音*/
		CreateThread(NULL, 0, ChooseCHESS, NULL, 0, NULL);
	}
}

void SaveChess()//将两步的操作进行记录,方便进行悔棋操作
{
	if ((order-1) % 2 == 0)
	{
		temprecord0.lx = chess[recordChess]->lx;
		temprecord0.ly = chess[recordChess]->ly;
		temprecord0.rx = chess[recordChess]->rx;
		temprecord0.ry = chess[recordChess]->ry;
		temprecord0.number = recordChess;
		temprecord0.color = chess[recordChess]->color;
		temprecord0.eat = -1;
		
	}

	if ((order-1) % 2 == 1)
	{
		temprecord1.lx = chess[recordChess]->lx;
		temprecord1.ly = chess[recordChess]->ly;
		temprecord1.rx = chess[recordChess]->rx;
		temprecord1.ry = chess[recordChess]->ry;
		temprecord1.number = recordChess;
		temprecord1.color = chess[recordChess]->color;
		temprecord1.eat = -1;
		
	}
}

BOOL GameOver()//判断游戏是否结束
{
	if (chess[15]->color == -1 || chess[31]->color == -1)
	{
		MessageBox(NULL, "游戏结束", "中国象棋", MB_OKCANCEL);
		return TRUE;
	}

	return FALSE;
}
