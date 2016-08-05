#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <stack>
#include <queue>

using namespace std;
// graph vertex 
struct Vertex 
{
	int data;
	vector<Vertex*> vec;// 근접 노드를 보관할 동적배열(또는 list)
};

// 그래프의 vertex를 연결하는 함수
void addEdge(Vertex* v1, Vertex* v2)
{
	v1->vec.push_back(v2);// v1의 배열(vector)에 근접요소(v2)의 주소보관
	v2->vec.push_back(v1);
}

int main()
{
	
	vertor<Vertex*> v(5);

	for ( int i = 0; i < v.size(); i++)
	{
		v[i] = (Vertex*)malloc(sizeof(Vertex));
		v[i]->data = i;
	}
	adddEdge(v[0], v[1]);
	adddEdge(v[0], v[2]);
	adddEdge(v[1], v[2]);
	adddEdge(v[1], v[4]);
	adddEdge(v[2], v[3]);
	adddEdge(v[2], v[4]);
	adddEdge(v[3], v[4]);
	
}
