#include <stdio.h>
#include <stdlib.h>

int main() {
    // 실행시간에 입력된 cnt 만큼 메모리를 할당 --> 동적 메모리 할당


	// 사용자가 -1을 입력 할떄 까지 계속 입력 받고 싶다. 
    // 메모리를 어떻게 할당해야 할까요?
    int in_cnt = 0; //입력된 갯수
    int mem_cnt = 5; // 할당된 메모리 크기;
    
    int* buf = (int*)malloc(sizeof(int) * 5);
	int num = 0;

	// 아래 구현의 문제점 : 5개 이상 입력 되면 잘못된 메모리를 참조하게 된다. 

    while (1) {
    	printf("입력하세요>> ");
    	scanf("%d", &num);
 
		if (num == -1) break;
 
    	buf[in_cnt] = num;
    	++in_cnt; 
	}

    for (int i = 0; i<in_cnt; i++)
		printf("%d \n", buf[i]);

	free(buf); // 메모리 제거
}
