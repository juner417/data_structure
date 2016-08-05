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

// 아래 함수는 이미만들어진 NODE를 조작해서 list앞 뒤에만
// 넣게 됩니다. 
void insert_front(NODE** head, NODE* node)
{
	node->next = 0;
	node->prev = 0;
	insert_node(node, *head, (*head)->next);	
}

void insert_back(NODE** head, NODE* node)
{
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


int main() 
{
	NODE* head = 0;
	init_list(&head);

	// 이제 list에 넣으려면 int가 아닌 NODE를 만들어 보내야함
	for (int i = 0; i < 10; i++)
	{
		NODE* node = (NODE*)malloc(sizeof(NODE));
		node->data = i;
		insert_back(&head, node);
	}
	display(&head); 
}
