#include <stdio.h>

int main()
{
	int n1 = 10;
	int n2 = n1;

	double d1 = 3.4;
	double d2 = d1;

	// 핵심 3. 모든 변수는 자신과 동일 타입의 변수로 복사 생성 될수 있다. (초기화 될수 있다는것)
	// 핵시 4. 단, 배열만은 자신의 타입으로 초기화 될수 없다.(메모리 크기가 크므로 성는저하 우려)
	// 핵심 5. 배열은 자신의 1번ㄷ째 요소의 타입의 주소로 암시적으로 형변환 될수 있다. 	
	int x1[5] = {1, 2, 3, 4, 5};
	//int p1[5] = x1;	안됨
	int* p1 = x1; //ok 배열의 이름은 배열의 1번쨰 요소의 주소로 암시적으로 형변환됨.
				// 절대 배열의 주소가 아님
	int(*p2)[5] = &x1; // 이 표현이 배열의 주소임...

	printf("%p, %p\n", p1, p1+1); // 4byte 증가
	printf("%p, %p\n", p2, p2+1); // 20byte 증가

}
