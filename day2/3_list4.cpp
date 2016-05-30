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
	NODE* temp = (NODE*)malloc(sizeof(NODE));
	temp->data = n;
	temp->next = 0;

	if (head == 0)
	{
		head = temp;
		return;
	} 

	NODE* cur = head;
	
	while (cur->next != 0)
		cur = cur->next;
	cur->next = temp;
	// 4. 2,3을 합치면 안될 까?

	//합칠수 없다. 
	// 비어있을떄 head는 0인데
	// cur = head;
	// while( cur->next != 0); // error	 
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
