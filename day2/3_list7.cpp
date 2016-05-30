#include <stdio.h>
#include <stdlib.h>


struct _Node
{
	int data;
	struct _Node* next;
};
typedef struct _Node NODE;

NODE* head = 0;


void init_list()
{
	NODE* temp = (NODE*)malloc(sizeof(NODE));

	temp->data = 0;
	temp->next = 0;

	head = temp;
}


void insert_front(int n)
{
	NODE* temp = (NODE*)malloc(sizeof(NODE));
	temp->data = n;

	temp->next = head->next;
	head->next = temp;
}


void display()
{
	NODE* cur = 0;
	system("cls");
	printf("[head]");

	cur = head->next;

	while (cur != 0)
	{
		printf("-> %d ", cur->data);
		cur = cur->next;
	}
}


void insert_back(int n)
{
	NODE* temp = (NODE*)malloc(sizeof(NODE));
	temp->data = n;
	temp->next = 0;

	NODE* cur = head;

	while (cur->next != 0)
		cur = cur->next;

	cur->next = temp;
}


void erase_front()
{
	if (head->next == 0)
		return;

	NODE* temp = head->next;
	head->next = temp->next;
	free(temp);
}
/*
// 한개 출력
void reverse_display(NODE* node)
{
	printf("-> %d ", node->data);
}
*/
/*
// 재귀 호출을 사용한 정방향 출력
void reverse_display(NODE* node)
{
	printf("-> %d ", node->data);

	if ( node->next != 0)
		reverse_display(node->next);
}
*/
// 역방향 출력

// 재귀 호출 => 재귀 호출  => 재귀 호출 => 재귀 호출 => node->next==0이면 재귀호출안함
// 1 출력       2출력        3출력        4출력        5출력
void reverse_display(NODE* node)
{
	if (node->next != 0)
		reverse_display(node->next);

	printf("-> %d ", node->data);
}


int main()
{
	init_list();
	insert_back(1);
	insert_back(2);
	insert_back(3);
	insert_back(4);
	insert_back(5);
	//display();   // 1 2 3 4 5

	reverse_display(head->next); // 5 4 3 2 1
}
