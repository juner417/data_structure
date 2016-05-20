// typedef의 정확한 의미 : 변수자리에 있는 변수가 아님 타입으로 해달라

#include <stdio.h>

int a;
double d;
int *p;
void(*f)(int, int);

typedef int INT;

typedef int a; // a aa -> int aa
typedef double d; // d dd -> double dd
typedef int *p; 
typedef void(*f)(int, int);
