#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define _widthof(array) (sizeof(array) / sizeof(*array))

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

void simPinball(const double threshold, const char* const file_path)
{
  const int ball_num = 1000, max_depth = 501;
  const double score_unit = 0.5;
  static int position_list[max_depth];
  
  for (int i = 0; i < ball_num; ++i) {
    double position = 0;
    for (int depth = 1; depth < max_depth; ++depth)
      position += score_unit * (double)getScore(threshold);
    position_list[(int)position + (int)(max_depth/2)]++;
  }
  
  FILE* filep = fopen(file_path, "w");
  for (int i = 0; i < _widthof(position_list); ++i) fprintf(filep, "%d\t%d\n", (int)(i-_widthof(position_list)/2), position_list[i]);
  fclose(filep);
}

int main()
{
  srand((unsigned)time(NULL));
  const double threshold = initThreshold(1.0l, 1.0l);

  const char* const data1_file_path = "data1.dat";
  simPinball(threshold, data1_file_path);

  FILE *gplotp = popen("gnuplot -persist","w");
  fprintf(gplotp, "plot \"%s\" with lines linetype 1 title \"data1\"\n", data1_file_path);
  pclose(gplotp);
  
  return 0;
}
