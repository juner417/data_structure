#include <stdio.h>
#include <stdlib.h>

void printArray(int* x, int sz)
{
	for (int i = 0; i<sz; i++)
		printf("%d ", x[i]);
	printf("\n");
}
// qsort()를 위한 비교 함수 모양
int cmp1(const void* p1, const void* p2)
{
	// void* 로 받은 것을 요소 타입으로 ㄱ캐스팅해서 비교 하세요
	int* a = (int*)p1;
	int* b = (int*)p2;
	return *a < *b;
}
	
int main()
{
	int x[10] = {5,3,4,10,7,6,1,8,2,9};

	// c 언어에 이미 quick_sort()함수가 있습니다 
	// 1. 모든타입의 배열을 위해 void*로 되어 있습니다. 
	// 2. 비교 정책을 담은 함수를 보내야 합니다. 
	// 3. 비교 정책 함수는 void*를 인자로 해야 합니다. 

	qsort(x, 10, sizeof(int), cmp1);	
	printArray(x,10);
}
