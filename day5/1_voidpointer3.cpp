// 1_voidpointer3
#include <stdio.h>
//핵심1. 모든타입의 주소를 담을수 있는 포인터
//2. 주소정보만 있고 타입은 없다(크기가 없다)
// p + 1, *p 등 크기가 필요한 모든 연산을 error
int main()
{
	int n = 100;
	short s = 10;

	// char* p1 = &n; -> error// 강제캐스팅(명시적캐스팅)하면 되지만.
       			// 암시적으로는 다른 타입의 주소에 넣을수 있다.
	// void a ; // error, void 타입의 변수는 만들수 없다. 
	void* p2 = &n;	// void*는 모든 주소를 담는다. 
	p2 = p2 + 1; // 몇바이트 증가? error, void*는 주소만 있고
				// 크기정보가 없는 포인터이다. 
	printf("%d\n", *p2); //error 크기와 관련된 연산은 모두 에러남
 	// void* 특징 
}
