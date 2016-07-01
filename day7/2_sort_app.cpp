#include <stdio.h>
#include <stdlib.h>

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
// 비교 정책을 사용자가 변경할 수 있게 하자. 
// 비교 정책함수를 함수 인자로 받는다. 


void quick_sort(int* x, int left, int right, int(*cmp)(int, int))
{
	int i, j;
	int pivot = x[left]; // 첫번째를 pivot으로
	
	if (left < right)
	{
		i = left; // 0
		j = right + 1; // 10
	
		while ( i <= j )	
		{
			// pivot보다 큰 숫자를 찾을 떄 까지 i 이동	
			do 
			{
				++i;
			} while (cmp(x[i], pivot));

			// pivot보다 작은 숫자를 찾을 때 까지 j 이동	
			do 
			{	
				--j;
			} while (cmp(pivot, x[j]));	
			
			// i, j가 교차하지 않은 경우만 두 요소를 swap
			if (i < j)
				Swap(&x[i], &x[j]);
			else
				break;
		}
		Swap(&x[left], &x[j]);

		quick_sort(x, left, j - 1, cmp);
		quick_sort(x, j + 1, right, cmp);
	}
}

// sort로 전ㄴ달할 빅 함수들
int cmp1(int a, int b) {return a < b;}
int cmp2(int a, int b) {return a > b;}
int cmp3(int a, int b) {return abs(a) > abs(b);}


int main()
{
	int x[10] = {5,3,4,10,7,6,1,8,2,9};

	printArray(x,10);
	//quick_sort(x,0,9, cmp1);
	quick_sort(x,0,9, cmp2);
	printArray(x,10);
	
}
