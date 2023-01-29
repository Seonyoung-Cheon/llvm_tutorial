#include "stdio.h"

void a(){
}

void c(){
  a();
}

int main () {
  int a = 10;
  int b = 20;
  c();
  printf("Result: %d\n", a+b);
  return 0;
}


