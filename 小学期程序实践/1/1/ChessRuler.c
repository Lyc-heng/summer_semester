#include "ChineseChess.h"

/*关于象棋的相关规则和判断是否将军的相关函数*/
BOOL RedKingRuler()//红帅的移动规则
{
	//判断红帅在不在区域内
	if (Ncp.lx >= IniLx + CHESS_LENGTH * 3
		&& Ncp.ly >= IniLy
		&& Ncp.rx <= IniRx + CHESS_LENGTH * 5
		&& Ncp.ry <= IniRy + CHESS_LENGTH * 2)
	{
		//红帅可以走的规则
		if (chess[31]->lx != Ncp.lx || (chess[31]->lx == Ncp.lx&&KINGCantMeet())) {
			if ((Ncp.lx == chess[recordChess]->lx&&Ncp.ly == chess[recordChess]->ly + CHESS_LENGTH)
				|| (Ncp.lx == chess[recordChess]->lx&&Ncp.ly == chess[recordChess]->ly - CHESS_LENGTH)
				|| (Ncp.lx == chess[recordChess]->lx + CHESS_LENGTH && Ncp.ly == chess[recordChess]->ly)
				|| (Ncp.lx == chess[recordChess]->lx - CHESS_LENGTH && Ncp.ly == chess[recordChess]->ly))
			{
				return TRUE;
			}
		}
	}
	else//不在区域内
	{
		return FALSE;
	}
}

BOOL BlackKingRuler()//黑将的移动规则
{
	//黑将是否在区域内
	if (Ncp.lx >= IniLx + CHESS_LENGTH * 3
		&& Ncp.ly >= IniLy + CHESS_LENGTH * 7
		&& Ncp.rx <= IniRx + CHESS_LENGTH * 5
		&& Ncp.ry <= IniRy + CHESS_LENGTH * 9)
	{
		//黑将行走规则
		if (chess[15]->lx != Ncp.lx || (chess[15]->lx == Ncp.lx&&KINGCantMeet())) {
			if ((Ncp.lx == chess[recordChess]->lx&&Ncp.ly == chess[recordChess]->ly + CHESS_LENGTH)
				|| (Ncp.lx == chess[recordChess]->lx&&Ncp.ly == chess[recordChess]->ly - CHESS_LENGTH)
				|| (Ncp.lx == chess[recordChess]->lx + CHESS_LENGTH && Ncp.ly == chess[recordChess]->ly)
				|| (Ncp.lx == chess[recordChess]->lx - CHESS_LENGTH && Ncp.ly == chess[recordChess]->ly))
			{
				return TRUE;
			}
		}
	}
	else//点击的地方在可行区域外
	{
		return FALSE;
	}
}

BOOL KINGCantMeet()//将帅不能移动到一条无阻挡的直线上去
{
	for (int i = 0; i < 32; ++i)
	{
		if (chess[i]->lx == Ncp.lx&&chess[i]->ly > chess[15]->ly
			&&chess[i]->ry < chess[31]->ry)
		{
			return TRUE;
		}

	}
	return FALSE;
}

BOOL RedRetinueRuler()//红士的移动规则
{
	//判断在红方田字区域内
	if (Ncp.lx >= IniLx + CHESS_LENGTH * 3
		&& Ncp.ly >= IniLy
		&& Ncp.rx <= IniRx + CHESS_LENGTH * 5
		&& Ncp.ry <= IniRy + CHESS_LENGTH * 2)
	{
		/*士行走规则*/
		if ((Ncp.lx == chess[recordChess]->lx - CHESS_LENGTH&&Ncp.ly == chess[recordChess]->ly - CHESS_LENGTH)
			|| (Ncp.lx == chess[recordChess]->lx + CHESS_LENGTH&&Ncp.ly == chess[recordChess]->ly - CHESS_LENGTH)
			|| (Ncp.lx == chess[recordChess]->lx - CHESS_LENGTH&&Ncp.ly == chess[recordChess]->ly + CHESS_LENGTH)
			|| (Ncp.lx == chess[recordChess]->lx + CHESS_LENGTH&&Ncp.ly == chess[recordChess]->ly + CHESS_LENGTH))
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL BlackRetinueRuler()//黑士的移动规则
{
	//判断在黑方区域内
	if (Ncp.lx >= IniLx + CHESS_LENGTH * 3
		&& Ncp.ly >= IniLy + CHESS_LENGTH * 7
		&& Ncp.rx <= IniRx + CHESS_LENGTH * 5
		&& Ncp.ry <= IniRy + CHESS_LENGTH * 9)
	{
		/*士行走规则*/
		if ((Ncp.lx == chess[recordChess]->lx - CHESS_LENGTH&&Ncp.ly == chess[recordChess]->ly - CHESS_LENGTH)
			|| (Ncp.lx == chess[recordChess]->lx + CHESS_LENGTH&&Ncp.ly == chess[recordChess]->ly - CHESS_LENGTH)
			|| (Ncp.lx == chess[recordChess]->lx - CHESS_LENGTH&&Ncp.ly == chess[recordChess]->ly + CHESS_LENGTH)
			|| (Ncp.lx == chess[recordChess]->lx + CHESS_LENGTH&&Ncp.ly == chess[recordChess]->ly + CHESS_LENGTH))
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL RedElephantRuler()//红象的移动规则
{
	//判断红象移动的位置是否还在本方的区域内
	if (Ncp.lx >= IniLx && Ncp.ly <= IniLy + CHESS_LENGTH * 4 && Ncp.rx <= IniRx + CHESS_LENGTH * 8)
	{
		
		//判断左上角可以下吗
		if (Ncp.lx == chess[recordChess]->lx - CHESS_LENGTH * 2 && Ncp.ly == chess[recordChess]->ly - CHESS_LENGTH * 2
			&& Ncp.rx == chess[recordChess]->rx - CHESS_LENGTH * 2 && Ncp.ry == chess[recordChess]->ry - CHESS_LENGTH * 2)
		{
			//判断会堵象眼吗
			if (!isChess(chess[recordChess]->lx - CHESS_LENGTH, chess[recordChess]->ly - CHESS_LENGTH, chess[recordChess]->rx - CHESS_LENGTH, chess[recordChess]->ry - CHESS_LENGTH))
			{
				return TRUE;
			}
		}

		//判断右上角可以下吗
		if (Ncp.lx == chess[recordChess]->lx + CHESS_LENGTH * 2 && Ncp.ly == chess[recordChess]->ly - CHESS_LENGTH * 2
			&& Ncp.rx == chess[recordChess]->rx + CHESS_LENGTH * 2 && Ncp.ry == chess[recordChess]->ry - CHESS_LENGTH * 2)
		{
			//判断会堵象眼吗
			if (!isChess(chess[recordChess]->lx + CHESS_LENGTH, chess[recordChess]->ly - CHESS_LENGTH, chess[recordChess]->rx + CHESS_LENGTH, chess[recordChess]->ry - CHESS_LENGTH))
			{
				return TRUE;
			}
		}

		//判断右下角可以下吗
		if (Ncp.lx == chess[recordChess]->lx + CHESS_LENGTH * 2 && Ncp.ly == chess[recordChess]->ly + CHESS_LENGTH * 2
			&& Ncp.rx == chess[recordChess]->rx + CHESS_LENGTH * 2 && Ncp.ry == chess[recordChess]->ry + CHESS_LENGTH * 2)
		{
			//判断会堵象眼吗
			if (!isChess(chess[recordChess]->lx + CHESS_LENGTH, chess[recordChess]->ly + CHESS_LENGTH, chess[recordChess]->rx + CHESS_LENGTH, chess[recordChess]->ry + CHESS_LENGTH))
			{
				return TRUE;
			}
		}

		//判断左下角可以下吗
		if (Ncp.lx == chess[recordChess]->lx - CHESS_LENGTH * 2 && Ncp.ly == chess[recordChess]->ly + CHESS_LENGTH * 2
			&& Ncp.rx == chess[recordChess]->rx - CHESS_LENGTH * 2 && Ncp.ry == chess[recordChess]->ry + CHESS_LENGTH * 2)
		{
			//判断会堵象眼吗
			if (!isChess(chess[recordChess]->lx - CHESS_LENGTH, chess[recordChess]->ly + CHESS_LENGTH, chess[recordChess]->rx - CHESS_LENGTH, chess[recordChess]->ry + CHESS_LENGTH))
			{
				return TRUE;
			}
		}

	}
	return FALSE;
}

BOOL BlackElephantRuler()//黑象的移动规则
{
	//判断黑棋移动的位置是否还在本方的区域内
	if (Ncp.lx >= IniLx && Ncp.ly >= 8 + CHESS_LENGTH * 5 && Ncp.rx <= IniRx + CHESS_LENGTH * 8)
	{
		
		//判断左上角可以下吗
		if (Ncp.lx == chess[recordChess]->lx - CHESS_LENGTH * 2 && Ncp.ly == chess[recordChess]->ly - CHESS_LENGTH * 2
			&& Ncp.rx == chess[recordChess]->rx - CHESS_LENGTH * 2 && Ncp.ry == chess[recordChess]->ry - CHESS_LENGTH * 2)
		{
			//判断会堵象眼吗
			if (!isChess(chess[recordChess]->lx - CHESS_LENGTH, chess[recordChess]->ly - CHESS_LENGTH, chess[recordChess]->rx - CHESS_LENGTH, chess[recordChess]->ry - CHESS_LENGTH))
			{
				return TRUE;
			}
		}

		//判断右上角可以下吗
		if (Ncp.lx == chess[recordChess]->lx + CHESS_LENGTH * 2 && Ncp.ly == chess[recordChess]->ly - CHESS_LENGTH * 2
			&& Ncp.rx == chess[recordChess]->rx + CHESS_LENGTH * 2 && Ncp.ry == chess[recordChess]->ry - CHESS_LENGTH * 2)
		{
			//判断会堵象眼吗
			if (!isChess(chess[recordChess]->lx + CHESS_LENGTH, chess[recordChess]->ly - CHESS_LENGTH, chess[recordChess]->rx + CHESS_LENGTH, chess[recordChess]->ry - CHESS_LENGTH))
			{
				return TRUE;
			}
		}

		//判断右下角可以下吗
		if (Ncp.lx == chess[recordChess]->lx + CHESS_LENGTH * 2 && Ncp.ly == chess[recordChess]->ly + CHESS_LENGTH * 2
			&& Ncp.rx == chess[recordChess]->rx + CHESS_LENGTH * 2 && Ncp.ry == chess[recordChess]->ry + CHESS_LENGTH * 2)
		{
			//判断会堵象眼吗
			if (!isChess(chess[recordChess]->lx + CHESS_LENGTH, chess[recordChess]->ly + CHESS_LENGTH, chess[recordChess]->rx + CHESS_LENGTH, chess[recordChess]->ry + CHESS_LENGTH))
			{
				return TRUE;
			}
		}

		//判断左下角可以下吗
		if (Ncp.lx == chess[recordChess]->lx - CHESS_LENGTH * 2 && Ncp.ly == chess[recordChess]->ly + CHESS_LENGTH * 2
			&& Ncp.rx == chess[recordChess]->rx - CHESS_LENGTH * 2 && Ncp.ry == chess[recordChess]->ry + CHESS_LENGTH * 2)
		{
			//判断会堵象眼吗
			if (!isChess(chess[recordChess]->lx - CHESS_LENGTH, chess[recordChess]->ly + CHESS_LENGTH, chess[recordChess]->rx - CHESS_LENGTH, chess[recordChess]->ry + CHESS_LENGTH))
			{
				return TRUE;
			}
		}

	}
	return FALSE;
}

BOOL HouseRuler()//马的移动规则
{
	//判断上方的两个位置可以走吗
	if ((Ncp.lx == chess[recordChess]->lx - CHESS_LENGTH && Ncp.ly == chess[recordChess]->ly - CHESS_LENGTH * 2
		&& Ncp.rx == chess[recordChess]->rx - CHESS_LENGTH && Ncp.ry == chess[recordChess]->ry - CHESS_LENGTH * 2)
		|| (Ncp.lx == chess[recordChess]->lx + CHESS_LENGTH && Ncp.ly == chess[recordChess]->ly - CHESS_LENGTH * 2
			&& Ncp.rx == chess[recordChess]->rx + CHESS_LENGTH && Ncp.ry == chess[recordChess]->ry - CHESS_LENGTH * 2))
	{
		//判断会蹩马脚吗
		if (!isChess(chess[recordChess]->lx, chess[recordChess]->ly - CHESS_LENGTH, chess[recordChess]->rx, chess[recordChess]->ry - CHESS_LENGTH))
		{
			return TRUE;
		}

	}

	//判断右边的两个位置可以走吗
	if ((Ncp.lx == chess[recordChess]->lx + CHESS_LENGTH * 2 && Ncp.ly == chess[recordChess]->ly - CHESS_LENGTH
		&& Ncp.rx == chess[recordChess]->rx + CHESS_LENGTH * 2 && Ncp.ry == chess[recordChess]->ry - CHESS_LENGTH)
		|| (Ncp.lx == chess[recordChess]->lx + CHESS_LENGTH * 2 && Ncp.ly == chess[recordChess]->ly + CHESS_LENGTH
			&& Ncp.rx == chess[recordChess]->rx + CHESS_LENGTH * 2 && Ncp.ry == chess[recordChess]->ry + CHESS_LENGTH))
	{
		//判断会蹩马脚吗
		if (!isChess(chess[recordChess]->lx + CHESS_LENGTH, chess[recordChess]->ly, chess[recordChess]->rx + CHESS_LENGTH, chess[recordChess]->ry))
		{
			return TRUE;
		}
	}

	//判断下面的两个位置可以走吗
	if ((Ncp.lx == chess[recordChess]->lx - CHESS_LENGTH && Ncp.ly == chess[recordChess]->ly + CHESS_LENGTH * 2
		&& Ncp.rx == chess[recordChess]->rx - CHESS_LENGTH && Ncp.ry == chess[recordChess]->ry + CHESS_LENGTH * 2)
		|| (Ncp.lx == chess[recordChess]->lx + CHESS_LENGTH && Ncp.ly == chess[recordChess]->ly + CHESS_LENGTH * 2
			&& Ncp.rx == chess[recordChess]->rx + CHESS_LENGTH && Ncp.ry == chess[recordChess]->ry + CHESS_LENGTH * 2))
	{
		//判断会蹩马脚吗
		if (!isChess(chess[recordChess]->lx, chess[recordChess]->ly + CHESS_LENGTH, chess[recordChess]->rx, chess[recordChess]->ry + CHESS_LENGTH))
		{
			return TRUE;
		}
	}

	//判断左边的两个位置可以走吗
	if ((Ncp.lx == chess[recordChess]->lx - CHESS_LENGTH * 2 && Ncp.ly == chess[recordChess]->ly - CHESS_LENGTH
		&& Ncp.rx == chess[recordChess]->rx - CHESS_LENGTH * 2 && Ncp.ry == chess[recordChess]->ry - CHESS_LENGTH)
		|| (Ncp.lx == chess[recordChess]->lx - CHESS_LENGTH * 2 && Ncp.ly == chess[recordChess]->ly + CHESS_LENGTH
			&& Ncp.rx == chess[recordChess]->rx - CHESS_LENGTH * 2 && Ncp.ry == chess[recordChess]->ry + CHESS_LENGTH))
	{
		//判断会蹩马脚吗
		if (!isChess(chess[recordChess]->lx - CHESS_LENGTH, chess[recordChess]->ly, chess[recordChess]->rx - CHESS_LENGTH, chess[recordChess]->ry))
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CarRuler()//车的移动规则
{
	//判断在同一条直线上吗
	if (chess[recordChess]->lx == Ncp.lx || chess[recordChess]->ly == Ncp.ly)
	{
		//判断该道路上是否有障碍物
		if (isFreeLine() == 0)
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CannonRuler()//炮的移动规则
{
	//判断在同一条直线上吗
	if (chess[recordChess]->lx == Ncp.lx || chess[recordChess]->ly == Ncp.ly)
	{
		//判断该道路上是否有障碍物
		if (isFreeLine() == 0)
		{
			return TRUE;
		}
	}
	return FALSE;
}

int isFreeLine()//用于判断改直线上中间隔了几个棋子
{
	int count = 0;
	int i;
	if (Ncp.lx < chess[recordChess]->lx)//要移动的位置在棋左方
	{
		for (i = 0; i < 32; i++)
		{
			if (chess[i]->lx >= Ncp.lx
				&&chess[i]->ly == Ncp.ly
				&&chess[i]->rx < chess[recordChess]->rx
				&&chess[i]->ry == chess[recordChess]->ry
				&&chess[i]->color != -1)
			{
				count++;
			}
		}
		return count;
	}

	if (Ncp.lx > chess[recordChess]->lx)//要移动的位置在棋右方
	{
		for (i = 0; i < 32; i++)
		{
			if (chess[i]->lx > chess[recordChess]->lx
				&&chess[i]->ly == chess[recordChess]->ly
				&&chess[i]->rx <= Ncp.rx
				&&chess[i]->ry == Ncp.ry
				&&chess[i]->color != -1)
			{
				count++;
			}
		}
		return count;
	}

	if (Ncp.ly < chess[recordChess]->ly)//要移动的位置在棋上方
	{
		for (i = 0; i < 32; i++)
		{
			if (chess[i]->lx == Ncp.lx
				&&chess[i]->ly >= Ncp.ly
				&&chess[i]->rx == chess[recordChess]->rx
				&&chess[i]->ry < chess[recordChess]->ry
				&&chess[i]->color != -1)
			{
				count++;
			}
		}
		return count;
	}

	if (Ncp.ly > chess[recordChess]->ly)//要移动的位置在棋下方
	{
		for (i = 0; i < 32; i++)
		{
			if (chess[i]->lx == chess[recordChess]->lx
				&&chess[i]->ly > chess[recordChess]->ly
				&&chess[i]->rx == Ncp.rx
				&&chess[i]->ry <= Ncp.ry
				&&chess[i]->color != -1)
			{
				count++;
			}
		}
		return count;
	}

	return 100;
}

BOOL RedSoldiersRuler()//红兵的移动规则
{
	//没过河
	if (chess[recordChess]->lx >= IniLx
		&& chess[recordChess]->ly <= IniLy + CHESS_LENGTH * 4
		&& chess[recordChess]->rx <= IniRx + CHESS_LENGTH * 8)
	{
		//只能直走
		if (Ncp.lx == chess[recordChess]->lx&&Ncp.ly == chess[recordChess]->ly + CHESS_LENGTH
			&& Ncp.rx == chess[recordChess]->rx&&Ncp.ry == chess[recordChess]->ry + CHESS_LENGTH)
		{
			return TRUE;
		}
	}
	
	//过河了
	if (chess[recordChess]->lx >= IniLx
		&& chess[recordChess]->ly >= IniLy + CHESS_LENGTH * 5
		&& chess[recordChess]->rx <= IniRx + CHESS_LENGTH * 8)
	{
		//可以左、右、下走
		if ((Ncp.lx == chess[recordChess]->lx && Ncp.ly == chess[recordChess]->ly + CHESS_LENGTH)
			|| (Ncp.lx == chess[recordChess]->lx - CHESS_LENGTH && Ncp.ly == chess[recordChess]->ly)
			|| (Ncp.lx == chess[recordChess]->lx + CHESS_LENGTH && Ncp.ly == chess[recordChess]->ly)) {
			return TRUE;
		}
	}

	return FALSE;
}

BOOL BlackSoldiersRuler()//黑兵的移动规则
{
	//没过河
	if (chess[recordChess]->lx >= IniLx
		&& chess[recordChess]->ly >= IniLy + CHESS_LENGTH * 5
		&& chess[recordChess]->rx <= IniRx + CHESS_LENGTH * 8)
	{
		//只能向前走
		if (Ncp.lx == chess[recordChess]->lx&&Ncp.ly == chess[recordChess]->ly - CHESS_LENGTH) {
			return TRUE;
		}
	}

	//过河了
	if (chess[recordChess]->lx >= IniLx
		&& chess[recordChess]->ly <= IniLy + CHESS_LENGTH * 4
		&& chess[recordChess]->rx <= IniRx + CHESS_LENGTH * 8)
	{
		//只能向左、右、上走
		if ((Ncp.lx == chess[recordChess]->lx && Ncp.ly == chess[recordChess]->ly - CHESS_LENGTH) ||
			(Ncp.lx == chess[recordChess]->lx - CHESS_LENGTH && Ncp.ly == chess[recordChess]->ly) ||
			(Ncp.lx == chess[recordChess]->lx + CHESS_LENGTH && Ncp.ly == chess[recordChess]->ly)) {
			return TRUE;
		}
	}

	return FALSE;
}

BOOL RedKingWillDie()//红帅被将军
{
	int flag = 0;//跳出for循环的变量
	int i;

	/*判断黑兵能杀死红帅*/
	for (i = 16; i < 21; ++i)
	{
		if (chess[i]->color != -1 && (chess[i]->lx == chess[15]->lx&&chess[i]->ly - CHESS_LENGTH == chess[15]->ly)
			|| (chess[i]->lx - CHESS_LENGTH == chess[15]->lx&&chess[i]->ly == chess[15]->ly)
			|| (chess[i]->lx + CHESS_LENGTH == chess[15]->lx&&chess[i]->ly == chess[15]->ly))
		{
			flag = 1;
		}
	}
	if (flag == 1)
	{
		return TRUE;
	}

	/*黑炮可以杀死红帅*/
	if ((chess[21]->lx == chess[15]->lx
		|| chess[22]->lx == chess[15]->lx
		|| chess[21]->ly == chess[15]->ly
		|| chess[22]->ly == chess[15]->ly)
		&& ((chess[21]->color != -1 && isFreeLineWD(chess[21]->lx, chess[21]->ly, chess[21]->rx, chess[21]->ry
			, chess[15]->lx, chess[15]->ly, chess[15]->rx, chess[15]->ry) == 2)
			|| ((chess[22]->color != -1 && isFreeLineWD(chess[22]->lx, chess[22]->ly, chess[22]->rx, chess[22]->ry
				, chess[15]->lx, chess[15]->ly, chess[15]->rx, chess[15]->ry) == 2))))
	{
		return TRUE;
	}

	/*黑车可以杀死红帅*/
	if ((chess[23]->color != -1 && isFreeLineWD(chess[23]->lx, chess[23]->ly, chess[23]->rx, chess[23]->ry
		, chess[15]->lx, chess[15]->ly, chess[15]->rx, chess[15]->ry) == 1)
		|| (chess[21]->color != -1 && isFreeLineWD(chess[24]->lx, chess[24]->ly, chess[24]->rx, chess[24]->ry
			, chess[15]->lx, chess[15]->ly, chess[15]->rx, chess[15]->ry) == 1))
	{
		return TRUE;
	}

	/*黑马可以杀死红帅*/
	if ((chess[25]->color != -1 && HouseRulerWD(chess[25]->lx, chess[25]->ly,
		chess[25]->rx, chess[25]->ry, chess[15]->lx, chess[15]->ly, chess[15]->rx, chess[15]->ry))
		|| (chess[26]->color != -1 && HouseRulerWD(chess[26]->lx, chess[26]->ly,
			chess[26]->rx, chess[26]->ry, chess[15]->lx, chess[15]->ly, chess[15]->rx, chess[15]->ry)))
	{
		return TRUE;
	}
	return FALSE;
}

BOOL BlackKingWillDie()//黑将被将军
{
	int flag = 0;
	int i;

	/*判断黑兵能杀死红帅*/
	for (i = 0; i < 5; ++i)
	{
		if (chess[i]->color != -1 && (chess[i]->lx == chess[31]->lx&&chess[i]->ly + CHESS_LENGTH == chess[31]->ly)
			|| (chess[i]->lx - CHESS_LENGTH == chess[31]->lx&&chess[i]->ly == chess[31]->ly)
			|| (chess[i]->lx + CHESS_LENGTH == chess[31]->lx&&chess[i]->ly == chess[31]->ly))
		{
			flag = 1;
		}
	}
	if (flag == 1)
	{
		return TRUE;
	}

	/*黑炮可以杀死红帅*/
	if ((chess[5]->lx == chess[31]->lx
		|| chess[6]->lx == chess[31]->lx
		|| chess[5]->ly == chess[31]->ly
		|| chess[6]->ly == chess[31]->ly)
		&& ((chess[5]->color != -1 && isFreeLineWD(chess[5]->lx, chess[5]->ly, chess[5]->rx, chess[5]->ry
			, chess[31]->lx, chess[31]->ly, chess[31]->rx, chess[31]->ry) == 2)
			|| ((chess[6]->color != -1 && isFreeLineWD(chess[6]->lx, chess[6]->ly, chess[6]->rx, chess[6]->ry
				, chess[31]->lx, chess[31]->ly, chess[31]->rx, chess[31]->ry) == 2))))
	{
		return TRUE;
	}

	/*黑车可以杀死红帅*/
	if ((chess[7]->color != -1 && isFreeLineWD(chess[7]->lx, chess[7]->ly, chess[7]->rx, chess[7]->ry
		, chess[31]->lx, chess[31]->ly, chess[31]->rx, chess[31]->ry) == 1)
		|| (chess[8]->color != -1 && isFreeLineWD(chess[8]->lx, chess[8]->ly, chess[8]->rx, chess[8]->ry
			, chess[31]->lx, chess[31]->ly, chess[31]->rx, chess[31]->ry) == 1))
	{
		return TRUE;
	}

	/*黑马可以杀死红帅*/
	if ((chess[9]->color != -1 && HouseRulerWD(chess[9]->lx, chess[9]->ly,
		chess[9]->rx, chess[9]->ry, chess[31]->lx, chess[31]->ly, chess[31]->rx, chess[31]->ry))
		|| (chess[10]->color != -1 && HouseRulerWD(chess[10]->lx, chess[10]->ly,
			chess[10]->rx, chess[10]->ry, chess[31]->lx, chess[31]->ly, chess[31]->rx, chess[31]->ry)))
	{
		return TRUE;
	}
	return FALSE;
}

int isFreeLineWD(LONG x1, LONG y1, LONG x2, LONG y2
	, LONG lx, LONG ly, LONG rx, LONG ry)//用于判断改直线上中间隔了几个棋子
{//x1,y1,x2,y2代表炮的位置,lx,ly,rx,ry代表王的位置
	int count = 0;
	int i;

	if (lx < x1)//在棋左方
	{
		for (i = 0; i < 32; i++)
		{
			if (chess[i]->lx >= lx
				&&chess[i]->ly == ly
				&&chess[i]->rx < x2
				&&chess[i]->ry == y2
				&&chess[i]->color != -1)
			{
				count++;
			}
		}
		return count;
	}

	if (lx > x1)//在棋右方
	{
		for (i = 0; i < 32; i++)
		{
			if (chess[i]->lx > x1
				&&chess[i]->ly == y1
				&&chess[i]->rx <= rx
				&&chess[i]->ry == ry
				&&chess[i]->color != -1)
			{
				count++;
			}
		}
		return count;
	}

	if (ly < y1)//在棋上方
	{
		for (i = 0; i < 32; i++)
		{
			if (chess[i]->lx == lx
				&&chess[i]->ly >= ly
				&&chess[i]->rx == x2
				&&chess[i]->ry < y2
				&&chess[i]->color != -1)
			{
				count++;
			}
		}
		return count;
	}

	if (ly > y1)//在棋下方
	{
		for (i = 0; i < 32; i++)
		{
			if (chess[i]->lx == x1
				&&chess[i]->ly > y1
				&&chess[i]->rx == rx
				&&chess[i]->ry <= ry
				&&chess[i]->color != -1)
			{
				count++;
			}
		}
		return count;
	}

	return 100;
}

BOOL HouseRulerWD(LONG x1, LONG y1, LONG x2, LONG y2
	, LONG lx, LONG ly, LONG rx, LONG ry)
{
	//x1,y1,x2,y2代表马的位置,lx,ly,rx,ry代表王的位置
	//判断上方的两个位置可以走吗
	if ((lx == x1 - CHESS_LENGTH && ly == y1 - CHESS_LENGTH * 2
		&& rx == x2 - CHESS_LENGTH && ry == y2 - CHESS_LENGTH * 2)
		|| (lx == x1 + CHESS_LENGTH && ly == y1 - CHESS_LENGTH * 2
			&& rx == x2 + CHESS_LENGTH && ry == y2 - CHESS_LENGTH * 2))
	{
		if (!isChess(x1, y1 - CHESS_LENGTH, x2, y2 - CHESS_LENGTH))
		{
			return TRUE;
		}
	}

	//判断右边的两个位置可以走吗
	if ((lx == x1 + CHESS_LENGTH * 2 && ly == y1 - CHESS_LENGTH
		&& rx == x2 + CHESS_LENGTH * 2 && ry == y2 - CHESS_LENGTH)
		|| (lx == x1 + CHESS_LENGTH * 2 && ly == y1 + CHESS_LENGTH
			&& rx == x2 + CHESS_LENGTH * 2 && ry == y2 + CHESS_LENGTH))
	{
		if (!isChess(x1 + CHESS_LENGTH, y1, x2 + CHESS_LENGTH, y2))
		{
			return TRUE;
		}
	}

	//判断下面的两个位置可以走吗
	if ((lx == x1 - CHESS_LENGTH && ly == y1 + CHESS_LENGTH * 2
		&& rx == x2 - CHESS_LENGTH && ry == y2 + CHESS_LENGTH * 2)
		|| (lx == x1 + CHESS_LENGTH && ly == y1 + CHESS_LENGTH * 2
			&& rx == x2 + CHESS_LENGTH && ry == y2 + CHESS_LENGTH * 2))
	{
		if (!isChess(x1, y1 + CHESS_LENGTH, x2, y2 + CHESS_LENGTH))
		{
			return TRUE;
		}
	}

	//判断左边的两个位置可以走吗
	if ((lx == x1 - CHESS_LENGTH * 2 && ly == y1 - CHESS_LENGTH
		&& rx == x2 - CHESS_LENGTH * 2 && ry == y2 - CHESS_LENGTH)
		|| (lx == x1 - CHESS_LENGTH * 2 && ly == y1 + CHESS_LENGTH
			&& rx == x2 - CHESS_LENGTH * 2 && ry == y2 + CHESS_LENGTH))
	{
		if (!isChess(x1 - CHESS_LENGTH, y1, x2 - CHESS_LENGTH, y2))
		{
			return TRUE;
		}
	}

	return FALSE;
}