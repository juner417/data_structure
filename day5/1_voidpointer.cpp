// 1_void pointer
#include <stdio.h>
// 핵심 : 포인터 변수 + 1 -> 포인터가 가르키는 대상체의 크기만큼 증가
// ex ) int* 라면 +1은 4바이트 증가 p3=400 -> p3+1 -> p3=404
int main()
{
	// 포인터 연산 
	char c = 0;
	short s = 0;
	int n = 0;

	char* p1 = &c;
	short* p2 = &s;
	int* p3 = &n;

	printf("%p, %p\n", p1, p1+1);
	printf("%p, %p\n", p2, p2+1);
	printf("%p, %p\n", p3, p3+1);
}
