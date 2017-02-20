#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 12
#define RANDOM16 ((rand() % 16) +1)

int* selection_sorting(int src[]);
void print_array(int src[]);
void color_print_array(int src[], int i);

int main(void){

  int array[MAX];

  srand((unsigned int)time(NULL));

  int i;
  for (i = 0; i < MAX; i++)
    array[i] = RANDOM16;

  print_array(array);
  
  selection_sorting(array);
  putchar('\n');

  print_array(array);
  
  return 0;
}

int* selection_sorting(int src[]){

  int minpos, buff;
  
  int i, j, k;
  for (i = 0; i < MAX; i++){
    minpos = i;
    for (j = i; j < MAX; j++)
      if (src[j] < src[minpos])
	minpos = j;
    buff = src[minpos];
    src[minpos] = src[i];
    src[i] = buff;

    color_print_array(src, i);
  }
      
  return src;
}

void print_array(int src[]){
  int i;
  for (i = 0; i < MAX; i++)
    printf("%d\t", src[i]);
  printf("\n\n\n");
}


void color_print_array(int src[], int j){
  int i;
  for (i = 0; i < MAX; i++){
    if (i <= j) printf("\x1b[36m");
    else printf("\x1b[39m");

    printf("%d\t", src[i]);
  }
  printf("\n\n");
}
