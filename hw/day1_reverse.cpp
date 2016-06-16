#include <stdio.h>
#include <stdlib.h>

void reverse( int **p1, int *p2) {

	int *temp = (int*)malloc(sizeof(int) * *p2);
	int r = *p2 - 1;
	for (int i=0; i <= *p2; i++){
		temp[i] = (*p1)[r];
		r--;
	}

	free(*p1);
	*p1 = temp;
}

void copySelf( int **p1, int *p2) {

    int newSize = *p2 * 2;
	int org_idx = 0;
	int idx = 0;
    int* temp = (int*)malloc(sizeof(int) * newSize);

	for (int i = 0; i < newSize; i++) {
	    if (i>=*p2) {
		    idx = org_idx - *p2; 
	        temp[i] = (*p1)[idx];
		    org_idx++;
		} else {
	        temp[i] = (*p1)[org_idx];
		    org_idx++;
	    }
    }

	free(*p1);
	*p1 = temp;
}
int main()
{
	int mem_cnt = 5;
	int *buf = (int*)malloc(sizeof(int) * 5);

	for (int i = 0; i<5; i++)
		buf[i] = i;// 0,1,2,3,4

	printf("first\n");
	for (int i = 0; i<5; i++) {
		printf("%d \n", buf[i]);
	}
    // 과제 1.
	//reverse(?); // buf의 내용을 뒤집으세요 
    printf("reverse\n");
	reverse(&buf, &mem_cnt);
	for (int i = 0; i<5; i++)
		printf("%d\n", buf[i]); // reverse실행 후 4,3,2,1,0  
	
	// 과제 2
	//copySelf를 위한 재 조정
	reverse(&buf, &mem_cnt);
    copySelf(&buf, &mem_cnt);
    
	printf("copyself\n");
	for (int i=0; i<10; i++)
		printf("%d\n", buf[i]); // reverse를 수행안했을떄 
                               // 0,1,2,3,4,0,1,2,3,4
// smkang@ioacademy.co.kr
//[자료구조] 라고 표시
}
