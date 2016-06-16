#include <stdio.h>

// 핵심 1. 전역변수 대신 여러개의 버퍼가 필요하면 함수 인자화 한다
//      값을 담아 오려면 주소를 보낸다. 

//int buf = 0;

void set(int* buf)
{
	// buf를 10으로 채워
	*buf = 10;
}

//int* pInt = 0;

void alloc(int** pInt)
{
	//pInt에 10파이트 할당
	*pInt = (int*)malloc(10);
}
int main()
{
	int buf1, buf2;
	set(&buf1);
	
	int* pInt1;
	int* pInt2;
	alloc(&pInt1);
}
