#include <stdio.h>
#include <stdlib.h>

// List5 : 더미 노드의 도입..

// 더미 노드 도입에 따라
// insert_back(), insert_front(), display() 코드가 변경됨.


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

	// 더미 노드를 head에 연결
	head = temp;
}




void insert_front(int n)
{
	NODE* temp = (NODE*)malloc(sizeof(NODE));
	temp->data = n;

	// 더미 노드 때문에 head가 아닌 head->next에 처음노드의 주소가 있다.
	temp->next = head->next;
	head->next = temp;
}


void display()
{
	NODE* cur = 0;
	system("cls");
	printf("[head]");

	//cur = head; // 더미 노드가 없을때

	cur = head->next; // 더미 노드가 있을때.

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

	// 더미노드 때문에 list가 비어 있을때와 몇개 있을때 같은 코드 사용가능
	NODE* cur = head;

	while (cur->next != 0)
		cur = cur->next;

	cur->next = temp;
}





int main()
{
	init_list();

	insert_back(1);
	insert_back(2);
	insert_back(3);
	insert_back(4);
	insert_back(5);
	insert_front(6);
	insert_front(7);
	insert_front(8);
	display();   // 8 7 6 1 2 3 4 5
}
