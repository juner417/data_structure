// 4_calc
#include <stdio.h>
#include "Stack.h"

// infix -> postfix 변환

char s[] = "3+4-2"; //5

char output[20] = { 0 };
int idx = 0;

// 연산자인지 확인 하는 함수 
int is_op(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}
// 알고리즘1/
// 1. 피연산자는 출력버퍼에 옮긴다. 
// 2. 연산자는 스택에 넣는다. 
//3. 모든 입력이 끝나면 스택에 있는 요소를 출력 버퍼에 옮긴다. 


int main()
{
	Stack st;
	init(&st);

	char* p = s; // 입력버퍼의 처음을 가르키게 한다. 

	while (*p != 0)
	{
		if ( is_op(*p) ) // 연산자는 스택에 넣기
			push(&st, *p); 
		else
			output[idx++] = *p; // 피연산자는 출력 버퍼
		++p;
	}
	// 모든 입력을 마치면 스택에 있는 모든 요소를 출력 버퍼에
	while (!isempty(&st))
	{
		char c = pop(&st);
		output[idx++] = c;
	}
	// 출력버퍼의 내용 확인	
	printf("%s\n", output); // 342-+
}
