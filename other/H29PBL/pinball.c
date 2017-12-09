#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define _widthof(array) (int)(sizeof(array) / sizeof(*array))

static const double left_score  = -1.0;
static const double right_score =  1.0;

double initThreshold(const double left_ratio, const double right_ratio)
{
  return left_ratio / (left_ratio + right_ratio);
}

double genRand()
{
  return (double)rand() / ((double)RAND_MAX + 1.0);
}

double getScore(const double threshold)
{
  return (genRand() < threshold) ? left_score : right_score;
}

int getAccessNum(const int position, const int* array)
{
  return position + _widthof(array) / 2;
}

const int* getSimResult(const double threshold)
{
  const int ball_num = 100000, max_depth = 501;
  const double score_unit = 0.5;

  static int position_list[max_depth];
  for (int i = 0; i < ball_num; ++i) {
    double position = 0;
    for (int depth = 1; depth < max_depth; ++depth)
      position += score_unit * (double)getScore(threshold);
    position_list[(int)position + (int)(max_depth/2)]++;
  }
  return position_list;
}

int main()
{
  srand((unsigned)time(NULL));
  const double threshold = initThreshold(1.0l, 1.0l);
  
  const int* result = getSimResult(threshold);
  for (int i = 0; i < 501; ++i)
    printf("%d\n", result[i]);
  return 0;
}
