#pragma once

struct point
{
	int x;
	int y;
};

struct block
{
	struct point a; 
	struct point b; 
	struct point c; 
	struct point d; 

	int whatblock; //what type of block
	int status; //what status the block is in: 1 for default, 2 for 90 degrees rotated clock wise, -2 for 90 degrees rotated counterclock wise, 3 for 180 degrees rotated
	int isdropped; //1 if block is dropped, 0 if it isn't
};

struct block collisionchecker(struct block block, int **board);

struct block linerotater(struct block block, int ** board, int key);
struct block Orotater(struct block block, int **board, int key);
struct block Trotater(struct block block, int **board, int key);
struct block Srotater(struct block block, int **board, int key);
struct block Zrotater(struct block block, int **board, int key);
struct block Lrotater(struct block block, int **board, int key);
struct block Jrotater(struct block block, int **board, int key);
