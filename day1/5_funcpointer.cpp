#include <stdio.h>
#include <stdlib.h>

void foo(int a)
{
	printf("foo %d\n", a);
}

int main()
{
	int n = 10;

	printf("%p\n", &n);
	printf("%p\n", &foo); // 함수 주소, 코드메모리에 함수가 저장되어 있다. 
	printf("%p\n", foo); //함수는 주소연산자를 사용하지 않고 이름만 적어도 주소가 나온다.

	// int 주소를 담는 변수 만들기	
    int *p = &n;
	// 함수 주소를 담는 변수 만들기
	void(*f)(int) = &foo; // 또는 foo

	foo(10);
	f(10); // foo(10) 과 동일 *f에 foo의 주소를 넣기 때문

}
