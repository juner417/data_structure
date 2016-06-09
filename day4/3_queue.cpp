#include <stdio.h>
#include <stdlib.h>
// 핵심
// 스택은 이덱스가 한개 있으면 된다. 
// 큐는 인덱스가 두개 있어야 ㅎ된다. 


// 배열을 사용한 큐
int buf[100] = { 0 };

int front = 0;
int rear = 0;

void push(int n)
{
	buf[front] = n;
	front++;
}

int pop()
{
	return buf[rear++];
}

int main()
{
	push(10);
	push(20);
	push(30);
	
	printf("%d\n", pop());
	printf("%d\n", pop());
	printf("%d\n", pop());
}
