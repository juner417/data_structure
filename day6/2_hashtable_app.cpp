// hash_table 활용
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define HASH_TABLE_SIZE 16

// 문자열을 키값으로 해서 bucket index를 구하는 해쉬함수
// 각 문자의 아ㅏ스키 코드를 더한 후 hash table크기로 나머지 연산 
int hashing(const char* key)
{
	int sum = 0 ;
	
	while( *key != 0 )
	{
		sum = sum + *key;
		++key;
	}

	return sum % HASH_TABLE_SIZE;
}

struct _Node
{
	char key[8]; // 7자 까지만 허용 
    int data;
    struct _Node* next;
};
typedef struct _Node NODE;

void push_front(NODE** head, const char* key, int n)
{
    NODE* temp = (NODE*)malloc(sizeof(NODE));
    strcpy(temp->key, key);
	temp->data = n;
    temp->next = *head;
    *head = temp;
}

NODE* hash_table[HASH_TABLE_SIZE] = { 0 };

void insert(const char* key, int data)
{
	int idx = hashing(key);
	
	push_front(&hash_table[idx], key, data);	
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
    		printf(" => %s(%d) ", cur->key, cur->data);
    	}
		printf("\n");
	}
}
/*
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
*/
int main()
{
	insert("MAX", 20);
	insert("XPOS", 100);
	insert("SIZE", 300);
	insert("WIDTH", 30);
	display();
}
