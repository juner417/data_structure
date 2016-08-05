#include <stdio.h>

struct People
{
	int data1;
	int data2;
};

int main() 
{
	struct People p;
	
	printf("People : %p\n", &p);
	printf("People : %p\n", &(p.data2));

	// 0번지를 강제로 구조체를 캐스팅 할수는 있다.
	// 하지만 값을 넣으면 runtime error 입니다. 
	//((People*)(0))->data2 = 10;//0번지를 강제로 Peopel 캐스팅 
	//아래 코드가 People구조체 안에서 data2라는 멤버가 몇 바이트
    // 떨어져 있는지 조사하는기술.
	printf("%p\n", &( ((People*)0)->data2) );

#define OFFSET_OF(TYPE, MEMBER)	(int)&(((TYPE*)0)->MEMBER)
	printf("%d\n", OFFSET_OF(People, data2));
}
