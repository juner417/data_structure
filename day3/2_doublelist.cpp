#include <stdio.h>
#include <stdlib.h>

// 1. double list Node 모양
struct _Node
{
	int data;
	struct _Node* prev;
	struct _Node* next;
};
typedef struct _Node NODE;

NODE* head = 0;

// create a dummy node
// dummy node가 prev,next를 자기자신의 주소로 하면 환형list가 된다. 
void init_list()
{
	head = (NODE*)malloc(sizeof(NODE));
	head->data = 0;

	// dummy node prev, next는 자신의 주소로 (환형 list)
	head->next = head;
    head->prev = head;
}

// 핵심 함수 : 이미 존재하는 2개의 노드 사이에 새로운 노드 넣기
// 			NODE는 이미 만들어져서 전달된다고 가정
// 1. 그림을 그리세요/
// 2. 변해야 하는 곳을 찾으세요
// 3. 변해야 하는 순서를 적으세요
//    핵심 : 새로운 NODE를 먼저 변경하세요
// 기존의 존재하는 2개의 노드 prev, next사이에 새로운 NODE인 node를 넣는 함수
// 메모리는 할당하지 않고 할당된 노드의 next, prev만 변경.
void insert_node(NODE* node, NODE* prev, NODE* next)
{
	// 새로운 노드 변경	
	node->prev = prev;
    node->next = next;

	// 기존노드 변경
	prev->next = node;
	next->prev = node;
}

// 더블리스트 앞에 넣는 코드
void insert_front(int n)
{
	// 1. 노드 생성
	NODE* node = (NODE*)malloc(sizeof(NODE));
	
	// 2. 노드 초기화	
	node->data = n;
	node->next = 0;
	node->prev = 0;

	// 3. List앞에 넣기 - 몇개의 노드가 있는 그림을 그리고 생각해 
	//    앞에 넣는 것 : 더미(head)와 첫번째 요소(head->next)사이에 넣는것
	insert_node(node, head, head->next);	
}

void insert_back(int n)
{
	// 1. 노드 생성
	NODE* node = (NODE*)malloc(sizeof(NODE));
	
	// 2. 노드 초기화	
	node->data = n;
	node->next = 0;
	node->prev = 0;

	// 3. List 뒤에 넣기 :누구와 누구 사이?
	// 마지막(head->priv, 더미와 prev)과 더미(head)사이에 넣기 
	insert_node(node, head->prev, head);	
}

void display() 
{
	printf("[head]");
	NODE* cur = 0;
	// 시작이 head->next인 것은 dummy 가 처음이기 때문
	// 그러므로 시작은 더미노드의 next
	// 환형리스트 이므로 끝나도->next는 head(더미주소)가 있다.
	for(cur = head->next; cur != head; cur=cur->next)
	{
		printf("-> %d", cur->data);
	}
}

// 재귀함수를 이용함...
void reverse_display_recur(NODE* node) 
{
	// 과제 망들어 보시오 힌트: cur = cur->prev	
	if (node->next != head)
		reverse_display_recur(node->next);
    printf("-> %d ", node->data);
}
void reverse_display()
{
    printf("[tail]");
    NODE* cur = 0;
	for(cur = head->prev; cur != head; cur=cur->prev)
	{
		printf("-> %d", cur->data);
	}
	
}

int main() 
{
	init_list();
	insert_front(1);
	insert_front(2);
	insert_front(3);
	insert_back(4);
	insert_back(5);
	insert_back(6);
	display(); //3-2-1-4-5-6
    printf("\n");
	reverse_display_recur(head->next);
    printf("\n");
	reverse_display();
}
