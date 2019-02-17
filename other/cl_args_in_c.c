#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
  char** args;
  args = (char**)malloc(sizeof(char*)*argc);

  for (int i = 0; i < argc; ++i)
  {
    args[i] = (char*)malloc(sizeof(char)*strlen(argv[i]));
    strcpy(args[i], argv[i]);
  }

  for (size_t i = 0u; i < argc; ++i)
  {
    printf("%s\n", args[i]);
  }

  return 0;
}
