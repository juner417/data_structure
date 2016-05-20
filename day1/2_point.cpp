// 2_포인터
#include <stdio.h>
/*
void inc(int n) 
{
    // call by value - 원본 메모리의 정보를 받는게 아니라 
    // 값만 전달 받는다.. 원본을 변경할 수 없다. 
    // main 합무의 x는 다른 주소에 저장 되어 있다. 
    ++n;
}
*/
// 핵심 1: 변수의 값을 변경하려면 주소를 보내야 한다. 
// 	    2: int의 주소를 받을 떄는 int* 타입을 사용해야 한다. 
void inc(int *p)
{
    //++(p) // p의 주소값이 증가 
    ++(*p);  // p가 가르키는 곳을 다라가서 증가

}

int main() 
{
    int x = 10;
    inc(&x);
    printf("x : %d \n", x); //11
}
