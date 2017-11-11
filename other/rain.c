#include <stdio.h>
#include <math.h>

typedef long double (*resist_calculator)(long double, long double);

typedef struct {
  long double radian; // [mm]
  long double mass;  // [mg]
  long double proportional_const;
  resist_calculator calculator;
} Param;

typedef struct {
  long double t;
  long double v;
} Pair;

const long double gravity_acc = 0.0098;
const long double dynamic_viscosity = 0.000018;
const long double kinetic_viscosity = 0.000015;

long double calc_mass(long double radian)
{
  return ((4/3) * M_PI * pow(radian, 3));
}

long double resister_method1(long double vel, long double proportional_const)
{
  return proportional_const * vel;
}

long double resister_method2(long double vel, long double proportional_const)
{
  return proportional_const * pow(vel, 2);
}

long double resister_method3(long double vel, long double proportional_const)
{
  return 0,0;
}

Param init_param(long double radian_mm)
{
  Param param;
  param.radian = radian_mm;
  param.mass = calc_mass(param.radian);
  if (0.0 < radian_mm && radian_mm  <= 0.1) {
    param.proportional_const = 6 * M_PI * dynamic_viscosity * param.radian;
    param.calculator = resister_method1;
  }
  else if (0.7 <= radian_mm && radian_mm <= 30) {
    param.proportional_const = 0.235 * M_PI * dynamic_viscosity * pow(param.radian, 2) / kinetic_viscosity;
    param.calculator = resister_method2;
  }
  else puts("Invalid argument");
  return param;
}

long double get_terminal_vel(Param param, long double time_lim)
{
  long double vel = 0.0, offset = 0.001;
  for (long double t = 0.0; t < time_lim; t += offset) {
    printf("time = %Lf\t\tvel = %Lf\n", t, vel);
    vel += (gravity_acc - (*param.calculator)(vel, param.proportional_const)/param.mass) * offset;
  }
  return vel;
}

int main()
{
  Param param = init_param(30);
  printf("radian : %Lf\n"
         "mass   : %Lf\n"
         "const  : %Lf\n"
         "resist : %Lf\n"
         , param.radian, param.mass, param.proportional_const, (*param.calculator)(1, param.proportional_const));
  printf("%Lu", sizeof(long double));
  get_terminal_vel(param, 500);
  return 0;
}
