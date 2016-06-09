//stack_final
#include <stdio.h>
#include <stdlib.h>

struct _Node
{
	int data;
	struct _Node* next;
};
typedef struct _Node NODE;

// 2개 이상의 스택을 사용하게 하려면 전역변수 head를 함수 인자화
// 해야 한다. 
//NODE* head = 0;
typedef NODE* Stack;

void push(Stack* head, int n)
{
    NODE* temp = (NODE*)malloc(sizeof(NODE));
    temp->data = n;
	temp->next = *head;
	*head = temp;
}

int pop(Stack* head)
{
	if (*head == 0)
		return -1; 

	NODE* temp = *head;
	*head = (*head)->next;
	
	int ret = temp->data;	
	free(temp); 
	return ret;
}

int isempty(Stack s)// NODE*
{
	return s == 0;
}

int top(Stack s)
{
	return s->data;
}
// 스택초기화
void init_stack(Stack* s)
{
	*s = 0; // *head = 0;
}

int main()
{
	Stack h1 = 0;
	Stack h2 //= 0;
	init_stack(&h2);

    push(&h1, 10);
    push(&h1, 20);
    push(&h2, 30);
    push(&h2, 40);
	printf("%d\n", pop(&h2));
	printf("%d\n", pop(&h2));
	printf("%d\n", pop(&h1));
	printf("%d\n", pop(&h1));
}
