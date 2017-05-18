#include <stdio.h>

void hello(int num) {
  printf("Hello! %d\n", num);
}

void bye(int num) {
  printf("Good bye! %d\n", num);
}

typedef struct tmp {
  int n;
  void (*func)(int);
}tmp;

int main() {

  tmp s[3] = {
    { 3, bye },
    { 6, hello},
    { 8, hello}
  };

  int i;
  for (i = 0; i < 3; i++) {
    (*s[i].func)(s[i].n);
  }
  return 0;
}
