#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
  char** args;
  args = (char**)calloc(argc+1, sizeof(char*));

  for (int i = 0; i < argc; ++i)
  {
    args[i] = (char*)malloc(sizeof(char)*strlen(argv[i]));
    strcpy(args[i], argv[i]);
  }

  for (size_t i = 0u; i < argc; ++i)
  {
    printf("%s\n", args[i]);
  }

  for (size_t i = 0u; i < argc; ++i)
  {
    free(args[i]);
  }

  free(args);
  return 0;
}
