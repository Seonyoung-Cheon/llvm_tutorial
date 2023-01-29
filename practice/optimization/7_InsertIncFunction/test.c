#include<stdio.h>

int a (int t) {
  return t;
}

int b (int t) {
  return a(t);
}

int c (int t) {
  return b(t);
}

int main () {
  printf("result : %d\n", c(0));
  return 0;
}
