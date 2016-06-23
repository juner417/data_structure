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

// single list의 앞쪽에 넣는 코드 
void push_front(NODE** head, int n)
{
    NODE* temp = (NODE*)malloc(sizeof(NODE));
    temp->data = n;
    temp->next = *head;
    *head = temp;
}
// 아래 배열의 메모리 모양을 잘 생각해 두세요...
NODE* hash_table[HASH_TABLE_SIZE] = { 0 };

int main()
{

}
