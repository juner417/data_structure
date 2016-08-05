#include <stdio.h>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <set> // tree

using namespace std;

int main()
{
	list<int> s;
	
	s.push_back(10);
	s.push_back(20);
	s.push_back(30);

	auto p = s.begin(); // p는 처음 요소를 가르키는 포인터와 유사합니다. 

	while (p!=s.end())
	{
		printf("%d\n", *p);
		++p;// linked list 이지만 ++로 이동하면 됩니다. 
	}
	
}
