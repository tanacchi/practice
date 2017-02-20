#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){

  int array[12];

  srand((unsigned int)time(NULL));

  int i;
  for (i = 0; i < 12; i++)
    array[i] = rand() % 16 + 1;

  for (i = 0; i < 12; i++)
    printf("%d  ", array[i]);
  putchar('\n');
  
  return 0;
}
