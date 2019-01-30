// Compile it with gcc -nostartfiles

#include <stdio.h>
#include <stdlib.h>

int main();

void _start()
{
  puts("Hello");
  int ret = main();
  exit(ret);
}

int main()
{
  puts("World");

  return 0;
}
