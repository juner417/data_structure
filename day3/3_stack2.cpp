// 3_stack2
#include <stdio.h>
// 스텍을 구현하는 방법은 아주 다양합니다. 
// 제일 쉬운 버전 - 배열사용
int buf[100];
int index = 0;

void push(int a)
{
//	buf[index] = a;
//	++index;
	buf[index++] = a;
}

int pop()
{
	// 배열에 넣고 index를 하나를 증가시킴 
	// 그렇게 되면 현재 index는 아무것도 없음
	// 그래서 index를 먼저 내려야 함
//	--index;
//	return buf[index];
	return buf[--index];
}
int main()
{
	push(10);
	push(20);
	push(30);

	printf("%d\n", pop()); // 30
	printf("%d\n", pop()); // 20
}
