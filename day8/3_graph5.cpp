#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <stack>
#include <queue>

using namespace std;
struct Vertex 
{
	int data;
	int visited; // 방문했는가. 
	vector<Vertex*> vec;
};


void addEdge(Vertex* v1, Vertex* v2)
{
	v1->vec.push_back(v2);
	v2->vec.push_back(v1);
}

void adjacentVertex(Vertex* v)
{
	printf("%d vertex에 근접 vertex\n", v->data);
	for (int i = 0; i < v->vec.size(); i++)
	{
		Vertex* p = v->vec[i];
		printf("Vertex %d\n", p->data);
	}
}

// 넓이 우선 탐색 (bread

queue<Vertex*> q;
//특정 vertex의 주변 vertex를 큐에 넣는 함수
void addVertexToQ(Vertex*)
{
}

void BFS(Vertex* v)
{
	// 무조건 Q에 넣는다. 
	q.push(v);
	
	while (!q.empty())
	{
		Vertex* p = q.front(); // Q에 처음 요소를 꺼내서
		q.pop();
	
		if (p->visited == 0)
		{
			printf("방문 %d\n", p->data);
			p->visited = 1;
			//근접한 모든 방문 안한 vertex를 큐에 넣는다. 
			addVertexToQ(p);
		}
	}

}

int main()
{
	
	vector<Vertex*> v(5);

	for ( int i = 0; i < v.size(); i++)
	{
		v[i] = new Vertex; 
		v[i]->data = i;
		v[i]->visited = 0;
	}
	addEdge(v[0], v[1]);
	addEdge(v[0], v[2]);
	addEdge(v[1], v[2]);
	addEdge(v[1], v[4]);
	addEdge(v[2], v[3]);
	addEdge(v[2], v[4]);
	addEdge(v[3], v[4]);
	
	BFS(v[0]);
}
