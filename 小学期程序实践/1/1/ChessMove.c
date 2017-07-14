#include "ChineseChess.h"

/*���������ƶ����������ز���*/
void CreateChess() //��32�����ӳ�ʼ��
{
	int i;
	/*�����ʼ��*/
	for (i = 0; i < 5; ++i)
	{
		chess[i]->lx = IniLx + 2 * i * CHESS_LENGTH;
		chess[i]->ly = IniLy + CHESS_LENGTH * 3;
		chess[i]->rx = IniRx + 2 * i * CHESS_LENGTH;
		chess[i]->ry = IniRy + CHESS_LENGTH * 3;
		chess[i]->color = 1;
		chess[i]->level = 0;
	}
	/*���ڳ�ʼ��*/
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
	/*�쳵��ʼ��*/
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
	/*�����ʼ��*/
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
	/*�����ʼ��*/
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
	/*��ʿ��ʼ��*/
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
	/*��˧��ʼ��*/
	chess[15]->lx = IniLx + CHESS_LENGTH * 4;
	chess[15]->ly = IniLy;
	chess[15]->rx = IniRx + CHESS_LENGTH * 4;
	chess[15]->ry = IniRy;
	chess[15]->color = 1;
	chess[15]->level = 6;
	/*�췽��ʼ��������ڿ�ʼ�ڷ���ʼ��*/

	/*�ڱ���ʼ��*/
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
	/*���ڳ�ʼ��*/
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
	/*��ʼ����*/
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
	/*��ʼ����*/
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
	/*��ʼ����*/
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
	/*��ʼ��ʿ*/
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
	/*���ĳ�ʼ��*/
	chess[31]->lx = IniLx + CHESS_LENGTH * 4;
	chess[31]->ly = IniLy + CHESS_LENGTH * 9;
	chess[31]->rx = IniRx + CHESS_LENGTH * 4;
	chess[31]->ry = IniRy + CHESS_LENGTH * 9;
	chess[31]->color = 0;
	chess[31]->level = 6;
	/*�Լ�¼ѡ�����ӵı�����ʼ��*/
	recordChess = -1;
}

void NextChess(LONG x, LONG y)//�������ƶ������жϵĺ���
{
	if (GetMoveChessPlace(x, y)) {
		//0����Ҫ�ƶ�ȥ��λ��Ϊ����,1Ϊ�ео�����,2Ϊ���Ѿ�����
		switch (isChess(Ncp.lx, Ncp.ly, Ncp.rx, Ncp.ry))
		{
		case 0:
			if (ChessRuler(x, y) == TRUE)
			{
				SaveChess();//�ƶ�ǰ�Ƚ�����λ�ñ�������
				MoveChess();
			}
			break;
		case 1:
			if (ChessRuler(x, y) == TRUE)
			{
				SaveChess();//�ƶ�ǰ�Ƚ�����λ�ñ�������
				EatChess(Ncp.lx, Ncp.ly, Ncp.rx, Ncp.ry);
				MoveChess();
			}
			//�������ںͳ������ж�
			if (isFreeLine() == 2 && chess[recordChess]->level == 1)
			{
				SaveChess();//�ƶ�ǰ�Ƚ�����λ�ñ�������
				EatChess(Ncp.lx, Ncp.ly, Ncp.rx, Ncp.ry);
				MoveChess();
			}
			if (isFreeLine() == 1 && chess[recordChess]->level == 2)
			{
				SaveChess();//�ƶ�ǰ�Ƚ�����λ�ñ�������
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

BOOL ChessRuler(LONG x, LONG y)//�������������߷��Ƿ���Ϲ�������ж�
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

int isChess(LONG lx, LONG ly, LONG rx, LONG ry)//�ж��µ�λ����û������
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
				return 3;//����Ϊ�Ѿ�
			}
			else
			{
				return 1;//����Ϊ�о�
			}
		}
	}
	return 0;//û��
}

void EatChess(LONG lx, LONG ly, LONG rx, LONG ry)//����,������������ɫ��Ϊ-1
{
	for (int i = 0; i < 32; ++i)
	{
		if (chess[i]->lx == lx
			&&chess[i]->ly == ly
			&&chess[i]->rx == rx
			&&chess[i]->ry == ry
			&&chess[i]->color != -1)
		{
			//�������Ifѭ��ʱΪ���岽������
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

void MoveChess()//�ƶ����ӵĺ���
{

	chess[recordChess]->lx = Ncp.lx;
	chess[recordChess]->ly = Ncp.ly;
	chess[recordChess]->rx = Ncp.rx;
	chess[recordChess]->ry = Ncp.ry;

	recordChess = -1;
	//�����ӵ�����
	CreateThread(NULL, 0, DownCHESS, NULL, 0, NULL);
}

BOOL GetMoveChessPlace(LONG x, LONG y)//�õ����µ�λ�õ����������ĸ�С��
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
		MessageBox(NULL, "����������������", "Warning", MB_OK | MB_ICONERROR);
	}

	return FALSE;
}

void GetChessInformation(LONG x, LONG y)//�õ�ѡ�е����ӵı��
{
	int flag = 0;

	for (int i = 0; i < 32 && flag == 0; ++i)
	{
		if (chess[i]->color != -1 && chess[i]->lx<x&&chess[i]->ly<y&&chess[i]->rx>x&&chess[i]->ry>y)
		{
			flag = 1;
			recordChess = i;
			//ѡ�����ӵ�����
			CreateThread(NULL, 0, ChooseCHESS, NULL, 0, NULL);
		}
	}
}

void Regretchess()
{
	if (order >= 2)//ֻ�е��������������ϵĲ���ʱ����ִ�л������
	{
		//�ָ�����
		chess[temprecord0.number]->lx = temprecord0.lx;
		chess[temprecord0.number]->ly = temprecord0.ly;
		chess[temprecord0.number]->rx = temprecord0.rx;
		chess[temprecord0.number]->ry = temprecord0.ry;
		chess[temprecord0.number]->color = temprecord0.color;

		if (temprecord0.eat != -1)//������ǰ�������з����˳������
		{
			chess[temprecord0.eat]->color = temprecord0.eatcolor;
		}

		//�ָ�����
		chess[temprecord1.number]->lx = temprecord1.lx;
		chess[temprecord1.number]->ly = temprecord1.ly;
		chess[temprecord1.number]->rx = temprecord1.rx;
		chess[temprecord1.number]->ry = temprecord1.ry;
		chess[temprecord1.number]->color = temprecord1.color;

		if (temprecord1.eat != -1)//������ǰ���������˳������
		{
			chess[temprecord1.eat]->color = temprecord1.eatcolor;
		}
		/*����ʱ������*/
		CreateThread(NULL, 0, ChooseCHESS, NULL, 0, NULL);
	}
}

void SaveChess()//�������Ĳ������м�¼,������л������
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

BOOL GameOver()//�ж���Ϸ�Ƿ����
{
	if (chess[15]->color == -1 || chess[31]->color == -1)
	{
		MessageBox(NULL, "��Ϸ����", "�й�����", MB_OKCANCEL);
		return TRUE;
	}

	return FALSE;
}
