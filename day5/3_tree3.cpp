//3_tree
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

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
// step2 tree에 data 넣기
NODE* root = 0;

// step3 insert() 함수 완성
// 분석 할때 왼쪽 자식 에 넣는 코드만 이해하면 됩니다. 
// 오른쪽 자식은 완전히 동일한 알고리즘입니다. 
void insert(int key)
{
	//1. tree가 비어있다면	
	if (root == 0)
	{
		root = make_node(key);
		return;
	}
	// 2. 비어있지 않을때 
	// 임시 변수가 있어야 함
	NODE* cur = root; //비어있을 때 까지 따라 가야 한다. 
                       //임시변수로 작업
						//root 는 절대 변경되면 안된다. 
	while(1)
	{
    	if ( cur->key > key ) //기존보다 작은 값이 오면 왼쪽 자식으로	
    	{
    		if ( cur->left == 0 )
    		{
    			cur->left = make_node(key);
    			return ;
    		} 
    		else // left 자식이 있었다면  
    		{	
    			cur = cur->left;
    		}
    	}
		else // 오른쪽 자식으로 ...
		{
    		if ( cur->right == 0 )
    		{
    			cur->right = make_node(key);
    			return ;
    		} 
    		else // left 자식이 있었다면  
    		{	
    			cur = cur->right;
    		}
			
		}	
	}		
}

int main()
{
	insert(5);
	insert(3);
	insert(7);
	insert(2);
	insert(4);
	insert(6);
	insert(8);
	insert(1);
	insert(9);
}
