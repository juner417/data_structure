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

// step4. root를 전역변수 대신 함수 인자로 만든 버전
// 2개 이상의 tree를 사용할 수 있게 되었다. 
//NODE* root = 0;

void insert(NODE** root, int key)
{
	if (*root == 0)
	{
		*root = make_node(key);
		return;
	}

	NODE* cur = *root; 

	while(1)
	{
    	if ( cur->key > key )
    	{
    		if ( cur->left == 0 )
    		{
    			cur->left = make_node(key);
    			return ;
    		} 
    		else
    		{	
    			cur = cur->left;
    		}
    	}
		else 
		{
    		if ( cur->right == 0 )
    		{
    			cur->right = make_node(key);
    			return ;
    		} 
    		else 
    		{	
    			cur = cur->right;
    		}
			
		}	
	}		
}

int main()
{
	NODE* root = 0;

	insert(&root, 5);
	insert(&root,3);
	insert(&root,7);
	insert(&root,2);
	insert(&root,4);
	insert(&root,6);
	insert(&root,8);
	insert(&root,1);
	insert(&root,9);
}
