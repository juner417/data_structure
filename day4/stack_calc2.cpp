// 4_calc
#include <stdio.h>
#include "Stack.h"

char output[20] = { 0 };
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

char s[] = "2+3*4+2"; 
// 연산자를 만날 때 계산함.
int main()
{
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

	// postfix표현식을 계산하는 알고리즘
		// 1. 숫자륾 만나면 스택에 넣기  
		// 2. 연산자를 만나면 스택에서 두개를 꺼내서 연산후 결과를 다시 스택에 넣기
 		// 3. 최종결과는스택에 남아 있게 된다. 
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
                case '/': ret = n2 / n1; break
			}
			push(&st, ret); // 연산의 결과를 다시 스택에 
		}
		++p2;
	} 
	// 스텍에 최종 결과만 남아 있게 된다. 
	int result = pop(&st);
	printf("result : %d\n", result);
}
