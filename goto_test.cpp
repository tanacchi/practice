#include <stdio.h>

int main()
{
 loop:
  for (int i = 0; i < 10000000; i++) ;

  printf("Hello, world!\n");

  goto loop;
  
  return 0;
}
