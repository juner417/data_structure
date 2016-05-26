#include <stdio.h>
#include <stdlib.h>

int main() {
	int cnt = 10;
	// 실행 시간에 결정된 cnt만큼의 int가 필요하다. 
	int *p = (int*)malloc(sizeof(int) *10); //malloc은 주소를 리턴한다. 
    // *p는 스택에 저장되어 있고, malloc으로 할당한 메모리는 heap에 저장됨
    for (int i = 0; i<cnt; i++) {
        p[i] = 0;
        printf("p %d add: %p, p value: %d\n",i, &p, p[i]);
    }
}
