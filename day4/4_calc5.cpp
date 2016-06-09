// 4_calc
#include <stdio.h>
#include "Stack.h"

// infix -> postfix 변환

char output[20] = { 0 };
int idx = 0;

// 연산자인지 확인 하는 함수 
int is_op(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}
// 연산자의 우선순위를 알려주는 함수
int priority(char c)
{
	if (c == '+' || c == '-' ) return 1;
	if (c == '*' || c == '/' ) return 2;

	return 0;
}
// 알고리즘3 - 괄호
// 1. 피연산자는 출력버퍼에 옮긴다. 
// 2. 연산자를 만나면 스택에서 자신보다 우선순위가 낮은 연산자를 
// 만날 때 까지 모두 꺼내서 (결국 높은 우선순위를 꺼낸다는것) 
// 출력하고 자신을 스택에 넣는다.
//  ( ) 처리를 위한 알고리즘
// 3. ( 를 만나면 무조건 스택으로 !!
// 4. ) 를 만나면 스택에서 ( 를 꺼낼때까지 무조건 꺼내서 출력버퍼에
//   넣고 ( 는 버린다. (출력버퍼에 넣지 말라는 의미) 
// 5. 모든 입력이 끝나면 스택에 있는 요소를 출력 버퍼에 옮긴다. 

char s[] = "3*4+2"; 
int main()
{
	Stack st;
	init(&st);

	char* p = s; 

	while (*p != 0)
	{
		if ( is_op(*p) ) 
		{	
			while ( !isempty(&st) )
			{	
				if (priority(top(&st)) <= priority(*p)) break;	
			
				output[idx++] = pop(&st);	
			}
			push(&st, *p);
		} 
		else
			output[idx++] = *p; // 피연산자는 출력 버퍼
		++p;
	}

	//-------------------------------------------
	while (!isempty(&st))
	{
		char c = pop(&st);
		output[idx++] = c;
	}
	// 출력버퍼의 내용 확인	
	printf("%s\n", output); 
}
