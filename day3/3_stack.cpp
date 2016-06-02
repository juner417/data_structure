// 3_stack
#include <stdio.h>
// 마지막 넣은 요소가 먼저 나오는 자료구조
// LIFO(last in first out)
// 넣는 함수: push
// 꺼네는 함수 : pop

int main()
{
	push(10);
	push(20);
	push(30);

	printf("%d\n", pop()); // 30
	printf("%d\n", pop()); // 20
}
