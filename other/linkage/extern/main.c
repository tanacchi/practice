#include <stdio.h>

extern int index;

int main()
{
  for (int i = 0; i < 3; ++i)
  {
    int a = increment();
    printf("%d\n", a);
  }
  printf("index = %d\n", index);

  return 0;
}
