//3_list2
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

int main()
{
	insert_front(1);
	insert_front(2);
	insert_front(3);
	insert_front(4);
	insert_front(5);

	display();
}
