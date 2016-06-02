// 3_stack2
#include <stdio.h>
// v2. 2ㅇ개 이상의 스택을 사용할 수 있게 해보자
// 저장공간과 index를 함수 인자로 만들자

void push(int* buf, int* index, int a)
{
	buf[(*index)++] = a;
}

int pop(int* buf, int* index)
{
	return buf[--(*index)];
}

int main()
{
	int buf1[100];
	int idx1 = 0;
	int buf2[100];
	int idx2 = 0;

	push(buf1, &idx1, 10);
	push(buf1, &idx1, 20);
	push(buf2, &idx2, 30);

	// buf에서 꺼네시오
	printf("%d\n", pop(buf1, &idx1)); // 20
	printf("%d\n", pop(buf2, &idx2)); // 30
}
