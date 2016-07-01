#include <stdio.h>

void printArray(int* x, int sz)
{
	for (int i = 0; i<sz; i++)
		printf("%d ", x[i]);
	printf("\n");
}
// 2개의 정수를 바꾸는 함수
void Swap(int* p1, int* p2)
{
	int temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

// 매번 swap 하지 말고.. 제일 작은 것의 index를 찾아서 찾아서 0번째와 swap
void selection_sort(int* x, int sz)
{
	int i = 0;
	int j = 0;
	int min = 0;

	for (j = 0; j<sz-1; j++)
	{
		min = j;
		for (i = j + 1; i<sz; i++)
		{
			if( x[min] > x[i]) 
				//Swap(&x[j], &x[i]);
				min = i;
		}
		// 제일 작은 요소와 0번째(j번쩨)를 교환한다. 
		Swap(&x[j], &x[min]);	
		printArray(x, 10);
	}
}


int main()
{
	int x[10] = {10,8,6,4,2,1,3,5,7,9};

	//printArray(x,10);
	selection_sort(x, 10);
}
