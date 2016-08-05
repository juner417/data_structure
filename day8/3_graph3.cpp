#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <stack>
#include <queue>

using namespace std;
struct Vertex 
{
	int data;
	vector<Vertex*> vec;
};


void addEdge(Vertex* v1, Vertex* v2)
{
	v1->vec.push_back(v2);
	v2->vec.push_back(v1);
}

//특정 vertex에 근접한 vertex를 출력하는 함수
void adjacentVertex(Vertex* v)
{
	printf("%d vertex에 근접 vertex\n", v->data);
	//v에 근접요소는 배열(vector)에 있다. 
	for (int i = 0; i < v->vec.size(); i++)
	{
		Vertex* p = v->vec[i];
		printf("Vertex %d\n", p->data);
	}
}
int main()
{
	
	vector<Vertex*> v(5);

	for ( int i = 0; i < v.size(); i++)
	{
		//v[i] = (Vertex*)malloc(sizeof(Vertex));
		v[i] = new Vertex; // c++ 사용시 vertor생성자 호출을 위해서 malloc대신 new사용
		v[i]->data = i;
	}
	addEdge(v[0], v[1]);
	addEdge(v[0], v[2]);
	addEdge(v[1], v[2]);
	addEdge(v[1], v[4]);
	addEdge(v[2], v[3]);
	addEdge(v[2], v[4]);
	addEdge(v[3], v[4]);

	adjacentVertex(v[2]);	
}
