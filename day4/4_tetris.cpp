//4_tetris

#include <stdio.h>
#include <stdlib.h>

void gotoxy(int x,int y)
{
	 printf("%c[%d;%df",0x1B,y,x);
}

int block1[4][4] = { 0,1,0,0,
					 0,1,0,0,
					 1,1,1,0,
					 0,0,0,0 };

void print_block(int x, int y)
{
	for (int j = 0; j<4; j++)
	{
	    for (int i = 0; i<4; i++)
		{
			if (block1[j][i] == 1)
			{
				gotoxy(x+i * 2, y + j);
				printf("◼︎");
			}
		}
	}
}

int main() 
{
	system("clear"); 
	print_block(10,10);
}
