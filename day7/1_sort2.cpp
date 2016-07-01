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

// selection sort(선택 정렬): 제일 작은 것(큰ㅅ것)을 하나씩 찾아내서 정렬
/*
void selection_sort(int* x, int sz)
{
	int i = 0;
	for (i = 1; i<sz; i++)
	{
		if( x[0] > x[i]) // x[0] 보다 작은 요소라면 2개를 변경한다.
			Swap(&x[0], &x[i]);
	}	
	printArray(x, 10);
}
*/
// 0 번ㄷ째 뿐 아니라 1, 2, 3...모두 적용한다. 
void selection_sort(int* x, int sz)
{
	int i = 0;
	int j = 0;

	for (j = 0; j<sz-1; j++)
	{
		for (i = j + 1; i<sz; i++)
		{
			if( x[j] > x[i]) // x[0] 보다 작은 요소라면 2개를 변경한다.
				Swap(&x[j], &x[i]);
		}	
		printArray(x, 10);
	}
}


int main()
{
	int x[10] = {10,8,6,4,2,1,3,5,7,9};

	//printArray(x,10);
	selection_sort(x, 10);
}
