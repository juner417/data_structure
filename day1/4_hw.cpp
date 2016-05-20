#include <stdio.h>
#include <stdlib.h>

int main()
{
	int *buf = (int*)malloc(sizeof(int) * 5);

	for (int i = 0; i<5; i++)
		buf[i] = i;// 0,1,2,3,4
    // 과제 1.
	//reverse(?); // buf의 내용을 뒤집으세요 

	for (int i = 0; i<5; i++)
		printf("%d\n", buf[i]); // reverse실행 후 4,3,2,1,0  
	
	// 과제 2
    //copySelf(&buf);

	for (int i=0; i<10; i++)
		printf("%d\n", buf[i]); // reverse를 수행안했을떄 
                                // 0,1,2,3,4,0,1,2,3,4
}

// smkang@ioacademy.co.kr
//[자료구조] 라고 표시
