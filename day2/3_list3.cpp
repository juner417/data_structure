//3_list3
#include <stdio.h>
#include <stdlib.h>
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
	system("cls"); // clear
	printf("[head]");
	
	cur = head;
	
	while ( cur != 0 )
	{
		printf("-> %d ", cur->data);
		cur = cur->next;

	}
}

void insert_back(int n)
{
	//1. 노드 생성 후 초기화	
	NODE* temp = (NODE*)malloc(sizeof(NODE));
	temp->data = n;
	temp->next = 0;	
	//2. list가 비어 있을 떄 
	if (head == 0)
	{
		head = temp;
		return;
	} 
	//3. list에 몇개 쯤 있을 떄 뒤에 넣는 코드
	// 뒤에다가 노드를 추가해야 하는 것이므로 마지막 노드의 주소저장소를 찾아 가야함 
	// cur 변수를 이용하여 끝을  찾음
	NODE* cur = head;
	
	//주의 아래처럼 하면 마지막 cur에 노ㅇ드의 주소가 아닌 0이 들어온다. 
	/*
	while (cur != 0)
		cur = cur->next;
	*/
	while (cur->next != 0)
		cur = cur->next;
	cur->next = temp;
	 
	//4. 2, 3을 합치면 안될까?
}
int main()
{
	insert_back(1);
	insert_back(2);
	insert_back(3);
	insert_back(4);
	insert_back(5);

	display();
}
