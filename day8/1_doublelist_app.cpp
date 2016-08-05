#include <stdio.h>
#include <stdlib.h>

struct _Node
{
	int data;
	struct _Node* prev;
	struct _Node* next;
};
typedef struct _Node NODE;

//NODE* head = 0;

void init_list( NODE** head)
{
	*head = (NODE*)malloc(sizeof(NODE));
	(*head)->data = 0;
	(*head)->next = *head;
    (*head)->prev = *head;
}

void insert_node(NODE* node, NODE* prev, NODE* next)
{
	// 새로운 노드 변경	
	node->prev = prev;
    node->next = next;

	// 기존노드 변경
	prev->next = node;
	next->prev = node;
}

void insert_front(NODE** head, int n)
{
	// 1. 노드 생성
	NODE* node = (NODE*)malloc(sizeof(NODE));
	
	// 2. 노드 초기화	
	node->data = n;
	node->next = 0;
	node->prev = 0;

	insert_node(node, *head, (*head)->next);	
}

void insert_back(NODE** head, int n)
{
	// 1. 노드 생성
	NODE* node = (NODE*)malloc(sizeof(NODE));
	
	// 2. 노드 초기화	
	node->data = n;
	node->next = 0;
	node->prev = 0;

	insert_node(node, (*head)->prev, *head);	
}

void display(NODE** head) 
{
	printf("[head]");
	NODE* cur = 0;
	for(cur = (*head)->next; cur != (*head); cur=cur->next)
	{
		printf("-> %d", cur->data);
	}
}

void reverse_display_recur(NODE* node) 
{
	if (node->next != head)
		reverse_display_recur(node->next);
    printf("-> %d ", node->data);
}
void reverse_display()
{
    printf("[tail]");
    NODE* cur = 0;
	for(cur = head->prev; cur != head; cur=cur->prev)
	{
		printf("-> %d", cur->data);
	}
	
}

int main() 
{
	NODE* head = 0;
	init_list(&head);
	insert_front(&head,1);
	insert_front(&head,2);
	insert_front(&head,3);
	insert_back(&head,4);
	insert_back(&head,5);
	insert_back(&head,6);
	display(&head,); 
}
