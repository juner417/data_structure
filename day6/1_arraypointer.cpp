#include <stdio.h>

int main()
{
	int n; // 변수 이름 : n, data type: int
	double d;  //
	int *p = &n; // 변수 이름 : p , data type : int*
	// 핵심1. 선언문에서 변수의 이름을 제외하면 타입만 남는다. 
	// 핵심2. 변수의 주소를 얻으려면 "&변수이름", 
	// 		  변수의 주소를 담으려면 변수선언에서 변수명 앞에 *을 붙인다. 

	int x[10]; // 변수이름 : x , 타입 : int[10] <= 중요함. 배열 타입의 개념
	// x 의 주소를 꺼내서 포인터 변수에 담아 보세요...
	//int *p2 = x;  // 절대 아님
	int (*p3)[10] = &x; // 정확한 표현
}
