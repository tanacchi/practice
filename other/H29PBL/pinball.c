#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum { Left = 0, Right = 1 };

float initThreshold(float left_ratio, float right_ratio);
int getDirectoin(float threshold);

int main()
{
  srand((unsigned)time(NULL));

  return 0;
}

float initThreshold(float left_ratio, float right_ratio)
{
  return left_ratio / (left_ratio + right_ratio) * 100.0;
}

int getDirectoin(float threshold)
{
  return (threshold < rand() % 100) ? Left : Right;
}

