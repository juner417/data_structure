#include <stdio.h>

int buf = 0;

void set()
{
	// buf를 10으로 채워
	buf = 10;
}

int* pInt = 0;

void alloc()
{
	//pInt에 10파이트 할당
	pInt = (int*)malloc(10);
}
int main()
{

}
