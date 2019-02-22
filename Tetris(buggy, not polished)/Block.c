#include "block.h"

int DIFF = 2;

struct block linerotater(struct block block, int **board, int key) //□□□□ 
{
	struct block line = block;

	if (key == 80 || key == 77 || key == 75)
	{
		if (key == 80) //DOWN
		{
			line.a.y++;
			line.b.y++;
			line.c.y++;
			line.d.y++;
		}
		if (key == 75) //LEFT
		{
			line.a.x -= DIFF;
			line.b.x -= DIFF;
			line.c.x -= DIFF;
			line.d.x -= DIFF;
		}
		if (key == 77)//RIGHT
		{
			line.a.x += DIFF;
			line.b.x += DIFF;
			line.c.x += DIFF;
			line.d.x += DIFF;
		}
	}

	else if (key == 113 || key == 114 || key == 81 || key == 82)
	{
		switch (line.status)
		{
		case 1:
			if (key == 113 || key == 81) //q
			{
				line.d.x = line.c.x = line.a.x = line.b.x;
				line.a.y -= 2;
				line.b.y--;
				line.d.y++;
				line.status = -2;
			}
			if (key == 114 || key == 82) //r
			{
				line.d.x = line.b.x = line.a.x = line.c.x;
				line.d.y++;
				line.b.y--;
				line.a.y -= 2;
				line.status = 2;
			}
			break;
		case 2:
			if (key == 113 || key == 81)
			{
				line.a.x -= 4;
				line.b.x -= 2;
				line.b.y--;
				line.c.y -= 2;
				line.d.x += 2;
				line.d.y -= 3;
				line.status = 1;
			}
			if (key == 114 || key == 82)
			{
				line.a.x -= 4;
				line.b.x -= 2;
				line.b.y--;
				line.c.y -= 2;
				line.d.x += 2;
				line.d.y -= 3;
				line.status = 1;
			}
			if (key == 80) //DOWN
			{
				line.a.y++;
				line.b.y++;
				line.c.y++;
				line.d.y++;
			}
			if (key == 75) //LEFT
			{
				line.a.x -= DIFF;
				line.b.x -= DIFF;
				line.c.x -= DIFF;
				line.d.x -= DIFF;
			}
			if (key == 77)//RIGHT
			{
				line.a.x += DIFF;
				line.b.x += DIFF;
				line.c.x += DIFF;
				line.d.x += DIFF;
			}
			break;
		case -2:
			if (key == 113 || key == 81)
			{
				line.a.x -= 2;
				line.b.y--;
				line.c.x += 2;
				line.c.y -= 2;
				line.d.x += 4;
				line.d.y -= 3;
				line.status = 1;
			}
			if (key == 114 || key == 82)
			{
				line.a.x -= 2;
				line.b.y--;
				line.c.x += 2;
				line.c.y -= 2;
				line.d.x += 4;
				line.d.y -= 3;
				line.status = 1;
			}
			if (key == 80) //DOWN
			{
				line.a.y++;
				line.b.y++;
				line.c.y++;
				line.d.y++;
			}
			if (key == 75) //LEFT
			{
				line.a.x -= DIFF;
				line.b.x -= DIFF;
				line.c.x -= DIFF;
				line.d.x -= DIFF;
			}
			if (key == 77)//RIGHT
			{
				line.a.x += DIFF;
				line.b.x += DIFF;
				line.c.x += DIFF;
				line.d.x += DIFF;
			}
			break;
		}
	}

	if (line.a.x > 0 && line.a.x < 21 && line.a.y > 0 && line.a.y < 23 && line.b.x > 0 && line.b.x < 21 && line.b.y > 0 && line.b.y < 23)
	{
		if (line.c.x > 0 && line.c.x < 21 && line.c.y > 0 && line.c.y < 23 && line.d.x > 0 && line.d.x < 21 && line.d.y > 0 && line.d.y < 23)
		{
			if (board[line.a.x][line.a.y] != 1 && board[line.b.x][line.b.y] != 1 && board[line.c.x][line.c.y] != 1 && board[line.d.x][line.d.y] != 1)
			{
				block = line;
			}
		}
	}

	return block;
}

struct block Orotater(struct block block, int **board, int key)
{
	struct block O = block;

	if (key == 80 || key == 77 || key == 75)
	{
		if (key == 80) //DOWN
		{
			O.a.y++;
			O.b.y++;
			O.c.y++;
			O.d.y++;
		}
		if (key == 75) //LEFT
		{
			O.a.x -= DIFF;
			O.b.x -= DIFF;
			O.c.x -= DIFF;
			O.d.x -= DIFF;
		}
		if (key == 77)//RIGHT
		{
			O.a.x += DIFF;
			O.b.x += DIFF;
			O.c.x += DIFF;
			O.d.x += DIFF;
		}
	}

	if (O.a.x > 0 && O.a.x < 21 && O.a.y > 0 && O.a.y < 23 && O.b.x > 0 && O.b.x < 21 && O.b.y > 0 && O.b.y < 23)
	{
		if (O.c.x > 0 && O.c.x < 21 && O.c.y > 0 && O.c.y < 23 && O.d.x > 0 && O.d.x < 21 && O.d.y > 0 && O.d.y < 23)
		{
			if (board[O.a.x][O.a.y] != 1 && board[O.b.x][O.b.y] != 1 && board[O.c.x][O.c.y] != 1 && board[O.d.x][O.d.y] != 1)
			{
				block = O;
			}
		}
	}

	if (block.a.y == 22 || block.b.y == 22 || block.c.y == 22 || block.d.y == 22)
		block.isdropped = 1;
	if (board[block.c.x][block.c.y + 1] == 1 || board[block.d.x][block.d.y + 1] == 1)
		block.isdropped = 1;

	return block;
}

struct block Trotater(struct block block, int **board, int key)
{
	struct block T = block;

	if (key == 80 || key == 77 || key == 75)
	{
		if (key == 80) //DOWN
		{
			T.a.y++;
			T.b.y++;
			T.c.y++;
			T.d.y++;
		}
		if (key == 75) //LEFT
		{
			T.a.x -= DIFF;
			T.b.x -= DIFF;
			T.c.x -= DIFF;
			T.d.x -= DIFF;
		}
		if (key == 77)//RIGHT
		{
			T.a.x += DIFF;
			T.b.x += DIFF;
			T.c.x += DIFF;
			T.d.x += DIFF;
		}
	}
	else if (key == 113 || key == 114 || key == 81 || key == 82)
	{
		switch (T.status)
		{
		case 1:
			if (key == 113 || key == 81)
			{
				T.a.y++;
				T.a.x += 2;
				T.c.x -= 2;
				T.c.y--;
				T.d.x -= 2;
				T.d.y++;
				T.status = -2;
			}
			if (key == 114 || key == 82)
			{
				T.a.x += 2;
				T.a.y--;
				T.c.x -= 2;
				T.c.y++;
				T.d.x += 2;
				T.d.y++;
				T.status = 2;
			}
			break;
		case 2:
			if (key == 113 || key == 81)
			{
				T.a.x -= 2;
				T.a.y++;
				T.c.x += 2;
				T.c.y--;
				T.d.x -= 2;
				T.d.y--;
				T.status = 1;
			}
			if (key == 114 || key == 82)
			{
				T.a.x += 2;
				T.a.y++;
				T.c.x -= 2;
				T.c.y--;
				T.d.x -= 2;
				T.d.y++;
				T.status = 3;
			}
			break;
		case -2:
			if (key == 113 || key == 81)
			{
				T.a.x += 2;
				T.a.y--;
				T.c.x -= 2;
				T.c.y++;
				T.d.x += 2;
				T.d.y++;
				T.status = 3;
			}
			if (key == 114 || key == 82)
			{
				T.a.x -= 2;
				T.a.y--;
				T.c.x += 2;
				T.c.y++;
				T.d.x += 2;
				T.d.y--;
				T.status = 1;
			}
			break;

		case 3:
			if (key == 113 || key == 81)
			{
				T.a.x -= 2;
				T.a.y--;
				T.c.x += 2;
				T.c.y++;
				T.d.x += 2;
				T.d.y--;
				T.status = 2;
			}
			if (key == 114 || key == 82)
			{
				T.a.x -= 2;
				T.a.y++;
				T.c.x += 2;
				T.c.y--;
				T.d.x -= 2;
				T.d.y--;
				T.status = -2;
			}
			break;
		}
	}

	if (T.a.x > 0 && T.a.x < 21 && T.a.y > 0 && T.a.y < 23 && T.b.x > 0 && T.b.x < 21 && T.b.y > 0 && T.b.y < 23)
	{
		if (T.c.x > 0 && T.c.x < 21 && T.c.y > 0 && T.c.y < 23 && T.d.x > 0 && T.d.x < 21 && T.d.y > 0 && T.d.y < 23)
		{
			if (board[T.a.x][T.a.y] != 1 && board[T.b.x][T.b.y] != 1 && board[T.c.x][T.c.y] != 1 && board[T.d.x][T.d.y] != 1)
			{
				block = T;
			}
		}
	}

	return block;
}

struct block Srotater(struct block block, int **board, int key)
{

	struct block S = block;

	if (key == 80 || key == 77 || key == 75)
	{
		if (key == 80) //DOWN
		{
			S.a.y++;
			S.b.y++;
			S.c.y++;
			S.d.y++;
		}
		if (key == 75) //LEFT
		{
			S.a.x -= DIFF;
			S.b.x -= DIFF;
			S.c.x -= DIFF;
			S.d.x -= DIFF;
		}
		if (key == 77)//RIGHT
		{
			S.a.x += DIFF;
			S.b.x += DIFF;
			S.c.x += DIFF;
			S.d.x += DIFF;
		}
	}

	else if (key == 113 || key == 114 || key == 81 || key == 82)
	{
		switch (S.status)
		{
		case 1:
			if (key == 113 || key == 81)
			{
				S.a.x += 2;
				S.b.y--;
				S.c.x -= 2;
				S.d.x -= 4;
				S.d.y--;
				S.status = -2;
			}
			if (key == 114 || key == 82)
			{
				S.a.x += 2;
				S.a.y -= 2;
				S.b.y--;
				S.c.x += 2;
				S.d.y++;
				S.status = 2;
			}
			break;
		case 2:
			if (key == 113 || key == 114 || key == 81 || key == 82)
			{
				S.a.x -= 2;
				S.a.y += 2;
				S.b.y++;
				S.c.x -= 2;
				S.d.y--;
				S.status = 1;
			}
			break;
		case -2:
			if (key == 113 || key == 114 || key == 81 || key == 82)
			{
				S.a.x -= 2;
				S.b.y++;
				S.c.x += 2;
				S.d.x += 4;
				S.d.y++;
				S.status = 1;
			}
			break;
		}
	}

	if (S.a.x > 0 && S.a.x < 21 && S.a.y > 0 && S.a.y < 23 && S.b.x > 0 && S.b.x < 21 && S.b.y > 0 && S.b.y < 23)
	{
		if (S.c.x > 0 && S.c.x < 21 && S.c.y > 0 && S.c.y < 23 && S.d.x > 0 && S.d.x < 21 && S.d.y > 0 && S.d.y < 23)
		{
			if (board[S.a.x][S.a.y] != 1 && board[S.b.x][S.b.y] != 1 && board[S.c.x][S.c.y] != 1 && board[S.d.x][S.d.y] != 1)
			{
				block = S;
			}
		}
	}

	return block;
}

struct block Zrotater(struct block block, int **board, int key)
{
	struct block Z = block;

	if (key == 80 || key == 77 || key == 75)
	{
		if (key == 80) //DOWN
		{
			Z.a.y++;
			Z.b.y++;
			Z.c.y++;
			Z.d.y++;
		}
		if (key == 75) //LEFT
		{
			Z.a.x -= DIFF;
			Z.b.x -= DIFF;
			Z.c.x -= DIFF;
			Z.d.x -= DIFF;
		}
		if (key == 77)//RIGHT
		{
			Z.a.x += DIFF;
			Z.b.x += DIFF;
			Z.c.x += DIFF;
			Z.d.x += DIFF;
		}
	}

	else if (key == 113 || key == 114 || key == 81 || key == 82)
	{
		switch (Z.status)
		{
		case 1:
			if (key == 113 || key == 81)
			{
				Z.a.y++;
				Z.b.x -= 2;
				Z.c.y--;
				Z.d.x -= 2;
				Z.d.y -= 2;
				Z.status = -2;
			}
			if (key == 114)
			{
				Z.a.x += 4;
				Z.a.y--;
				Z.b.x += 2;
				Z.c.y--;
				Z.d.x -= 2;
				Z.status = 2;
			}
			break;
		case 2:
			if (key == 113 || key == 114 || key == 81 || key == 82)
			{
				Z.a.x -= 4;
				Z.a.y++;
				Z.b.x -= 2;
				Z.c.y++;
				Z.d.x += 2;
				Z.status = 1;
			}
			break;
		case -2:
			if (key == 114 || key == 113 || key == 81 || key == 82)
			{
				Z.a.y--;
				Z.b.x += 2;
				Z.c.y++;
				Z.d.x += 2;
				Z.d.y += 2;
				Z.status = 1;
			}
			break;
		}
	}

	if (Z.a.x > 0 && Z.a.x < 21 && Z.a.y > 0 && Z.a.y < 23 && Z.b.x > 0 && Z.b.x < 21 && Z.b.y > 0 && Z.b.y < 23)
	{
		if (Z.c.x > 0 && Z.c.x < 21 && Z.c.y > 0 && Z.c.y < 23 && Z.d.x > 0 && Z.d.x < 21 && Z.d.y > 0 && Z.d.y < 23)
		{
			if (board[Z.a.x][Z.a.y] != 1 && board[Z.b.x][Z.b.y] != 1 && board[Z.c.x][Z.c.y] != 1 && board[Z.d.x][Z.d.y] != 1)
			{
				block = Z;
			}
		}
	}

	return block;
}

struct block Lrotater(struct block block, int **board, int key)
{
	struct block L = block;

	if (key == 80 || key == 77 || key == 75)
	{
		if (key == 80) //DOWN
		{
			L.a.y++;
			L.b.y++;
			L.c.y++;
			L.d.y++;
		}
		if (key == 75) //LEFT
		{
			L.a.x -= DIFF;
			L.b.x -= DIFF;
			L.c.x -= DIFF;
			L.d.x -= DIFF;
		}
		if (key == 77)//RIGHT
		{
			L.a.x += DIFF;
			L.b.x += DIFF;
			L.c.x += DIFF;
			L.d.x += DIFF;
		}
	}

	else if (key == 113 || key == 114 || key == 81 || key == 82)
	{
		switch (L.status)
		{
		case 1:
			if (key == 113 || key == 81) //q
			{
				L.a.x += 2;
				L.b.y--;
				L.c.x -= 2;
				L.c.y -= 2;
				L.d.y++;
				L.status = -2;
			}
			if (key == 114 || key == 82) //r
			{
				L.a.x += 2;
				L.a.y -= 2;
				L.b.y--;
				L.c.x -= 2;
				L.d.x += 4;
				L.d.y--;
				L.status = 2;
			}
			break;
		case 2:
			if (key == 113 || key == 81)
			{
				L.a.x -= 2;
				L.a.y += 2;
				L.b.y++;
				L.c.x += 2;
				L.d.x -= 4;
				L.d.y++;
				L.status = 1;
			}
			if (key == 114 || key == 82)
			{
				L.a.x += 2;
				L.a.y++;
				L.c.x -= 2;
				L.c.y--;
				L.d.y += 2;
				L.status = 3;
			}
			break;
		case -2:
			if (key == 113 || key == 81)
			{
				L.a.x += 2;
				L.a.y--;
				L.c.x -= 2;
				L.c.y++;
				L.d.x += 4;
				L.status = 3;
			}
			if (key == 114 || key == 82)
			{
				L.a.x -= 2;
				L.b.y++;
				L.c.x += 2;
				L.c.y += 2;
				L.d.y--;
				L.status = 1;
			}
			break;
		case 3:
			if (key == 113 || key == 81) //q
			{
				L.a.x -= 2;
				L.a.y--;
				L.c.x += 2;
				L.c.y++;
				L.d.y -= 2;
				L.status = 2;
			}
			if (key == 114 || key == 82) //r
			{
				L.a.x -= 2;
				L.a.y++;
				L.c.x += 2;
				L.c.y--;
				L.d.x -= 4;
				L.status = -2;
			}
			break;

		}
	}

	if (L.a.x > 0 && L.a.x < 21 && L.a.y > 0 && L.a.y < 23 && L.b.x > 0 && L.b.x < 21 && L.b.y > 0 && L.b.y < 23)
	{
		if (L.c.x > 0 && L.c.x < 21 && L.c.y > 0 && L.c.y < 23 && L.d.x > 0 && L.d.x < 21 && L.d.y > 0 && L.d.y < 23)
		{
			if (board[L.a.x][L.a.y] != 1 && board[L.b.x][L.b.y] != 1 && board[L.c.x][L.c.y] != 1 && board[L.d.x][L.d.y] != 1)
			{
				block = L;
			}
		}
	}

	return block;
}

struct block Jrotater(struct block block, int **board, int key)
{
	struct block J = block;

	if (key == 80 || key == 77 || key == 75)
	{
		if (key == 80) //DOWN
		{
			J.a.y++;
			J.b.y++;
			J.c.y++;
			J.d.y++;
		}
		if (key == 75) //LEFT
		{
			J.a.x -= DIFF;
			J.b.x -= DIFF;
			J.c.x -= DIFF;
			J.d.x -= DIFF;
		}
		if (key == 77)//RIGHT
		{
			J.a.x += DIFF;
			J.b.x += DIFF;
			J.c.x += DIFF;
			J.d.x += DIFF;
		}
	}

	else if (key == 113 || key == 114 || key == 81 || key == 82)
	{
		switch (J.status)
		{
		case 1:
			if (key == 113 || key == 81)
			{
				J.a.x += 2;
				J.b.y--;
				J.c.x -= 2;
				J.c.y -= 2;
				J.d.x -= 4;
				J.d.y--;
				J.status = -2;
			}
			if (key == 114 || key == 82)
			{
				J.a.x += 2;
				J.a.y -= 2;
				J.b.y--;
				J.c.x -= 2;
				J.d.y++;
				J.status = 2;
			}
			break;
		case 2:
			if (key == 113 || key == 81)
			{
				J.a.x -= 2;
				J.a.y += 2;
				J.b.y++;
				J.c.x += 2;
				J.d.y--;
				J.status = 1;
			}
			if (key == 114 || key == 82)
			{
				J.a.x += 2;
				J.a.y++;
				J.c.x -= 2;
				J.c.y--;
				J.d.x -= 4;
				J.status = 3;
			}
			break;
		case -2:
			if (key == 113 || key == 81)
			{
				J.a.x += 2;
				J.a.y--;
				J.c.x -= 2;
				J.c.y++;
				J.d.y += 2;
				J.status = 3;
			}
			if (key == 114 || key == 82)
			{
				J.a.x -= 2;
				J.b.y++;
				J.c.x += 2;
				J.c.y += 2;
				J.d.x += 4;
				J.d.y++;
				J.status = 1;
			}
			break;

		case 3:
			if (key == 113 || key == 81)
			{
				J.a.x -= 2;
				J.a.y--;
				J.c.x += 2;
				J.c.y++;
				J.d.x += 4;
				J.status = 2;
			}
			if (key == 114 || key == 82)
			{
				J.a.x -= 2;
				J.a.y++;
				J.c.x += 2;
				J.c.y--;
				J.d.y -= 2;
				J.status = -2;
			}
			break;
		}
	}

	if (J.a.x > 0 && J.a.x < 21 && J.a.y > 0 && J.a.y < 23 && J.b.x > 0 && J.b.x < 21 && J.b.y > 0 && J.b.y < 23)
	{
		if (J.c.x > 0 && J.c.x < 21 && J.c.y > 0 && J.c.y < 23 && J.d.x > 0 && J.d.x < 21 && J.d.y > 0 && J.d.y < 23)
		{
			if (board[J.a.x][J.a.y] != 1 && board[J.b.x][J.b.y] != 1 && board[J.c.x][J.c.y] != 1 && board[J.d.x][J.d.y] != 1)
			{
				block = J;
			}
		}
	}

	return block;
}
