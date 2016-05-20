#include <stdio.h>
#include <stdlib.h>

int foo(int a, double d)
{
	printf("foo : %d, %f \n", a, d);

	return 0;
}

int main() 
{	
	// foo 의 주소를 담는 포인터 변수 f를 만드세요
    //int(*f)(int,double) = foo;
    int(*f)(int,double) = &foo;

	// f를 사용해서 foo()를 호출 하세요
	f(1, 3.4);

}
