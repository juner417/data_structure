// 2_리스트 개념
#include <stdio.h>
#include <stdlib.h>

int main() 
{
	int n = 0;
	int* head = 0;
	// 사용자가 -1을 입력 할 때 까지 계속 입력하고 싶다. 

	while (1) 
	{
		scanf("%d", &n);
		if (n==-1) break;

		head = (int*)malloc(sizeof(int));
		*head = n;
	}
}
