#include <stdio.h>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <set> // tree

using namespace std;

int main()
{
	vector<int> v(10);	//ㅡ크기가 10개인 동적배열
	v[0] = 1;
	v[1] = 10; // 사용법은 배열과 동일합니다. 

	v.resize(20); // 20개로 늘어납니다. 
	v.push_back(1); // 끝에 하나 추가
	
	printf("%d\n", v.size());
}
