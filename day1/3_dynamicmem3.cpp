#include <stdio.h>
#include <stdlib.h>

// 다른 함수에서 동적 메모리 할당한 주소를 꺼네오는 코드 

// 메모리를 할당하고 0으로 리셋해주는 함수
void AllocZeroMemory( int **p, int n ) {
	*p = (int*)malloc(sizeof(int)* n);	

    for ( int i = 0; i<n; i++) 
    {
        (*p)[i] = 0;
    }
}

int main() {
	int cnt = 10; // 정수 담는 변수 
	int *p = 0; // 주소를 담는 변수

	AllocZeroMemory( &p, cnt );
}
