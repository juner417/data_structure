#include <stdio.h>
#include <time.h>
#include <stdlib.h>
/*
int hashing(int key)
{
	return key % 16;
}
*/
// mid-squre 알고리즘 : 키값을 제곱한 후에 중간에 임의 비트만큼 꺼낸다
int hashing(int key)
{
	return ((key * key) & 0x00000F00) >> 8; //0~15 사이 
}
int main()
{
	srand(time(0));
	int x[16] = {0};
	
	for (int i = 0; i<10000; i++)
	{
		x[hashing(rand())] += 1; // 잘 생각해보세요
	}
	
	for (int i = 0; i<16; i++)
	{
		printf("[%d] : %d\n", i, x[i]);
	}
}
