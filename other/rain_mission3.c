#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef long double DataType;
typedef DataType (*resist_calculator)(DataType, DataType);

typedef struct {
  DataType radian_cm;
  DataType mass;
  DataType proportional_const;
  resist_calculator calculator;
} Param;

const DataType gravity_acc = 9.8; // [m/s^2]
const DataType dynamic_viscosity = 0.000018;
const DataType kinetic_viscosity = 0.000015;

DataType calcMass(DataType radian)
{
  return M_PI * pow(radian, 3) * 4 / 3 * 0.001; // [kg]
}

DataType resisterMethod1(DataType vel, DataType proportional_const)
{
  return proportional_const * vel;
}

DataType resisterMethod2(DataType vel, DataType proportional_const)
{
  return proportional_const * pow(vel, 2);
}

DataType getTransVel(DataType vel,  Param param)
{
  return gravity_acc - param.calculator(vel, param.proportional_const) / param.mass;
}

void plotVelFollowingTime(Param param, FILE *gplotp)
{
  const DataType time_offset = 0.001, limit = 10.0;
  DataType vel = 0.0;
  for (DataType t = 0.0; t <= limit; t += time_offset) {
    vel += getTransVel(vel, param) * time_offset;
    printf("t = %Lf\tvel = %.15Lf\n", t, vel);
    fprintf(gplotp, "%Lf\t%Lf\n", t, vel);
  }
}

Param initParam(DataType radian_mm)
{
  Param param;
  param.radian_cm = radian_mm * 0.1;
  param.mass = calcMass(param.radian_cm);
  if (0.0 < radian_mm && radian_mm  <= 0.1) {
    param.proportional_const = 6 * M_PI * dynamic_viscosity * param.radian_cm * 0.01;
    param.calculator = resisterMethod1;
  } else if (0.7 <= radian_mm && radian_mm <= 30) {
    param.proportional_const = 0.235 * M_PI * dynamic_viscosity / kinetic_viscosity * pow(param.radian_cm * 0.01, 2);
    param.calculator = resisterMethod2;
  } else { puts("Invalid argument"); exit(-1); };
  return param;
}

int main()
{
  FILE *gplotp = popen("gnuplot -persist", "w");
  fprintf(gplotp, "set xrange [%f:%f]\n", 0.0, 10.0);
  fprintf(gplotp, "set yrange [%f:%f]\n", 0.0, 50.0);
  fprintf(gplotp, "set xlabel \"x\"\n");
  fprintf(gplotp, "set ylabel \"y\"\n");
  fprintf(gplotp, "plot '-' w p ps 3 pointtype 3\n");
  Param param = initParam(0.1);
  plotVelFollowingTime(param, gplotp);
  fprintf(gplotp, "e\n");
  fclose(gplotp);
  return 0;
}
