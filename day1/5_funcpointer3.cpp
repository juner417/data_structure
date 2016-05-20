#include <stdio.h>
#include <stdlib.h>

int foo(int a, double d)
{
	printf("foo : %d, %f \n", a, d);

	return 0;
}

// 함수 포인터를 바로 사용하면 복잡해 보입니다. 
// 반ㅅ드시 typedef를 사용해서 함수 포인터 ㄷ타입을 만드세요

typedef int(*PF)(int, double); // PF 는 함수포인터 타입입니다. 

//void goo(int a, double d, int(*f)(int, double)) 
void goo(int a, double d, PF f)
{
	f(a, d);

}

int main() 
{
	// goo 함수를 만드세요a
    goo(1, 3.4, foo); // 결과가 foo : 1, 3.4 
}	
