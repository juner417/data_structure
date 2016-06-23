// hash_table 3. insert()를 완성한 코드 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define HASH_TABLE_SIZE 16

int hashing(int key)
{
	return key % HASH_TABLE_SIZE;
}

struct _Node
{
    int data;
    struct _Node* next;
};
typedef struct _Node NODE;

void push_front(NODE** head, int n)
{
    NODE* temp = (NODE*)malloc(sizeof(NODE));
    temp->data = n;
    temp->next = *head;
    *head = temp;
}

NODE* hash_table[HASH_TABLE_SIZE] = { 0 };

void insert(int data)
{
	int idx = hashing(data);
	
	push_front(&hash_table[idx], data);	
}
/*
void display()
{
	NODE* cur = hash_table[0];
	for (; cur != 0; cur = cur->next)
	{
		printf(" => %d ", cur->data);
	}
}*/
void display()
{
	system("clear");
	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
    	NODE* cur = hash_table[i];
		printf("[ %d ] ", i);

    	for (; cur != 0; cur = cur->next)
    	{
    		printf(" => %d ", cur->data);
    	}
		printf("\n");
	}
}

int main()
{
	srand(time(0)); // random init
	
	for ( int i = 0; i < 100; i++)
		insert(rand()%100);
	display();
		
}

