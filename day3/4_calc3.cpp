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
// 알고리즘1/
// 1. 피연산자는 출력버퍼에 옮긴다. 
// 2. 연산자는 스택에 넣는다. 
//3. 모든 입력이 끝나면 스택에 있는 요소를 출력 버퍼에 옮긴다. 


//char s[] = "3+4-2"; //5
//char s[] = "3+4*2"; //11
char s[] = "3*4+2"; //14 그런데 위 알고리즘을 사용하면 
					//연산자 우선순위가 고려되지 않는다. 
					// 알고리즘을 변경하자 
int main()
{
	Stack st;
	init(&st);

	char* p = s; 

	while (*p != 0)
	{
		if ( is_op(*p) ) // 연산자는 스택에 넣기
			push(&st, *p); 
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
	printf("%s\n", output); // 342-+
}
