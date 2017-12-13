#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define _widthof(array) (sizeof(array) / sizeof(*array))

static const double left_score  = -1.0;
static const double right_score =  1.0;

double initThreshold(const double right_ratio, const double left_ratio)
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

int simPinball(const double threshold, const char* const file_path)
{
  const int ball_num = 1000, max_depth = 501;
  const double score_unit = 0.5;
  int position_list[max_depth];
  for (int i = 0; i < _widthof(position_list); position_list[i++] = 0);
  for (int i = 0; i < ball_num; ++i) {
    double position = 0;
    for (int depth = 1; depth < max_depth; ++depth) position += score_unit * (double)getScore(threshold);
    position_list[(int)position + (int)(max_depth/2)]++;
  }
  
  FILE* filep = fopen(file_path, "w");
  for (int i = 0; i < _widthof(position_list); ++i) fprintf(filep, "%d\t%d\n", (int)(i-_widthof(position_list)/2), position_list[i]);
  fclose(filep);

  return position_list[_widthof(position_list)/2];
}

int main()
{
  srand((unsigned)time(NULL));
  {
    const double threshold = initThreshold(1.0l, 1.0l);
    const char* const file_path = "data.dat";
    int center_balls = simPinball(threshold, file_path);
    printf("x = 0, y = %d\n", center_balls);
    FILE *gplotp = popen("gnuplot -persist", "w");
    fprintf(gplotp, "plot \"%s\" w l lw 5 linetype 1 title \"1\"\n", file_path);
    pclose(gplotp);
  }
  {
    const double threshold = initThreshold(6.0l, 4.0l);
    const char* const file_path = "data.dat";
    int center_balls = simPinball(threshold, file_path);
    printf("x = 0, y = %d\n", center_balls);
    FILE *gplotp = popen("gnuplot -persist", "w");
    fprintf(gplotp, "plot \"%s\" w l lw 5 linetype 1 title \"2\"\n", file_path);
    pclose(gplotp);
  }
  return 0;
}
