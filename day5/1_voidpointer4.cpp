//1_voidpointer4
#include <stdio.h>

// 두개의 변수 값을 swap해 봅시다. 
void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main()
{
	int x = 10, y = 20;
	swap(&x,&y);
	printf("%d, %d\n", x, y); // 20, 10
}
