#include <stdio.h>
// 정렬(sort) : 연속된 자료를 정해진 기준의 순서로 배치하는 것.

void printArray(int* x, int sz)
{
	for (int i = 0; i<sz; i++)
		printf("%d ", x[i]);
	printf("\n");
}

void Swap(int* p1, int* p2)
{
	int temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

int main()
{
	int x[10] = {10,8,6,4,2,1,3,5,7,9};

	printArray(x,10);
}
