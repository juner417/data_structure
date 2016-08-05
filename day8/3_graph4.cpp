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

// 특정 vertex의 주변에 방문 안한 vertex를 리턴하는 함수
Vertex* findNextVertex(Vertex* v)
{
	for ( int i = 0; i < v->vec.size(); i++)
	{
		Vertex* p = v->vec[i];
	
		if (p->visited == 0)
			return p;
	}
	return 0; // 주변에 방문 안한 vertex가 없는 경우 0리턴.
			
}

// 깊이 우선 탐색(depth first search)
stack<Vertex*> st;

void DFS(Vertex* v)
{
	printf("방문 %d\n", v->data);
	v->visited = 1; //방문했음
	
	st.push(v); //스택에 넣기
	while (!st.empty())
	{
		// 스택 꼭데이 vertex의 방문가능한 근접 요소를 찾는다.
		Vertex* p = findNextVertex(st.top());
		
		if (p == 0)
		{
			st.pop();
		}
		else
		{
			printf("방문 %d\n", p->data);
			p->visited = 1;
			st.push(p);
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

//	Vertex* vt = findNextVertex(v[0]);
//	printf("%d\n", vt->data);

	DFS(v[0]);
}
