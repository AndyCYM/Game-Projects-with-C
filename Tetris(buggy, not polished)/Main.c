#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <MMSystem.h>
#include <conio.h>
#include "block.h"

//note to self
//do not use the algorithm of redrawing the entire screen each frame
//only calculate elements from board[1][1] to board[1][21]
//leave the walls be after drawing them at the first frame
//when the start button is pressed right after the program has started, nothing gets printed --> FIXED

struct block nextblock; //next block on queue
time_t lengthotime;
int width = 22;
int height = 24;
int xsquare = 24; //x-coordinate of the square that will show what next block will be
int ysquare = 6; //y-coordinate of the square that will show what next block will be
int widsquare = 4; //width of the square .
int xoftext = 1; //x-coordinate of texts on manual
int yoftext = 1;//y-coordinate of texts on manual
int freqodelay = 10; //how long each delay will be while constantly checking if there is an input
int timeodelay = 1000;  //how long each frame will be
int textdelay = 500; //how long each blinking of the text will be
int level = 1; //each level has 20 blocks. When a level uses up all of its blocks, then the level increases
int speed = 1;
int score = 0;

//size of grid --> 10 blocks x 22
void startmenu(void);
void boarddisplay(int **board);
struct block spawner(struct block block);
void manual(void);
void pauser(void);
struct block ghostblockmaker(struct block block, struct block ghostblock, int **board);
int **linedeleter(int **board, struct block block); //function for deleting full lines from the screen

void gotoxy(int x, int y)
{
	COORD point;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	point.X = x;
	point.Y = y;
	SetConsoleCursorPosition(h, point);
}

void color(int color)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, color);
}

int main()
{
	srand(time(NULL));

	time_t currenttime;
	time_t elapsedtime;
	int numomusic = 1; 

	int **board = (int*)malloc(sizeof(int*) * width);
	for (int i = 0; i < width; i++)
	{
		board[i] = (int)malloc(sizeof(int) * height);
	}

	int key;
	int numblock = 20; //how many blocks current level has

	startmenu();

	struct block block;
	struct block ghostblock; //"ghost" block: shows how the current block will land when it goes straight down

	currenttime = clock();
	PlaySound(TEXT("Smug.wav"), NULL, SND_ASYNC);

	block.a.x = 7;
	block.a.y = 2;
	nextblock.isdropped = 0;
	nextblock.status = 1;

	block.whatblock = rand() % 7;

	do
	{
		nextblock.whatblock = rand() % 7;
	} while (nextblock.whatblock == block.whatblock);

	switch (block.whatblock)
	{
	case 0: //if the block is a line
		block.b.x = block.a.x + 2;
		block.c.x = block.b.x + 2;
		block.d.x = block.c.x + 2;
		block.d.y = block.c.y = block.b.y = block.a.y;
		break;
	case 1: // if the block is a O shape
		block.b.x = block.a.x + 2;
		block.b.y = block.a.y;
		block.c.x = block.a.x;
		block.c.y = block.a.y + 1;
		block.d.x = block.a.x + 2;
		block.d.y = block.a.y + 1;
		break;
	case 2: //if the block is L shape
		block.c.y = block.b.y = block.a.y;
		block.d.y = block.a.y - 1;
		block.b.x = block.a.x + 2;
		block.c.x = block.b.x + 2;
		block.d.x = block.a.x;
		break;
	case 3: //J shape
		block.c.y = block.b.y = block.a.y;
		block.d.y = block.a.y - 1;
		block.b.x = block.a.x + 2;
		block.c.x = block.b.x + 2;
		block.d.x = block.c.x;
		break;
	case 4: //S shape
		block.b.x = block.a.x + 2;
		block.b.y = block.a.y;
		block.c.x = block.b.x;
		block.c.y = block.b.y - 1;
		block.d.x = block.c.x + 2;
		block.d.y = block.c.y;
		break;
	case 5: //T shape
		block.c.y = block.b.y = block.a.y;
		block.b.x = block.a.x + 2;
		block.c.x = block.b.x + 2;
		block.d.x = block.b.x;
		block.d.y = block.b.y - 1;
		break;
	case 6: //Z shape
		block.b.y = block.a.y;
		block.b.x = block.a.x + 2;
		block.c.x = block.b.x;
		block.c.y = block.b.y + 1;
		block.d.x = block.c.x + 2;
		block.d.y = block.c.y;
		break;
	}

	switch (nextblock.whatblock)
	{
	case 0: //if next block is a line
		nextblock.a.x = 25;
		nextblock.a.y = 9;
		nextblock.b.x = nextblock.a.x + 2;
		nextblock.c.x = nextblock.b.x + 2;
		nextblock.d.x = nextblock.c.x + 2;
		nextblock.d.y = nextblock.c.y = nextblock.b.y = nextblock.a.y;
		break;
	case 1: //O shape
		nextblock.a.x = 27;
		nextblock.a.y = 8;
		nextblock.b.x = nextblock.a.x + 2;
		nextblock.b.y = nextblock.a.y;
		nextblock.c.x = nextblock.a.x;
		nextblock.c.y = nextblock.a.y + 1;
		nextblock.d.x = nextblock.a.x + 2;
		nextblock.d.y = nextblock.a.y + 1;
		break;
	case 2: //L shape
		nextblock.a.x = 27;
		nextblock.a.y = 9;
		nextblock.c.y = nextblock.b.y = nextblock.a.y;
		nextblock.d.y = nextblock.a.y - 1;
		nextblock.b.x = nextblock.a.x + 2;
		nextblock.c.x = nextblock.b.x + 2;
		nextblock.d.x = nextblock.a.x;
		break;
	case 3: //J shape
		nextblock.a.x = 27;
		nextblock.a.y = 9;
		nextblock.c.y = nextblock.b.y = nextblock.a.y;
		nextblock.d.y = nextblock.a.y - 1;
		nextblock.b.x = nextblock.a.x + 2;
		nextblock.c.x = nextblock.b.x + 2;
		nextblock.d.x = nextblock.c.x;
		break;
	case 4: //S shape
		nextblock.a.x = 27;
		nextblock.a.y = 9;
		nextblock.b.x = nextblock.a.x + 2;
		nextblock.b.y = nextblock.a.y;
		nextblock.c.x = nextblock.b.x;
		nextblock.c.y = nextblock.b.y - 1;
		nextblock.d.x = nextblock.c.x + 2;
		nextblock.d.y = nextblock.c.y;
		break;
	case 5: //T shape
		nextblock.a.x = 27;
		nextblock.a.y = 9;
		nextblock.c.y = nextblock.b.y = nextblock.a.y;
		nextblock.b.x = nextblock.a.x + 2;
		nextblock.c.x = nextblock.b.x + 2;
		nextblock.d.x = nextblock.b.x;
		nextblock.d.y = nextblock.b.y - 1;
		break;
	case 6: //Z shape
		nextblock.a.x = 27;
		nextblock.a.y = 8;
		nextblock.b.y = nextblock.a.y;
		nextblock.b.x = nextblock.a.x + 2;
		nextblock.c.x = nextblock.b.x;
		nextblock.c.y = nextblock.b.y + 1;
		nextblock.d.x = nextblock.c.x + 2;
		nextblock.d.y = nextblock.c.y;
		break;
	}

	block.status = 1;
	block.isdropped = 0;
	board[block.a.x][block.a.y] = 1;
	board[block.b.x][block.b.y] = 1;
	board[block.c.x][block.c.y] = 1;
	board[block.d.x][block.d.y] = 1;

	ghostblock = block;
	ghostblock = ghostblockmaker(block, ghostblock, board);
	board[ghostblock.a.x][ghostblock.a.y] = -1;
	board[ghostblock.b.x][ghostblock.b.y] = -1;
	board[ghostblock.c.x][ghostblock.c.y] = -1;
	board[ghostblock.d.x][ghostblock.d.y] = -1;

	gotoxy(nextblock.a.x, nextblock.a.y);
	printf("бс");
	gotoxy(nextblock.b.x, nextblock.b.y);
	printf("бс");
	gotoxy(nextblock.c.x, nextblock.c.y);
	printf("бс");
	gotoxy(nextblock.d.x, nextblock.d.y);
	printf("бс");

	//frame begins
	while (1)
	{
		boarddisplay(board);
		//check for user input
		for (int i = 0; i < (timeodelay / freqodelay); i++)
		{
			if (_kbhit() == 1)
			{
				key = _getch();
				if (key == 80 || key == 75 || key == 77 || key == 113 || key == 114 || key == 81 || key == 82)
				{
					if (key == 80) //soft drop
						score++;
					board[block.a.x][block.a.y] = 0;
					board[block.b.x][block.b.y] = 0;
					board[block.c.x][block.c.y] = 0;
					board[block.d.x][block.d.y] = 0;
					gotoxy(block.a.x, block.a.y);
					printf(" ");
					gotoxy(block.b.x, block.b.y);
					printf(" ");
					gotoxy(block.c.x, block.c.y);
					printf(" ");
					gotoxy(block.d.x, block.d.y);
					printf(" ");

					switch (block.whatblock)
					{
					case 0: //line 
						block = linerotater(block, board, key);
						break;
					case 1: //O 
						block = Orotater(block, board, key);
						break;
					case 2: //L
						block = Lrotater(block, board, key);
						break;
					case 3: //J
						block = Jrotater(block, board, key);
						break;
					case 4: //S
						block = Srotater(block, board, key);
						break;
					case 5: //T
						block = Trotater(block, board, key);
						break;
					case 6: //Z
						block = Zrotater(block, board, key);
						break;
					}

					board[ghostblock.a.x][ghostblock.a.y] = 0;
					board[ghostblock.b.x][ghostblock.b.y] = 0;
					board[ghostblock.c.x][ghostblock.c.y] = 0;
					board[ghostblock.d.x][ghostblock.d.y] = 0;
					gotoxy(ghostblock.a.x, ghostblock.a.y);
					printf(" ");
					gotoxy(ghostblock.b.x, ghostblock.b.y);
					printf(" ");
					gotoxy(ghostblock.c.x, ghostblock.c.y);
					printf(" ");
					gotoxy(ghostblock.d.x, ghostblock.d.y);
					printf(" ");
					ghostblock = ghostblockmaker(block, ghostblock, board);
					board[ghostblock.a.x][ghostblock.a.y] = -1;
					board[ghostblock.b.x][ghostblock.b.y] = -1;
					board[ghostblock.c.x][ghostblock.c.y] = -1;
					board[ghostblock.d.x][ghostblock.d.y] = -1;

					board[block.a.x][block.a.y] = 1;
					board[block.b.x][block.b.y] = 1;
					board[block.c.x][block.c.y] = 1;
					board[block.d.x][block.d.y] = 1;

					boarddisplay(board);

					//check if the block has dropped on the floor
					if (block.a.y == 22 || block.b.y == 22 || block.c.y == 22 || block.d.y == 22)
					{
						block.isdropped = 1;
						goto JUMP;
					}
					//collision check
					switch (block.whatblock)
					{
					case 0:
						//line
						if (block.status == 1)
						{
							if (board[block.a.x][block.a.y + 1] == 1 || board[block.b.x][block.b.y + 1] == 1 || board[block.c.x][block.c.y + 1] == 1 || board[block.d.x][block.d.y + 1] == 1)
								block.isdropped = 1;
						}
						if (block.status == 2 || block.status == -2)
							if (board[block.d.x][block.d.y + 1] == 1)
								block.isdropped = 1;
						break;
					case 1:
						//O
						if (board[block.c.x][block.c.y + 1] == 1 || board[block.d.x][block.d.y + 1] == 1)
							block.isdropped = 1;
						break;
					case 2:
						//L
						if (block.status == 1)
							if (board[block.a.x][block.a.y + 1] == 1 || board[block.b.x][block.b.y + 1] == 1 || board[block.c.x][block.c.y + 1] == 1)
								block.isdropped = 1;
						if (block.status == 2)
							if (board[block.c.x][block.c.y + 1] == 1 || board[block.d.x][block.d.y + 1] == 1)
								block.isdropped = 1;
						if (block.status == -2)
							if (board[block.a.x][block.a.y + 1] == 1 || board[block.d.x][block.d.y + 1] == 1)
								block.isdropped = 1;
						if (block.status == 3)
							if (board[block.b.x][block.b.y + 1] == 1 || board[block.c.x][block.c.y + 1] == 1 || board[block.d.x][block.d.y + 1] == 1)
								block.isdropped = 1;
						break;
					case 3:
						//J
						if (block.status == 1)
							if (board[block.a.x][block.a.y + 1] == 1 || board[block.b.x][block.b.y + 1] == 1 || board[block.c.x][block.c.y + 1] == 1)
								block.isdropped = 1;
						if (block.status == 2)
							if (board[block.c.x][block.c.y + 1] == 1 || board[block.d.x][block.d.y + 1] == 1)
								block.isdropped = 1;
						if (block.status == -2)
							if (board[block.a.x][block.a.y + 1] == 1 || board[block.d.x][block.d.y + 1] == 1)
								block.isdropped = 1;
						if (block.status == 3)
							if (board[block.a.x][block.a.y + 1] == 1 || board[block.b.x][block.b.y + 1] == 1 || board[block.d.x][block.d.y + 1] == 1)
								block.isdropped = 1;
						break;
					case 4:
						//about S
						if (block.status == 1)
							if (board[block.a.x][block.a.y + 1] == 1 || board[block.b.x][block.b.y + 1] == 1 || board[block.d.x][block.d.y + 1] == 1)
								block.isdropped = 1;
						if (block.status == 2)
							if (board[block.d.x][block.d.y + 1] == 1 || board[block.b.x][block.b.y + 1] == 1)
								block.isdropped = 1;
						if (block.status == -2)
							if (board[block.a.x][block.a.x + 1] == 1 || board[block.c.x][block.c.y + 1] == 1)
								block.isdropped = 1;
						break;
					case 5:
						//about T
						if (block.status == 1)
							if (board[block.a.x][block.a.y + 1] == 1 || board[block.b.x][block.b.y + 1] == 1 || board[block.c.x][block.c.y + 1] == 1)
								block.isdropped = 1;
						if (block.status == 2)
							if (board[block.c.x][block.c.y + 1] == 1 || board[block.d.x][block.d.y + 1] == 1)
								block.isdropped = 1;
						if (block.status == -2)
							if (board[block.a.x][block.a.y + 1] == 1 || board[block.d.x][block.d.y + 1] == 1)
								block.isdropped = 1;
						if (block.status == 3)
							if (board[block.d.x][block.d.y + 1] == 1 || board[block.a.x][block.a.y + 1] == 1 || board[block.c.x][block.c.y + 1] == 1)
								block.isdropped = 1;
						break;
					case 6:
						//Z
						if (block.status == 1)
							if (board[block.c.x][block.c.y + 1] == 1 || board[block.d.x][block.d.y + 1] == 1 || board[block.a.x][block.a.y + 1] == 1)
								block.isdropped = 1;
						if (block.status == 2)
							if (board[block.d.x][block.d.y + 1] == 1 || board[block.b.x][block.b.y + 1] == 1)
								block.isdropped = 1;
						if (block.status == -2)
							if (board[block.a.x][block.a.y + 1] == 1 || board[block.c.x][block.c.y + 1] == 1)
								block.isdropped = 1;
						break;
					}

					if (block.isdropped == 1)
						goto JUMP;

					boarddisplay(board);
				}

				else if (key == 80 || key == 112) //pause the game
				{
					pauser();
				}
				else
					continue;
			}
			Sleep(freqodelay);
		}

		boarddisplay(board);

	JUMP:
		if (block.isdropped == 1) //if the block has dropped on the floor
		{
			if (block.a.y <4)
			{
				system("cls");
				for (int boxybox = 1; boxybox < width - 1; boxybox++)
				{
					gotoxy(boxybox, 0);
					printf("-");
					gotoxy(boxybox, height - 1);
					printf("-");
				}

				for (int boxybox = 1; boxybox < height - 1; boxybox++)
				{
					gotoxy(0, boxybox);
					printf("|");
					gotoxy(width - 1, boxybox);
					printf("|");
				}

				for (int boxybox = xsquare + 1; boxybox <xsquare + 2 * widsquare + 1; boxybox++)
				{
					gotoxy(boxybox, ysquare);
					printf("-");
					gotoxy(boxybox, ysquare + widsquare + 1);
					printf("-");
				}

				for (int boxybox = ysquare + 1; boxybox < ysquare + widsquare + 1; boxybox++)
				{
					gotoxy(xsquare, boxybox);
					printf("|");
					gotoxy(xsquare + 2 * widsquare + 1, boxybox);
					printf("|");
				}

				gotoxy(5, 5);
				printf("GAME OVER!");

				gotoxy(xsquare, 1);
				printf("LEVEL: ");
				gotoxy(xsquare + 6, 1);
				printf("%d", level);
				gotoxy(xsquare, 3);
				printf("SCORE: ");
				gotoxy(xsquare + 6, 3);
				printf("%d", score);
				gotoxy(xsquare, 5);
				printf("NEXT:");

				PlaySound(NULL, NULL, SND_ASYNC);

				goto FINALLY;
			}

			gotoxy(nextblock.a.x, nextblock.a.y);
			printf(" ");
			gotoxy(nextblock.b.x, nextblock.b.y);
			printf(" ");
			gotoxy(nextblock.c.x, nextblock.c.y);
			printf(" ");
			gotoxy(nextblock.d.x, nextblock.d.y);
			printf(" ");

			block = spawner(block);

			ghostblock = ghostblockmaker(block, ghostblock, board);

			board[ghostblock.a.x][ghostblock.a.y] = -1;
			board[ghostblock.b.x][ghostblock.b.y] = -1;
			board[ghostblock.c.x][ghostblock.c.y] = -1;
			board[ghostblock.d.x][ghostblock.d.y] = -1;

			gotoxy(nextblock.a.x, nextblock.a.y);
			printf("бс");
			gotoxy(nextblock.b.x, nextblock.b.y);
			printf("бс");
			gotoxy(nextblock.c.x, nextblock.c.y);
			printf("бс");
			gotoxy(nextblock.d.x, nextblock.d.y);
			printf("бс");

			board = linedeleter(board, block);

			numblock--;
		}

		if (block.isdropped == 0) //if the block hasn't dropped
		{
			board[block.a.x][block.a.y] = 0;
			board[block.b.x][block.b.y] = 0;
			board[block.c.x][block.c.y] = 0;
			board[block.d.x][block.d.y] = 0;
			gotoxy(block.a.x, block.a.y);
			printf(" ");
			gotoxy(block.b.x, block.b.y);
			printf(" ");
			gotoxy(block.c.x, block.c.y);
			printf(" ");
			gotoxy(block.d.x, block.d.y);
			printf(" ");
			block.a.y += speed;
			block.b.y += speed;
			block.c.y += speed;
			block.d.y += speed;
			board[block.a.x][block.a.y] = 1;
			board[block.b.x][block.b.y] = 1;
			board[block.c.x][block.c.y] = 1;
			board[block.d.x][block.d.y] = 1;

			//check if it was dropped
			if (block.a.y == 22 || block.b.y == 22 || block.c.y == 22 || block.d.y == 22)
			{
				block.isdropped = 1;
				goto JUMP;
			}
			//collision check
			switch (block.whatblock)
			{
			case 0:
				//line
				if (block.status == 1)
				{
					if (board[block.a.x][block.a.y + 1] == 1 || board[block.b.x][block.b.y + 1] == 1 || board[block.c.x][block.c.y + 1] == 1 || board[block.d.x][block.d.y + 1] == 1)
						block.isdropped = 1;
				}
				if (block.status == 2 || block.status == -2)
					if (board[block.d.x][block.d.y + 1] == 1)
						block.isdropped = 1;
				break;
			case 1:
				//O
				if (board[block.c.x][block.c.y + 1] == 1 || board[block.d.x][block.d.y + 1] == 1)
					block.isdropped = 1;
				break;
			case 2:
				//L
				if (block.status == 1)
					if (board[block.a.x][block.a.y + 1] == 1 || board[block.b.x][block.b.y + 1] == 1 || board[block.c.x][block.c.y + 1] == 1)
						block.isdropped = 1;
				if (block.status == 2)
					if (board[block.c.x][block.c.y + 1] == 1 || board[block.d.x][block.d.y + 1] == 1)
						block.isdropped = 1;
				if (block.status == -2)
					if (board[block.a.x][block.a.y + 1] == 1 || board[block.d.x][block.d.y + 1] == 1)
						block.isdropped = 1;
				if (block.status == 3)
					if (board[block.b.x][block.b.y + 1] == 1 || board[block.c.x][block.c.y + 1] == 1 || board[block.d.x][block.d.y + 1] == 1)
						block.isdropped = 1;
				break;
			case 3:
				//J
				if (block.status == 1)
					if (board[block.a.x][block.a.y + 1] == 1 || board[block.b.x][block.b.y + 1] == 1 || board[block.c.x][block.c.y + 1] == 1)
						block.isdropped = 1;
				if (block.status == 2)
					if (board[block.c.x][block.c.y + 1] == 1 || board[block.d.x][block.d.y + 1] == 1)
						block.isdropped = 1;
				if (block.status == -2)
					if (board[block.a.x][block.a.y + 1] == 1 || board[block.d.x][block.d.y + 1] == 1)
						block.isdropped = 1;
				if (block.status == 3)
					if (board[block.a.x][block.a.y + 1] == 1 || board[block.b.x][block.b.y + 1] == 1 || board[block.d.x][block.d.y + 1] == 1)
						block.isdropped = 1;
				break;
			case 4:
				//about S
				if (block.status == 1)
					if (board[block.a.x][block.a.y + 1] == 1 || board[block.b.x][block.b.y + 1] == 1 || board[block.d.x][block.d.y + 1] == 1)
						block.isdropped = 1;
				if (block.status == 2)
					if (board[block.d.x][block.d.y + 1] == 1 || board[block.b.x][block.b.y + 1] == 1)
						block.isdropped = 1;
				if (block.status == -2)
					if (board[block.a.x][block.a.x + 1] == 1 || board[block.c.x][block.c.y + 1] == 1)
						block.isdropped = 1;
				break;
			case 5:
				//about T
				if (block.status == 1)
					if (board[block.a.x][block.a.y + 1] == 1 || board[block.b.x][block.b.y + 1] == 1 || board[block.c.x][block.c.y + 1] == 1)
						block.isdropped = 1;
				if (block.status == 2)
					if (board[block.c.x][block.c.y + 1] == 1 || board[block.d.x][block.d.y + 1] == 1)
						block.isdropped = 1;
				if (block.status == -2)
					if (board[block.a.x][block.a.y + 1] == 1 || board[block.d.x][block.d.y + 1] == 1)
						block.isdropped = 1;
				if (block.status == 3)
					if (board[block.d.x][block.d.y + 1] == 1 || board[block.a.x][block.a.y + 1] == 1 || board[block.c.x][block.c.y + 1] == 1)
						block.isdropped = 1;
				break;
			case 6:
				//Z
				if (block.status == 1)
					if (board[block.c.x][block.c.y + 1] == 1 || board[block.d.x][block.d.y + 1] == 1 || board[block.a.x][block.a.y + 1] == 1)
						block.isdropped = 1;
				if (block.status == 2)
					if (board[block.d.x][block.d.y + 1] == 1 || board[block.b.x][block.b.y + 1] == 1)
						block.isdropped = 1;
				if (block.status == -2)
					if (board[block.a.x][block.a.y + 1] == 1 || board[block.c.x][block.c.y + 1] == 1)
						block.isdropped = 1;
				break;
			}

			if (block.isdropped == 1)
				goto JUMP;
		}

		if (numblock == 0)
		{
			numblock = 20;
			level++;
			if (timeodelay > 300)
				timeodelay -= 100;
			else
				continue;
		}
		//check elapsed time for music
		elapsedtime = clock();
		switch (numomusic)
		{
		case 1:
			if ((elapsedtime - currenttime) / 1000 == 102 || (elapsedtime - currenttime) / 1000 == 103 || (elapsedtime - currenttime) / 1000 == 104)
			{
				PlaySound(TEXT("Stronkest.wav"), NULL, SND_ASYNC);
				currenttime = elapsedtime;
				numomusic = 2;
			}
			break;
		case 2:
			if ((elapsedtime - currenttime) / 1000 == 147 || (elapsedtime - currenttime) / 1000 == 148 || (elapsedtime - currenttime) / 1000 == 149)
			{
				PlaySound(TEXT("CheekiBreeki.wav"), NULL, SND_ASYNC);
				currenttime = elapsedtime;
				numomusic = 3;
			}
			break;
		case 3:
			if ((elapsedtime - currenttime) / 1000 == 158 || (elapsedtime - currenttime) / 1000 == 159 || (elapsedtime - currenttime) / 1000 == 160)
			{
				PlaySound(TEXT("Tetris.wav"), NULL, SND_ASYNC);
				currenttime = elapsedtime;
				numomusic = 4;
			}
			break;
		case 4:
			if ((elapsedtime - currenttime) / 1000 == 91 || (elapsedtime - currenttime) / 1000 == 92 || (elapsedtime - currenttime) / 1000 == 93)
			{
				PlaySound(TEXT("Smug.wav"), NULL, SND_ASYNC);
				currenttime = elapsedtime;
				numomusic = 1;
			}
			break;
		}

		//lastly, print score and current level
		gotoxy(xsquare + 6, 1);
		printf("%d", level);
		gotoxy(xsquare + 6, 3);
		printf("%d", score);
	}

FINALLY:

	for (int i = 0; i < width; i++)
		free(board[i]);
	free(board);
	return 0;

}

void boarddisplay(int **board)
{
	for (int i = 1; i < width - 1; i += 2)
	{
		for (int j = 1; j < height - 1; j++)
		{
			if (board[i][j] == 1)
			{
				gotoxy(i, j);
				printf("бс");
			}

			if (board[i][j] == -1)
			{
				gotoxy(i, j);
				printf("бр");
			}
		}
	}
}

void startmenu(void) 
{
	int temp = 1;
	int key;
	PlaySound(TEXT("TSR.wav"), NULL, SND_ASYNC);
MAIN_MENU:
	system("cls");
	gotoxy(8, 1);
	printf("Tetris");
	gotoxy(5, 3);
	printf("-Pure C Edition-");
	gotoxy(5, 7);
	printf("Press m for help");

	while (1)
	{
		lengthotime = clock() / 1000;
		if (lengthotime == 252 * temp || lengthotime == 251 * temp)
		{
			PlaySound(TEXT("TSR.wav"), NULL, SND_ASYNC);
			temp++;
		}
		gotoxy(5, 5);
		color(0);
		printf("Press s to start");
		for (int i = 0; i < (textdelay / freqodelay); i++)
		{
			if (_kbhit() == 1)
			{
				key = _getch();
				if (key == 115 || key == 83)
					goto EXIT;
				if (key == 109 || key == 77)
				{
					manual();
					goto MAIN_MENU;
				}
			}
			Sleep(freqodelay);
		}
		gotoxy(5, 5);
		color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		printf("Press s to start");
		for (int i = 0; i < (textdelay / freqodelay); i++)
		{
			if (_kbhit() == 1)
			{
				key = _getch();
				if (key == 115 || key == 83)
					goto EXIT;
				if (key == 109 || key == 77)
				{
					manual();
					goto MAIN_MENU;
				}
			}
			Sleep(freqodelay);
		}

	}

EXIT:
	color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	PlaySound(NULL, NULL, SND_ASYNC);
	system("cls");

	for (int i = 1; i < width - 1; i++)
	{
		gotoxy(i, 0);
		printf("-");
		gotoxy(i, height - 1);
		printf("-");
	}

	for (int i = 1; i < height - 1; i++)
	{
		gotoxy(0, i);
		printf("|");
		gotoxy(width - 1, i);
		printf("|");
	}
	
	//3...2....1...GO! 

	for (int i = 3; i > 0; i--)
	{
		gotoxy(10, 7);
		printf("%d", i);
		Sleep(1000);
	}

	gotoxy(10, 7);
	printf("GO!");
	Sleep(1000);
	gotoxy(10, 7);
	printf("    ");


	for (int i = xsquare + 1; i <xsquare + 2 * widsquare + 1; i++)
	{
		gotoxy(i, ysquare);
		printf("-");
		gotoxy(i, ysquare + widsquare + 1);
		printf("-");
	}

	for (int i = ysquare + 1; i < ysquare + widsquare + 1; i++)
	{
		gotoxy(xsquare, i);
		printf("|");
		gotoxy(xsquare + 2 * widsquare + 1, i);
		printf("|");
	}

	gotoxy(xsquare, 1);
	printf("LEVEL: ");
	gotoxy(xsquare + 6, 1);
	printf("%d", level);
	gotoxy(xsquare, 3);
	printf("SCORE: ");
	gotoxy(xsquare + 6, 3);
	printf("%d", score);
	gotoxy(xsquare, 5);
	printf("NEXT:");
}

struct block spawner(struct block block) //picks a random block and spawns it
{
	block.whatblock = nextblock.whatblock;

	do
	{
		nextblock.whatblock = rand() % 7;
	} while (nextblock.whatblock == block.whatblock);

	block.a.x = 7;
	block.a.y = 2;
	block.status = 1;
	block.isdropped = 0;

	switch (block.whatblock)
	{
	case 0: //line
		block.b.x = block.a.x + 2;
		block.c.x = block.b.x + 2;
		block.d.x = block.c.x + 2;
		block.d.y = block.c.y = block.b.y = block.a.y;
		break;
	case 1: // O
		block.b.x = block.a.x + 2;
		block.b.y = block.a.y;
		block.c.x = block.a.x;
		block.c.y = block.a.y + 1;
		block.d.x = block.a.x + 2;
		block.d.y = block.a.y + 1;
		break;
	case 2: //L
		block.c.y = block.b.y = block.a.y;
		block.d.y = block.a.y - 1;
		block.b.x = block.a.x + 2;
		block.c.x = block.b.x + 2;
		block.d.x = block.a.x;
		break;
	case 3: //J
		block.c.y = block.b.y = block.a.y;
		block.d.y = block.a.y - 1;
		block.b.x = block.a.x + 2;
		block.c.x = block.b.x + 2;
		block.d.x = block.c.x;
		break;
	case 4: //S
		block.b.x = block.a.x + 2;
		block.b.y = block.a.y;
		block.c.x = block.b.x;
		block.c.y = block.b.y - 1;
		block.d.x = block.c.x + 2;
		block.d.y = block.c.y;
		break;
	case 5: //T
		block.c.y = block.b.y = block.a.y;
		block.b.x = block.a.x + 2;
		block.c.x = block.b.x + 2;
		block.d.x = block.b.x;
		block.d.y = block.b.y - 1;
		break;
	case 6: //Z
		block.b.y = block.a.y;
		block.b.x = block.a.x + 2;
		block.c.x = block.b.x;
		block.c.y = block.b.y + 1;
		block.d.x = block.c.x + 2;
		block.d.y = block.c.y;
		break;
	}

	switch (nextblock.whatblock)
	{
	case 0: //Line
		nextblock.a.x = 25;
		nextblock.a.y = 9;
		nextblock.b.x = nextblock.a.x + 2;
		nextblock.c.x = nextblock.b.x + 2;
		nextblock.d.x = nextblock.c.x + 2;
		nextblock.d.y = nextblock.c.y = nextblock.b.y = nextblock.a.y;
		break;
	case 1: // O
		nextblock.a.x = 27;
		nextblock.a.y = 8;
		nextblock.b.x = nextblock.a.x + 2;
		nextblock.b.y = nextblock.a.y;
		nextblock.c.x = nextblock.a.x;
		nextblock.c.y = nextblock.a.y + 1;
		nextblock.d.x = nextblock.a.x + 2;
		nextblock.d.y = nextblock.a.y + 1;
		break;
	case 2: //L
		nextblock.a.x = 27;
		nextblock.a.y = 9;
		nextblock.c.y = nextblock.b.y = nextblock.a.y;
		nextblock.d.y = nextblock.a.y - 1;
		nextblock.b.x = nextblock.a.x + 2;
		nextblock.c.x = nextblock.b.x + 2;
		nextblock.d.x = nextblock.a.x;
		break;
	case 3: //J
		nextblock.a.x = 27;
		nextblock.a.y = 9;
		nextblock.c.y = nextblock.b.y = nextblock.a.y;
		nextblock.d.y = nextblock.a.y - 1;
		nextblock.b.x = nextblock.a.x + 2;
		nextblock.c.x = nextblock.b.x + 2;
		nextblock.d.x = nextblock.c.x;
		break;
	case 4: //S
		nextblock.a.x = 27;
		nextblock.a.y = 9;
		nextblock.b.x = nextblock.a.x + 2;
		nextblock.b.y = nextblock.a.y;
		nextblock.c.x = nextblock.b.x;
		nextblock.c.y = nextblock.b.y - 1;
		nextblock.d.x = nextblock.c.x + 2;
		nextblock.d.y = nextblock.c.y;
		break;
	case 5: //T
		nextblock.a.x = 27;
		nextblock.a.y = 9;
		nextblock.c.y = nextblock.b.y = nextblock.a.y;
		nextblock.b.x = nextblock.a.x + 2;
		nextblock.c.x = nextblock.b.x + 2;
		nextblock.d.x = nextblock.b.x;
		nextblock.d.y = nextblock.b.y - 1;
		break;
	case 6: //Z
		nextblock.a.x = 27;
		nextblock.a.y = 8;
		nextblock.b.y = nextblock.a.y;
		nextblock.b.x = nextblock.a.x + 2;
		nextblock.c.x = nextblock.b.x;
		nextblock.c.y = nextblock.b.y + 1;
		nextblock.d.x = nextblock.c.x + 2;
		nextblock.d.y = nextblock.c.y;
		break;
	}

	return block;
}

void manual(void) //shows game manual
{
	color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	int key;
	system("cls");
	gotoxy(xoftext, yoftext);
	printf("Press 'q' or 'Q' to rotate a block counter-clockwise.");
	gotoxy(xoftext, yoftext + 2);
	printf("Press 'r' or 'R' to rotate a block clockwise.");
	gotoxy(xoftext, yoftext + 4);
	printf("Use arrow keys to move or drop a block.");
	gotoxy(xoftext, yoftext + 6);
	printf("Press 'p' or 'P' to pause/unpause.");
	gotoxy(xoftext, yoftext + 8);
	printf("Press 'h' or 'H' to hard drop.");
	//m = 109 
	//M = 77
	//S = 83
	while (1)
	{
		gotoxy(xoftext, 11);
		color(0);
		printf("Press m to return to main menu");
		for (int j = 0; j < (textdelay / freqodelay); j++)
		{
			if (_kbhit() == 1)
			{
				key = _getch();
				if (key == 109 || key == 77)
					goto EXIT;
			}
			Sleep(freqodelay);
		}
		gotoxy(xoftext, 11);
		color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		printf("Press m to return to main menu");
		for (int j = 0; j < (textdelay / freqodelay); j++)
		{
			if (_kbhit() == 1)
			{
				key = _getch();
				if (key == 109 || key == 77)
					goto EXIT;
			}
			Sleep(freqodelay);
		}
	}

EXIT:
	color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}

void pauser(void)
{
	int key;

	for (int i = 1; i < 21; i++)
	{
		for (int j = 1; j < 23; j++)
		{
			gotoxy(i, j);
			printf(" ");
		}
	}

	gotoxy(8, 7);
	printf("PAUSED");

	while (1)
	{
		if (_kbhit() == 1)
		{
			key = _getch();
			if (key == 112 || key == 80)
				break;
		}
	}
	color(0);
	gotoxy(8, 7);
	printf("PAUSED");
	color(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}

struct block ghostblockmaker(struct block block, struct block ghostblock, int **board)
{
	ghostblock = block;

	switch (ghostblock.whatblock)
	{
	case 0://line
		if (ghostblock.status == 1)
			ghostblock.d.y = ghostblock.c.y = ghostblock.b.y = ghostblock.a.y = height - 2;
		if (ghostblock.status == 2 || ghostblock.status == -2)
		{
			ghostblock.d.y = height - 2;
			ghostblock.c.y = height - 3;
			ghostblock.b.y = height - 4;
			ghostblock.a.y = height - 5;
		}
		break;
	case 1: //O
		ghostblock.d.y = ghostblock.c.y = height - 2;
		ghostblock.b.y = ghostblock.a.y = height - 3;
		break;
	case 2: //L
		if (ghostblock.status == 1)
		{
			ghostblock.c.y = ghostblock.b.y = ghostblock.a.y = height - 2;
			ghostblock.d.y = height - 3;
		}
		if (ghostblock.status == 2)
		{
			ghostblock.c.y = height - 2;
			ghostblock.b.y = height - 3;
			ghostblock.a.y = ghostblock.d.y = height - 4;
		}
		if (ghostblock.status == -2)
		{
			ghostblock.d.y = ghostblock.a.y = height - 2;
			ghostblock.b.y = height - 3;
			ghostblock.c.y = height - 4;
		}
		if (ghostblock.status == 3)
		{
			ghostblock.d.y = height - 2;
			ghostblock.c.y = ghostblock.b.y = ghostblock.a.y = height - 3;
		}
		break;
	case 3: //J
		if (ghostblock.status == 1)
		{
			ghostblock.a.y = ghostblock.b.y = ghostblock.c.y = height - 2;
			ghostblock.d.y = height - 3;
		}
		if (ghostblock.status == 2)
		{
			ghostblock.d.y = ghostblock.c.y = height - 2;
			ghostblock.b.y = height - 3;
			ghostblock.a.y = height - 4;
		}
		if (ghostblock.status == -2)
		{
			ghostblock.a.y = height - 2;
			ghostblock.b.y = height - 3;
			ghostblock.c.y = ghostblock.d.y = height - 4;
		}
		if (ghostblock.status == 3)
		{
			ghostblock.d.y = height - 2;
			ghostblock.a.y = ghostblock.b.y = ghostblock.c.y = height - 3;
		}
		break;
	case 4: //S
		if (ghostblock.status == 1)
		{
			ghostblock.a.y = ghostblock.b.y = height - 2;
			ghostblock.c.y = ghostblock.d.y = height - 3;
		}
		if (ghostblock.status == 2)
		{
			ghostblock.d.y = height - 2;
			ghostblock.c.y = ghostblock.b.y = height - 3;
			ghostblock.a.y = height - 4;
		}
		if (ghostblock.status == -2)
		{
			ghostblock.a.y = height - 2;
			ghostblock.b.y = ghostblock.c.y = height - 3;
			ghostblock.d.y = height - 4;
		}
		break;
	case 5: //T
		if (ghostblock.status == 1)
		{
			ghostblock.a.y = ghostblock.b.y = ghostblock.c.y = height - 2;
			ghostblock.d.y = height - 3;
		}
		if (ghostblock.status == 2)
		{
			ghostblock.c.y = height - 2;
			ghostblock.b.y = ghostblock.d.y = height - 3;
			ghostblock.a.y = height - 4;
		}
		if (ghostblock.status == -2)
		{
			ghostblock.a.y = height - 2;
			ghostblock.b.y = ghostblock.d.y = height - 3;
			ghostblock.c.y = height - 4;
		}
		if (ghostblock.status == 3)
		{
			ghostblock.d.y = height - 2;
			ghostblock.a.y = ghostblock.b.y = ghostblock.c.y = height - 3;
		}
		break;
	case 6: //Z
		if (ghostblock.status == 1)
		{
			ghostblock.d.y = ghostblock.c.y = height - 2;
			ghostblock.a.y = ghostblock.b.y = height - 3;
		}
		if (ghostblock.status == 2)
		{
			ghostblock.d.y = height - 2;
			ghostblock.c.y = ghostblock.b.y = height - 3;
			ghostblock.a.y = height - 4;
		}
		if (ghostblock.status == -2)
		{
			ghostblock.a.y = height - 2;
			ghostblock.b.y = ghostblock.c.y = height - 3;
			ghostblock.d.y = height - 4;
		}
		break;
	}

	while (board[ghostblock.a.x][ghostblock.a.y] == 1 || board[ghostblock.b.x][ghostblock.b.y] == 1 || board[ghostblock.c.x][ghostblock.c.y] == 1 || board[ghostblock.d.x][ghostblock.d.y] == 1 || board[ghostblock.a.x][ghostblock.a.y - 1] == 1 || board[ghostblock.b.x][ghostblock.b.y - 1] == 1 || board[ghostblock.c.x][ghostblock.c.y - 1] == 1 || board[ghostblock.d.x][ghostblock.d.y - 1] == 1)
	{
		ghostblock.a.y--;
		ghostblock.b.y--;
		ghostblock.c.y--;
		ghostblock.d.y--;
	}

	return ghostblock;
}

int **linedeleter(int **board, struct block block) 
{
	int numformult = 100; //score added for a full line cleared
	int completedlines = 0;

	clear lines
	for (int i = 1; i<23; i++)
	{
		if (board[1][i] == 1 && board[3][i] == 1 && board[5][i] == 1 && board[7][i] == 1 && board[9][i] == 1 && board[11][i] == 1 && board[13][i] == 1 && board[15][i] == 1 && board[17][i] == 1 && board[19][i] == 1)
		{
			for (int temp = 1; temp < 20; temp += 2)
				board[temp][i] = 0;
			gotoxy(1, i);
			printf("                    ");
			completedlines++;
			for (int j = i - 1; j >0; j--)
			{
				for (int k = 1; k < width - 1; k += 2)
				{
					if (board[k][j] == 1)
					{
						gotoxy(k, j);
						printf(" ");
						board[k][j] = 0;
						board[k][j + 1] = 1;
					}
				}
			}
		}
	}
	/*
	board[block.a.x][block.a.y + 1] = board[block.b.x][block.b.y + 1] = board[block.c.x][block.c.y + 1] = board[block.d.x][block.d.y + 1] = 0;
	board[block.a.x][block.a.y ] = board[block.b.x][block.b.y] = board[block.c.x][block.c.y] = board[block.d.x][block.d.y] = 1;
	*/
	if (completedlines > 0)
	{
		for (int i = 0; i < completedlines - 1; i++)
		{
			numformult *= 2;
		}

		score += numformult;
	}

	return board;
}
