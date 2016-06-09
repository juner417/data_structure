#include <stdio.h>
#include <stdlib.h>

// 배열 기반의 원형 ㄱ큐
// 비어있을 떄와 가득 찬 경우를 구별하기 위한 슬롯 하나는 사용하지 않고 비ㅝ둔다. 
//front = (front+1) % 큐버퍼크기

// 큐를 구성하는 data를 묶어서 타입화 하자 
// ADT(abstract data type)
#define QUEUE_SIZE 100

struct _Queue
{
	int buf[QUEUE_SIZE];
	int front;
	int rear;
};
typedef struct _Queue Queue;

void init_queue(Queue* q) 
{
	q->front = 0;
	q->rear = 0;
	
}

int isempty(Queue* q)
{
	return q->front == q->rear ;
}

int isfull(Queue* q)
{
	return (q->front + 1) % QUEUE_SIZE == q->rear;
}

// Q에 넣기 
void push(Queue* q, int data)
{
	if (isfull(q)) return; // 가득찬 경우는 무시 
	
	q->buf[q->front] = data;
	q->front = (q->front + 1) % QUEUE_SIZE;
	
}

int pop(Queue* q)
{
	if (isempty(q)) return -1;
	
	int ret = q->buf[q->rear];
	q->rear = (q->rear + 1) % QUEUE_SIZE;
	return ret;
}
int main()
{
	Queue q1, q2;	
	init_queue(&q1);
	init_queue(&q2);

	// q1에 1~50까지 넣으세요
	for (int i = 1; i<=50; i++)
	{
		push(&q1, i);
	}

	// q1이 빌때까지 꺼네세요
	while( !isempty(&q1) )
	{
		printf("%d\n", pop(&q1));
	}

	// q1에 80 깨 넣으세요
	for (int i = 1; i<=80; i++)
	{
		push(&q1, i);
	}

	// q1이 빌때까지 꺼네세요
	while( !isempty(&q1) )
	{
		printf("%d\n", pop(&q1));
	}

	
}
