// stact_calc
#include <stdio.h>
#include "Stack.h"

char output[32] = { 0 };
int idx = 0;

int is_op(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

int priority(char c)
{
	if (c == '+' || c == '-' ) return 1;
	if (c == '*' || c == '/' ) return 2;

	return 0;
}

int main()
{
	char s[32] = {0};
	printf("수식을 입력하시오 >> ");
	scanf("%s", s); // 공백입력안됨.
					// 숫자는 한자리만 입력

	Stack st;
	init(&st);

	char* p = s; 

	while (*p != 0)
	{
		if ( *p == '(' )
			push(&st, *p);
		else if ( *p == ')' )
		{
			while( !isempty(&st))
			{
				char c = pop(&st);
				if ( c=='(' ) break; 
				output[idx++] = c;
			}
		}
		else if ( is_op(*p) ) 
		{	
			while ( !isempty(&st) )
			{	
				if (priority(top(&st)) <= priority(*p)) break;	
			
				output[idx++] = pop(&st);	
			}
			push(&st, *p);
		} 
		else
			output[idx++] = *p; 
		++p;
	}

	while (!isempty(&st))
	{
		char c = pop(&st);
		output[idx++] = c;
	}
	printf("%s\n", output);

	char* p2 = output;
	while (*p2 !=0)
	{
		if(!is_op(*p2)) // 숫자라면
 		{
			push(&st, *p2 - '0');// 문자 '2'를 숫자 2로 넣기 	
		}
		else // 연산자 일때
		{
			int n1 = pop(&st);
			int n2 = pop(&st);

			int ret = 0;
			switch (*p2)
			{
				case '+': ret = n2 + n1; break;
				case '-': ret = n2 - n1; break;
				case '*': ret = n2 * n1; break;
				case '/': ret = n2 / n1; break;
			}
			push(&st, ret); // 연산의 결과를 다시 스택에 
		}
		++p2;
	} 
	// 스텍에 최종 결과만 남아 있게 된다. 
	int result = pop(&st);
	printf("result : %d\n", result);
}
