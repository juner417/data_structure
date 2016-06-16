//3_tree
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

struct _Node
{
	int key;
	struct _Node* left;
	struct _Node* right;
};
typedef struct _Node NODE;

NODE* make_node(int key)
{
	NODE* node = (NODE*)malloc(sizeof(NODE));
	node->key = key;
	node->left = 0;
	node->right = 0;
	return node;
}

// step5. 재귀호출을 사용한 insert()함수 만들기 
// tree의 제일 위 노드는 root가 가르키지만
// 첫번째 노드의 왼쪽에 있는 tree들의 최상위 노드는 root->left가 가르킨다. 
// 재귀를 사용하면 쉬워진다. 


void insert(NODE** root, int key)
{
	if (*root == 0)
		*root = make_node(key);
	else
	{
		if ( (*root)->key > key )
			insert(&((*root)->left), key);	// 왼쪽에 넣어야 한다. 
		else
			insert(&((*root)->right), key);
	}
}
// inoder방식의 순회... : 정렬된 상태를 확인할 수 있다. 
// 1. 왼쪽 자식 먼저 출력
// 2. 부모 출력
// 3. 오른쪽 자식 출력 
void inorder(NODE* r)
{
	if (r!=0)
	{
		inorder(r->left);
		printf("%d => ", r->key);
		inorder(r->right);
	}
}
// post order 방식 : tree 의 node를 메모리 해지할때 사용하는 방식 
// 1. 왼쪽이 있으면 이동
// 2. 오른쪽이 있으면 이동
// 3. 출력. 
void postorder(NODE* r)
{
	if (r!=0)
	{
		postorder(r->left);
		postorder(r->right);
		printf("free memory  %d => ", r->key);

	}
}

// preorder
// 1. 출력하고
// 2. 왼쪽으로 이동
// 3. 오른쪽으로 이동
void preorder(NODE* r)
{
	if (r!=0)
	{
		printf("%d => ", r->key);
		preorder(r->left);
		preorder(r->right);

	}
}

int main()
{
	NODE* root = 0;

	insert(&root,5);
	insert(&root,3);
	insert(&root,7);
	insert(&root,2);
	insert(&root,4);
	insert(&root,6);
	insert(&root,8);
	insert(&root,8);
	insert(&root,1);
	insert(&root,9);
	
	inorder(root); // tree 내용 출력
	printf("\n");
	postorder(root); // tree 내용 출력
	printf("\n");
	preorder(root); // tree 내용 출력

	// 8이 있는 횟수를 리턴하세요, 
	// 재귀 호출을 이용하여 만들으세요
	int ret = search(root, 8);
	
	if (ret == 0)
		printf("8이 없습니다. \n");
	else
		printf("8dl %d번 있습니다. \n", ret);
}
