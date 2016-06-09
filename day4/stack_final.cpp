//stack_final
#include <stdio.h>
#include <stdlib.h>

struct _Node
{
	int data;
	struct _Node* next;
};
typedef struct _Node NODE;

NODE* head = 0;
// 결국 list 앞에 넣는 코드
void push(int n)
{
    NODE* temp = (NODE*)malloc(sizeof(NODE));
    temp->data = n;
	temp->next = head;
	head = temp;
}

// list에 앞에서 값을 꺼내고 제거하는 함수
int pop()
{
	if (head == 0)
		return -1; // list가 비어 있을 때
	// 앞 노드의 주소를 잠시 보관 
	NODE* temp = head;
	head = head->next;
	
	int ret = temp->data;	
	free(temp); // node제거
	return ret;
}

int main()
{
    push(10);
    push(20);
    push(30);
}
