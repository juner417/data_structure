//3_list
#include <stdio.h>
#include <stdlib.h>
// 1. 링크드 리스트이 기본은 무조건 노드가 필요하다. Node
struct _Node
{
	int data;
	struct _Node* next;
};
typedef struct _Node NODE;

// 2. 첫번째 NODE를 저정할 변수가 필요하다. 
// 처음의 변수 주소를 저장해야 하니까 
NODE* head = 0;

/*
void insert_front(int n)
{
	//그림을 그려가며 생각 해보시오!!
	//DATA 를 보관하기 위해 노드를 만들고 초기화 한다. 
	NODE* temp = (NODE*)malloc(sizeof(NODE));
	temp->data = n;
	temp->next = 0;
	// linkedlist는 두개의 경우로 나누면 된다. 
	// 1. list가 비어있을 떄	
	if( head == 0)
		temp->next = head; // 어차피 첫 노드는 next에 0가 들어가도 됨
		head = temp;
	else {
	// 2. 몇개가 들어가 있을 때	
 	// 변해야 하는 next가 어디인지 체크하고 
	// 누구부터 변경해야 하는지 기록 - 순서가 아주 중요!!
		temp->next = head;
		head = temp; // insert_front 앞으로 계속 들어가야 하기 떄문에
	}	
	// 3. 비어있을 떄와 몇개쯤 있을 떄의 코드를 하나로 함치면 안될까?
	// if문 안에가 동일하게 동작 
}
*/

void insert_front(int n)
{
    NODE* temp = (NODE*)malloc(sizeof(NODE));
    temp->data = n;
	temp->next = head;
	head = temp;
}

int main()
{
	insert_front(1);
	insert_front(2);
	insert_front(3);
	insert_front(4);
	insert_front(5);
}
