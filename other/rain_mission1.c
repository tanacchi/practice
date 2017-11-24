#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef long double data_type;
typedef data_type (*resist_calculator)(data_type, data_type);

typedef struct {
  data_type radian_cm;
  data_type mass;
  data_type proportional_const;
  resist_calculator calculator;
} Param;

const data_type gravity_acc = 9.8; // [m/s^2]
const data_type dynamic_viscosity = 0.000018;
const data_type kinetic_viscosity = 0.000015;

data_type calc_mass(data_type radian)
{
  return M_PI * pow(radian, 3) * 4 / 3 * pow(10, -3); // [kg]
}

data_type terminal_vel_method1(data_type mass, data_type proportional_const)
{
  return mass * gravity_acc / proportional_const;
}

data_type terminal_vel_method2(data_type mass, data_type proportional_const)
{
  return sqrtl(mass * gravity_acc / proportional_const);
}

data_type get_terminal_vel(Param param)
{
  return param.calculator(param.mass, param.proportional_const);
}

Param init_param(data_type radian_mm)
{
  Param param;
  param.radian_cm = radian_mm * pow(10, -1);
  param.mass = calc_mass(param.radian_cm);
  if (0.0 < radian_mm && radian_mm  <= 0.1) {
    param.proportional_const = 6 * M_PI * dynamic_viscosity * (param.radian_cm * pow(10, -2));
    param.calculator = terminal_vel_method1;
  } else if (0.7 <= radian_mm && radian_mm <= 30) {
    param.proportional_const = 0.235 * M_PI * dynamic_viscosity / kinetic_viscosity * pow(param.radian_cm * pow(10, -2), 2);
    param.calculator = terminal_vel_method2;
  } else { puts("Invalid argument"); exit(-1); };
  return param;
}

int main()
{
  /* FILE *gplotp = popen("gnuplot -persist", "w"); */
  /* fprintf(gplotp, "set xrange [%f:%f]\n", 0.0, 0.8); */
  /* fprintf(gplotp, "set yrange [%f:%f]\n", 0.0, 3.0); */
  /* fprintf(gplotp, "set xlabel \"x\"\n"); */
  /* fprintf(gplotp, "set ylabel \"y\"\n"); */
  /* fprintf(gplotp, "plot '-' w p ps 5 pointtype 3\n"); */
  /* const data_type rad_offset = 0.01; */
  /* for (int i = 1; i <= 10; ++i) { */
  /*   Param param = init_param(i*rad_offset); */
  /*   data_type terminal_vel = get_terminal_vel(param); */
  /*   printf("%.15Lf\n", terminal_vel); */
  /*   fprintf(gplotp, "%Lf\t%.15Lf\n", i*rad_offset, terminal_vel); */
  /* } */
  /* for (int i = 70; i < 80; ++i) { */
  /*   Param param = init_param(i*rad_offset); */
  /*   data_type terminal_vel = param.mass * gravity_acc / param.proportional_const; */
  /*   printf("%.15Lf\n", terminal_vel); */
  /*   fprintf(gplotp, "%Lf\t%.15Lf\n", i*rad_offset, terminal_vel); */
  /* } */
  /* fprintf(gplotp, "e\n"); */
  /* fclose(gplotp); */
  Param param;
  param = init_param(30);
  printf("%.15Lf\n", get_terminal_vel(param));
  return 0;
}
