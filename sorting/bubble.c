#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 12

int* bubble_sorting(int src[]);
void print_array(int src[]);
void color_print_array(int src[], int i);

int main(void){

  int array[MAX];

  srand((unsigned int)time(NULL));

  int i;
  for (i = 0; i < 12; i++)
    array[i] = rand() % 16 + 1;

  print_array(array);  

  bubble_sorting(array);

  print_array(array);
  
  return 0;
}

int* bubble_sorting(int src[]){
  int i, j;
  for (){
    for (j = i ){
      if (src[i] < src[j])
    }
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

