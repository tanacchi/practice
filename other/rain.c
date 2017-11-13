#include <stdio.h>
#include <math.h>

typedef long double data_type;
typedef data_type (*resist_calculator)(data_type, data_type);

typedef struct {
  data_type radian; // [mm]
  data_type mass;  // [mg]
  data_type proportional_const;
  resist_calculator calculator;
} Param;

typedef struct {
  data_type t;
  data_type v;
} Pair;

const data_type gravity_acc = 0.0098;
const data_type dynamic_viscosity = 0.000018;
const data_type kinetic_viscosity = 0.000015;

data_type calc_mass(data_type radian)
{
  return M_PI * pow(radian, 3) * 4 / 3;
}

data_type resister_method1(data_type vel, data_type proportional_const)
{
  return proportional_const * vel;
}

data_type resister_method2(data_type vel, data_type proportional_const)
{
  return proportional_const * pow(vel, 2);
}

data_type resister_method3(data_type vel, data_type proportional_const)
{
  return 0,0;
}

Param init_param(data_type radian_mm)
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

data_type get_terminal_vel(Param param, data_type time_lim)
{
  data_type vel = 0.0, offset = 0.001;
  for (data_type t = 0.0; t < time_lim; t += offset) {
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
  printf("%Lu", sizeof(data_type));
  /* get_terminal_vel(param, 500); */
  return 0;
}
