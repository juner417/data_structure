//1_voidpointer5
#include <stdio.h>

// 핵심1. 
// 2. void*인자는 사용할 때 가장작은 크기의 타입의 포인터로 캐스팅후 사용(char)
// 3. 인자를 전달할때 인자타입의 크기도 같이 전달해야 한다. 
void swap(void* a, void* b, int sz)
{
	char* p1 = (char*)a;
	char* p2 = (char*)b;

	for (int i = 0; i < sz; i++)
	{
		char temp = *(p1+i);
		*(p1+i) = *(p2+i);
		*(p2+i) = temp;
	}
}

int main()
{
	int x = 0x11223344;
	int y = 0x66778899;

	swap(&x,&y,sizeof(x));
	printf("%x, %x\n", x, y); // 20, 10
}
