#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t get_max_argv_length(char** argv)
{
  size_t max_length = 0;
  for (size_t i = 0; argv[i] != NULL; ++i)
  {
    size_t length = strlen(argv[i]);
    if (length > max_length)
    {
      max_length = length;
    }
  }
  return max_length;
}

int main(int argc, char** argv)
{
  const size_t max_argv_length = get_max_argv_length(argv);
  char args[argc][max_argv_length];

  for (size_t i = 0; i < argc; ++i)
  {
    strcpy(args[i], argv[i]);
  }
  
  for (size_t i = 0; i < argc; ++i)
    puts(args[i]);

  return 0;
}
