#include <stdio.h>
#include <stdlib.h>
#include "memchk.h"   // 카페에서 다운받아 서 현재 폴더에 넣으세요.

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

void reverse_display(NODE* node)
{
	if (node->next != 0)
		reverse_display(node->next);

	printf("-> %d ", node->data);
}

int main()
{
	init_list();

	// 사용자가 -1을 입력할때 까지 입력 받고 싶다.
	int n = 0;

	while (1)
	{
		scanf("%d", &n);
		if (n == -1) break;
		insert_back(n);
	}

	display();

	while( head->next != 0)
		erase_front(); // 메모리 해지.

	free(head); // 더미 노드 삭제..

	return 0; // memchk.h 를 사용하려면 main 함수 제일 아래에
				// return 0 넣으세요
}
