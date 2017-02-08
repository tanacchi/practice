#include <stdio.h>

int i;

int main()
{
 head:
  i = 0;
  
 loop:

  if (i++ < 100000000) goto loop;

  printf("Hello, world!\n");

  goto head;
  
  return 0;
}
