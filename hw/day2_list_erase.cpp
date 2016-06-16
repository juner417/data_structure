#include <stdio.h>
#include <stdlib.h>
#include "memchk.h"
// List6 : erase_front()만들기

// 과제 2. erase_back()을 만들어 보세요..


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
	system("clear");
	printf("[head]");

	cur = head->next;

	while (cur != 0)
	{
		printf("-> %d ", cur->data);
		cur = cur->next;
	}
	//printf("\n");
}


void insert_back(int n)
{
	NODE* temp = (NODE*)malloc(sizeof(NODE));
	temp->data = n;
	temp->next = 0;

	// 더미노드 때문에 list가 비어 있을때와 몇개 있을때 같은 코드 사용가능
	NODE* cur = head;

	while (cur->next != 0)
		cur = cur->next;

	cur->next = temp;
}


void erase_front()
{
	// 1. 비어 있을때
	if (head->next == 0)
		return;

	// 2. 비어있지 않을때
	NODE* temp = head->next; // 처음 노드 주소를 꺼내 놓는다.
	head->next = temp->next;
	free(temp);
}

void erase_back()
{
	//1. empty
	if (head->next == 0)
		return;

	// 2. not empty(few nodes)
    NODE* cur = head->next;
    NODE* front = 0;

	while(cur->next != 0) // 만약 환형 이면 (cur->next != head)
    {
		front = cur;
		cur = cur->next;
    }
	//마지막 전노드도 알아야함...
	//왜냐면 마지막 전노드의 next를 0나 head로 변경해야 함...
    front->next = 0;// 환형이면 front->next = head
 
    free(cur); //마지막 노드 제거
}

int main()
{
	init_list();
	insert_back(1);
	insert_back(2);
	insert_back(3);
	insert_back(4);
	display();   

	erase_front();
    erase_back();

	display();   // 2 3
    return 0;
}
