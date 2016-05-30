// 2_리스트 개념2
#include <stdio.h>
#include <stdlib.h>

// node : 이전 메모리의 주소와 값을 함께 가지고 있는 것
struct _Node
{
	int data;
	struct _Node* next;
};
// node를 typedef로 지정함
typedef struct _Node Node;

int main() 
{
	int n = 0;
	//int* head = 0;
	Node* head = 0;
	// 사용자가 -1을 입력 할 때 까지 계속 입력하고 싶다. 

	while (1) 
	{
		scanf("%d", &n);
		if (n==-1) break;

		//head = (int*)malloc(sizeof(int));
		Node* temp = (Node*)malloc(sizeof(Node));
		//*head = n;
		temp->data = n;
		temp->next = 0;

		// list에 넣는 코드를 만드는 방법
		// 1. 처음 노드일때 
		if(head == 0)
			head = temp;
		else
		{
			//2. list에 몇개 있을 때	
			// nextㅣ필드에 0이 들어 있을 떄 까지 이동	
			Node* cur = head;
			
			while (cur->next != 0)
				cur = cur->next;
			cur->next = temp;
		}
	}
}
