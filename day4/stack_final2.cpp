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

void push(NODE** head, int n)
{
    NODE* temp = (NODE*)malloc(sizeof(NODE));
    temp->data = n;
	temp->next = *head;
	*head = temp;
}

int pop(NODE** head)
{
	if (*head == 0)
		return -1; 

	NODE* temp = *head;
	*head = (*head)->next;
	
	int ret = temp->data;	
	free(temp); 
	return ret;
}

int main()
{
	NODE* h1 = 0;
	NODE* h2 = 0;

    push(&h1, 10);
    push(&h1, 20);
    push(&h2, 30);
    push(&h2, 40);
	printf("%d\n", pop(&h2));
	printf("%d\n", pop(&h2));
	printf("%d\n", pop(&h1));
	printf("%d\n", pop(&h1));
}
