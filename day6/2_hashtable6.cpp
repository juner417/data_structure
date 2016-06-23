// hash_table 6. search()를 완성한 코드 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define HASH_TABLE_SIZE 32

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

void search(int data)
{
	int idx = hashing(data);
	// list순회로 검색 
	int cnt = 0;
	NODE* cur = hash_table[idx];
	
	while (cur != 0)
	{
		if (cur->data == data)
		{
			printf("%d 버킷의 %d 번쨰에 있음 \n", idx, cnt);
			break;
		}
		++cnt;
		cur = cur->next;
	}
	if (cur == 0)
		printf("찾을수 없습니다\n");
}

int main()
{
	srand(time(0)); // random init
	
	for ( int i = 0; i < 100; i++)
		insert(rand()%100);
	display();

	while(1)
	{
		int n ; 
		printf("찾을 값은 >> ");
		scanf("%d", &n);
		
		search(n);
	}
		
}

