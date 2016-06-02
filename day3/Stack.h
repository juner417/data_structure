struct _Stack
{
    int buf[100];
    int index;
};
typedef struct _Stack Stack;

void push(Stack* s, int a)
{
    s->buf[(s->index)++] = a;
}

int pop(Stack* s)
{
    return s->buf[--(s->index)];
}

void init(Stack* s)
{
    s->index = 0;
}

// 스택이 비어있는지 확인하는 함수
int isempty(Stack* s)
{
    return s->index == 0;
}

// 스택에 제일 위 요소를 확인만 하는 함수(제거안함)
int top(Stack* s)
{
    return s->buf[s->index - 1]; // index--가 아님 index는 변화없음
}
