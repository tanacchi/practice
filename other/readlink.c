#include <stdio.h>
#include <unistd.h>

int main()
{
  char my_path[100];
  readlink("/proc/self/exe", my_path, sizeof(my_path));

  puts(my_path);

  return 0;
}
