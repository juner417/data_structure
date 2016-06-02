// 3_stack4
#include <stdio.h>
// v3. 스택의 내부 구조를 표현하려면
//		배열과 index가 필요하다. 
//	구조체로 묶어서 사용하자. 
struct _Stack
{
	int buf[100];
	int index;	
};
typedef struct _Stack Stack;

void push(Stack* s, int a)
{
	s->buf[(s->index)++] = a;
}

int pop(Stack* s)
{
	return s->buf[--(s->index)];
}

void init(Stack* s)
{
	s->index = 0;
}

int main()
{
	Stack s1;
	init(&s1);

	push(&s1, 10);
	push(&s1, 20);
	push(&s1, 30);

	// buf에서 꺼네시오
	printf("%d\n", pop(&s1)); // 30
	printf("%d\n", pop(&s1)); // 20
}
