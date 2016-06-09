#include <stdio.h>
#include <stdlib.h>
#include "Stack2.h"

int main()
{
	Stack s1;
	init_stack(&s1);
	
	// for 문을 사용해서 s1 스택에 1 ~10ㄷ까지 넣으세ㅁ요
	for (int i=1; i<=10; i++)
	{
		push(&s1, i);
	}
	// 스택의 꼭대기 요소를 출력만 (꺼내지 말고) 하세요
	printf("%d\n" , top(s1));

	// 스택이 빌때 까지 루프 돌면서 꺼내서 출력하시오	
	while ( !isempty(s1) )
	{
		printf("pop: %d\n", pop(&s1));
	}
}

