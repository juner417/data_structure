// 3_stack4
#include <stdio.h>
#include "Stack.h"
// v3. 스택의 내부 구조를 표현하려면
//		배열과 index가 필요하다. 
//	구조체로 묶어서 사용하자. 
int main()
{
	Stack s1;
	init(&s1);

	push(&s1, 10);
	push(&s1, 20);
	push(&s1, 30);

	while( ! isempty(&s1) )
	{
		printf("%d\n", pop(&s1)); 
	}
}
