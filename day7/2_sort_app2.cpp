#include <stdio.h>
#include <stdlib.h>

void printArray(int* x, int sz)
{
	for (int i = 0; i<sz; i++)
		printf("%d ", x[i]);
	printf("\n");
}

void Swap(void* a, void* b, int sz)
{
    char* p1 = (char*)a;
    char* p2 = (char*)b;

    for (int i = 0; i < sz; i++)
    {
        char temp = *(p1+i);
        *(p1+i) = *(p2+i);
        *(p2+i) = temp;
    }
}
// 모든 타입을 정렬하기 위해 void*를 사용한다. 
// void*로 받을 때는 요소의 크기가 같이 전달되어야 한다. 

void quick_sort(void* x, int esz, int left, int right, int(*cmp)(void*, void*))
{
	int i, j;
	// void*를 사용할 때는 가장 작은 타입으로 변경후 사용 
	char* p = (char*)x;

	void* pivot = &p[left* esz]; // 첫번째를 pivot으로
	
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
			} while (cmp(&p[i*esz], pivot));

			// pivot보다 작은 숫자를 찾을 때 까지 j 이동	
			do 
			{	
				--j;
			} while (cmp(pivot, &p[j*esz]));	
			
			// i, j가 교차하지 않은 경우만 두 요소를 swap
			if (i < j)
				Swap(&p[i*esz], &p[j*esz], esz);
			else
				break;
		}
		Swap(&p[left*esz], &p[j*esz], esz);

		quick_sort(x, left, j - 1, cmp);
		quick_sort(x, j + 1, right, cmp);
	}
}

// sort로 전ㄴ달할 빅 함수들
int cmp1(void* a, void* b) 
{
	double* p1 = (double*)a;
	double* p2 = (double*)b;
	return *p1 < *p2;
}
int cmp2(int a, int b) {return a > b;}
int cmp3(int a, int b) {return abs(a) > abs(b);}


int main()
{
	double x[10] = {5,3,4,10,7,6,1,8,2,9};

	//printArray(x,10);
	quick_sort(x,0,9, cmp1);
	//quick_sort(x,0,9, cmp2);
	//printArray(x,10);
	
}
