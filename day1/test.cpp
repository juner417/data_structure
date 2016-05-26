#include <stdio.h>

int main() {

  int x = 100;
  int *p;
  p = &x;

  printf("var x value : %d \n" , x);
  printf("var x address : %p \n" , &x);
  printf("pointer var p in x address : %p \n" , p);
  printf("var x value referrened by p : %d \n" , *p);
}
