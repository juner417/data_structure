#include <stdio.h>

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

void quick_sort(int* x, int left, int right)
{
	int i, j;
	int pivot = x[left]; // 첫번째를 pivot으로
	
	if (left < right)
	{
		i = left; // 0
		j = right + 1; // 10, 아래 코드에서 --j를 먼저 하게 되므로 +1해놓고 시작 
	
		while ( i <= j )	
		{
			// pivot보다 큰 숫자를 찾을 떄 까지 i 이동	
			do 
			{
				++i;
			} while (x[i] < pivot);

			// pivot보다 작은 숫자를 찾을 때 까지 j 이동	
			do 
			{	
				--j;
			} while (x[j] > pivot);	
			
			// i, j가 교차하지 않은 경우만 두 요소를 swap
			if (i < j)
				Swap(&x[i], &x[j]);
			else
				break;
		}
		//printArray(x, 10);
		// 이제 j는 pivot보다 작은 요소들의 마지막을 가르키게 됩니다. 
		// pivot 과 j번째를 Swap합니다. 
		Swap(&x[left], &x[j]);
		printArray(x + left,(right-left)+1);
		
		// j를 기준으로 left ~ (j-1), (j+1) ~ right에 동일 작업 수행
		quick_sort(x, left, j - 1);
		quick_sort(x, j + 1, right);
	}
}
int main()
{
	int x[10] = {5,3,4,10,7,6,1,8,2,9};

	printArray(x,10);

	quick_sort(x,0,9);
}
