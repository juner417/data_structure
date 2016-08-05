#include <stdio.h>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <set> // tree

using namespace std;

int main()
{
	stack<int> s; // c++ stack
	s.push(10);
	s.push(20);
	s.push(30);

	printf("%d\n", s.top());
	s.pop();
	printf("%d\n", s.top());
	
	
}
