// hash_table 3. insert()를 완성한 코드 
#include <stdio.h>
#include <stdlib.h>

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
//----------------------------------------
// hash table 에 data를 넣는 함수 
void insert(int data)
{
	// hash함수를 통해서 저장할 버킷(bucket)의 index를 구한다. 
	int idx = hashing(data);
	
	// 해당 버킷의 list에 추가한다. 
	push_front(&hash_table[idx], data);	
}
int main()
{
	insert(10);
	insert(20);
	insert(100);
	insert(333);
	insert(444);

}
