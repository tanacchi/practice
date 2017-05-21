#include <stdio.h>

typedef struct tmp {
  float num;
  const int* const array;
} Sample;

const int* make_array() {
  static int dist[5] = {0, 5, 5, 5, 2};
  return dist;
}

int main() { 

  Sample ttt = {
    8.67,
    make_array(),
  };
    
  int i;
  for (i = 0; i < 63; i++)
    printf("%d\n", ttt.array[i]);
    
  return 0;
}
