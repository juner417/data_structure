//Stack2.h
#include <stdio.h>
#include <stdlib.h>

struct _Node
{
	int data;
	struct _Node* next;
};
typedef struct _Node NODE;

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

int isempty(Stack s)
{
	return s == 0;
}

int top(Stack s)
{
	return s->data;
}

void init_stack(Stack* s)
{
	*s = 0; // *head = 0;
}

