#include <stdio.h>
#include <stdlib.h>
// define node
struct _Node
{
	int data;
	struct _Node* next;
};
typedef struct _Node NODE;

NODE* head = 0;

void insert_front(int n)
{
	NODE* temp = (NODE*)malloc(sizeof(NODE));
	temp->data = n;
	temp->next = head;
	head = temp;
}

void display()
{
	NODE* cur = 0;
	system("clear");
	printf("[head]");

	cur = head;
	while(cur != 0)
	{
		printf("-> %d ", cur->data);
		cur = cur->next;
	}
}

void insert_back(int n)
{
	// 1. 노드 생성 후 초기화 
	NODE* temp = (NODE*)malloc(sizeof(NODE));
	temp->data = n;
	temp->next = 0;

	// 2. empty list
	if ( head == 0 )
	{
		head = temp;
		return ;
	}

	//
	NODE* cur = head;
	while (cur->next !=0)
		cur = cur->next;
	cur->next = temp;
}

int main()
{
	insert_back(1);
	insert_back(2);
	insert_back(3);
	insert_back(4);

	display();
}
