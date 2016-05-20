#include <stdio.h>
#include <stdlib.h>

// 크기가 커지는 동적 메모리 : 동적배열 또는 vector라고 부른다. 
// java 등의 arraylist가 이렇게 구현 됩니다. 

// 동적 할당 메모리의 크ㄹ기를 키누는 함수j
void resize_array( int **p1, int *p2) {

	// 기존 메모리 크기보다 5개씩 키운다. 
    int newSize = *p2 + 5;

    // 새로운 메모리의 주소는 임ㅈ시 포인터 변수에 보관한다. 
	int* temp = (int*)malloc(sizeof(int) * newSize);

	// 원래 버퍼의 내용을 옮긴다.
	for (int i=0; i <= *p2; i++) 
		temp[i] = (*p1)[i];
 

	// 원래 버퍼를 지운다.
    free(*p1); 

	// 그리고 해야할 나머지 하나는?
    *p2 = newSize;
    // 결국 새로운 메모리 주소는 원본에 넣어준다. 
    *p1 = temp;
}

int main() {
    int in_cnt = 0; //입력된 갯수
    int mem_cnt = 5; // 할당된 메모리 크기;
    
    int* buf = (int*)malloc(sizeof(int) * 5);
	int num = 0;

    while (1) {
    	printf("입력하세요>> ");
    	scanf("%d", &num);
 
		if (num == -1) break;
 
    	buf[in_cnt] = num;
    	++in_cnt; 

		if (in_cnt == mem_cnt) { // 입력된 정수가 메모리 크기와 같아 지면	
			// 메모리를 재 할당 한다. 
			resize_array( &buf, &mem_cnt); // 변수값 바꾸려면 주소를 보내야 한다. 
				
		}
	}

    for (int i = 0; i<in_cnt; i++)
		printf("%d \n", buf[i]);

	free(buf); // 메모리 제거
}
