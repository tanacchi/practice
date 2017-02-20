#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 12

int* insertion_sorting(int src[]);
void print_array(int src[]);
void color_print_array(int src[], int i);

int main(void){

  int array[12];

  srand((unsigned int)time(NULL));

  int i;
  for (i = 0; i < 12; i++)
    array[i] = rand() % 16 + 1;

  print_array(array);

  insertion_sorting(array);
  putchar('\n');
  
  print_array(array);
  
  return 0;
}

int* insertion_sorting(int src[]){
  int buff;
  int i, j;
  for (i = 0; i < MAX; i++){
    for (j = i; j >= 0; j--){
      if (src[j] < src[j-1]){
        buff = src[j];
        src[j] = src[j-1];
        src[j-1] = buff;
      }
      else break;
    }
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
