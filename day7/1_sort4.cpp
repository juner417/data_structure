#include <stdio.h>
// selection sort : 한번 루프로 제일 작은 요소의 인덱스를 찾아서 0번째 요소와 교체
// 이 작업을 배열의 크기만큼 반복
// bubble sort : 루프를 돌면서 근접한 2개의 요소를 비교해서 앞이 큰 경우 Swap 
// 한번 루프를 통해서 제일 큰값이 마지막에 오게 된다. 
// 이 작업을 배열의 크기만큼 반복
// 성능 : 100 개를 정렬할때 1*2*3*...*99
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

// bubble sort : 근접한 2개를 계속 비교하여 앞쪽이 큰 경우 2개의 수를 교체한다. 
void bubble_sort(int* x, int sz)
{
	int i = 0;
	int j = 0;

	for (i = sz-1; i>0; i--)
	{
		// 아래 루프를 수행하면 제일 큰 값이 마지막으로 이동된다. 
		for (j = 0; j<i; j++)
		{
			if (x[j] > x[j+1])
			{
				Swap(&x[j], &x[j+1]);
				//printArray(x, sz);
			}
		}
		printArray(x,sz);
	}
}
int main()
{
	int x[10] = {10,8,6,4,2,1,3,5,7,9};

	//printArray(x,10);
	//selection_sort(x, 10);
	bubble_sort(x,10);
}
