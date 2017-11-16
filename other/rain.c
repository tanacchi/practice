#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long double data_type;
typedef data_type (*resist_calculator)(data_type, data_type);

typedef struct {
  data_type radian;
  data_type mass;
  data_type proportional_const;
  resist_calculator calculator;
} Param;

typedef struct {
  data_type t;
  data_type v;
} Pair;

const data_type gravity_acc = 9.8; // [m/s^2]
const data_type dynamic_viscosity = 0.000018;
const data_type kinetic_viscosity = 0.000015;

data_type calc_mass(data_type radian)
{
  return M_PI * pow(radian, 3) * 4 / 3 * pow(10, -6); // [kg]
}

data_type resister_method1(data_type vel, data_type proportional_const)
{
  return proportional_const * vel; // [N]
}

data_type resister_method2(data_type vel, data_type proportional_const)
{
  return proportional_const * pow(vel, 2); // [N]
}

data_type resister_method3(data_type vel, data_type proportional_const)
{
}

Param init_param(data_type radian_mm)
{
  Param param;
  param.radian = radian_mm;
  param.mass = calc_mass(param.radian);
  if (0.0 < radian_mm && radian_mm  <= 0.1) {
    puts("ONE");
    param.proportional_const = 6 * M_PI * dynamic_viscosity * param.radian;
    param.calculator = resister_method1;
  }
  else if (0.7 <= radian_mm && radian_mm <= 30) {
    puts("TWO");
    param.proportional_const = 0.235 * M_PI * dynamic_viscosity * pow(param.radian, 2) / kinetic_viscosity;
    param.calculator = resister_method2;
  }
  else { puts("Invalid argument"); exit(-1); };
  return param;
}

data_type get_terminal_vel(Param param, data_type time_lim, FILE* fp)
{
  data_type vel = 0.0, offset = 0.0001;
  for (data_type t = 0.0; t < time_lim; t += offset) {
    printf("time = %Lf\t\tvel = %.15Lf\n", t, vel);
    fprintf(fp, "%Lf\t%.15Lf\n", t, vel);
    vel += (gravity_acc - (*param.calculator)(vel, param.proportional_const) / param.mass) * offset;
  }
  return vel;
}

int main()
{
  FILE *data_01_filep, *data_30_filep;
  const char* const data_01_path = "data_01_output.dat";
  const char* const data_30_path = "data_30_output.dat";
  if ((data_01_filep = fopen(data_01_path, "w")) == NULL) { printf("Could not open %s !!\n", data_01_path); exit(1); }
  if ((data_30_filep = fopen(data_30_path, "w")) == NULL) { printf("Could not open %s !!\n", data_30_path); exit(1); }
  
  Param param1 = init_param(0.1);
  data_type terminal_vel1 = get_terminal_vel(param1, 0.1, data_01_filep);
  fclose(data_01_filep);

  Param param2 = init_param(30);
  data_type terminal_vel2 = get_terminal_vel(param2, 0.1, data_30_filep);
  fclose(data_30_filep);

  FILE *gplotp = popen("gnuplot -persist", "w");
  fprintf(gplotp, "set multiplot\n");
  fprintf(gplotp, "set grid\n");
  fprintf(gplotp, "set xrange [0.0:0.02]\n");
  fprintf(gplotp, "set yrange [0.0:0.04]\n");
  fprintf(gplotp, "set palette model HSV functions gray,1,1\n");
  fprintf(gplotp, "plot \"%s\" w l lw 3 lc palette frac 0.5 title \"2\"\n", data_01_path);
  fprintf(gplotp, "plot \"%s\" w l lw 3 lc palette frac 0.0 title \"1\"\n", data_30_path);
  pclose(gplotp);
  
  return 0;
}
