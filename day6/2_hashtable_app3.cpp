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

int search(const char* key)
{
	int idx = hashing(key);
	// list순회로 검색 
	NODE* cur = hash_table[idx];
	
	while (cur != 0)
	{
		if ( strcmp( cur->key, key) == 0)
			return cur->data;

		cur = cur->next;
	}
	if (cur == 0)
		printf("찾을수 없습니다\n");
	return -1;
}

void set()
{
	char name[8] = {0};
	int value = 0;
	
	printf("환경변수 이름 >> ");
	scanf("%s", name);
	
	printf("값 >>");
	scanf("%d", &value);
	
	insert(name, value);
}

void get()
{
    char name[8] = {0};
    int value = 0;

    printf("환경변수 이름 >> ");
    scanf("%s", name);

	value = search(name);
	printf("%s = %d\n", name, value);
}
int main()
{
	while(1)
	{
		char cmd[8] = {0};
		
		printf(">> ");
		scanf("%s", cmd);
		
		if (strcmp(cmd, "set") == 0)
			set();
		else if (strcmp(cmd, "get") == 0)
			get();
		else
			return 1;
	}

}
