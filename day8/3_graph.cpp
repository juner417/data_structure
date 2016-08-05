#include <stdio.h>
#include <vector>
#include <stack>
#include <queue>

using namespace std;
// single
struct Node
{
	int data;
	Node* next;
};
// double
struct Node
{
	int data;
	Node* prev;
	Node* next; 
};
// graph node
struct Node
{
	int data;
	vector<Node*> vec;// 근접 노드를 보관할 동적배열(또는 list)
};

int main()
{
	
}
