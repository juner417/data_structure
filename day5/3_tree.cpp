//3_tree
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// 키값과 왼쪽 /오른쪽 자식 node포인터만 있으면 된다. 

struct _Node
{
	int key;
	struct _Node* left;
	struct _Node* right;
};
typedef struct _Node NODE;

// NODE 구조체를 메모리 할당하고 초기화 해주는 함수
NODE* make_node(int key)
{
	NODE* node = (NODE*)malloc(sizeof(NODE));
	node->key = key;
	node->left = 0;
	node->right = 0;
	return node;
}

int main()
{

}
