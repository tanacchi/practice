#include <stdio.h>

int main() {

  int num[5];

  int i;
  for (i = 0; i < 5; i++)
    scanf("%d\n", &num[i]);
  
  for (i = 0; i < 5; i++)
    printf("%d\n", num[i]);
  
  return 0;
}
