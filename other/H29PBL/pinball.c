#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum { Left = -1, Right = 1 };

typedef double DataType;

DataType genThreshold(const float left_ratio, const float right_ratio)
{
  return left_ratio / (left_ratio + right_ratio);
}

DataType getRand()
{
  return (DataType)rand() / ((DataType)RAND_MAX + 1.0);
}

int getDirectoin(const float threshold)
{
  return (getRand() < threshold) ? Left : Right;
}

int main()
{
  srand((unsigned)time(NULL));
  const DataType threshold = genThreshold(6.0l, 4.0l);

  float count = 0;
  const float times = 100000;
  for (int i = 0; i < times; ++i) {
    if (getDirectoin(threshold) == -1) count++;
  }
  
  printf("%.10f\n", count / times);
  return 0;
}
