#include <stdio.h>
#include <math.h>

typedef double (*Formula)(double, double);

typedef struct {
  double x;
  double y;
} Pair;

static inline double formula1(double x, double y)
{
  return y + 2 * sin(2*x);
}

static inline double formula2(double x, double y)
{
  return -2 * pow(y, 2) + exp(-x);
}

double euler(Pair begin, int x_lim, const Formula formula)
{
  double y = begin.y, offset = 0.0001;
  puts("=================================================");
  for (; begin.x < x_lim; begin.x += offset) {
    printf("x = %f, y = %f\n", begin.x, y);
    y += (*formula)(begin.x, y) * offset;
  }
  puts("=================================================");
  return y;
}

int main(int argc, char** argv)
{
  Pair question1 = {2, 0};
  Pair question2 = {0, 0};
  double ans1 = euler(question1, 50, formula1);
  double ans2 = euler(question2, 1, formula2);
  printf("Question1 : f(5) = %f\n", ans1);
  printf("Question2 : f(1) = %f\n", ans2);
  return 0;
}
