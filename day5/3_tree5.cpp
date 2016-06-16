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
	insert(&root,1);
	insert(&root,9);
}
