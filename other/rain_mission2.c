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

typedef struct {
  DataType param_C;
  DataType param_d;
  DataType dist;
} DataSet;

const DataType gravity_acc = 9.8; // [m/s^2]
const DataType dynamic_viscosity = 0.000018;
const DataType kinetic_viscosity = 0.000015;

DataType calcMass(DataType radian_cm)
{
  return M_PI * pow(radian_cm, 3) * 4 / 3 * 0.001; // [kg]
}

DataType terminalVelMethod1(DataType mass, DataType proportional_const)
{
  return mass * gravity_acc / proportional_const;
}

DataType terminalVelMethod2(DataType mass, DataType proportional_const)
{
  return sqrtl(mass * gravity_acc / proportional_const);
}

DataType getTerminalVel(Param param)
{
  return param.calculator(param.mass, param.proportional_const);
}

DataType getTerminalVel2(DataType radian_mm, DataType d, DataType C)
{
  const DataType mass = calcMass(radian_mm * 0.1);
  const DataType T = powl(mass * gravity_acc / C, 1/d);
  
  return powl(radian_mm* 0.001, -1) * T;
}

Param initParam(DataType radian_mm)
{
  Param param;
  param.radian_cm = radian_mm * 0.1;
  param.mass = calcMass(param.radian_cm);
  if (0.0 < radian_mm && radian_mm  <= 0.1) {
    param.proportional_const = 6 * M_PI * dynamic_viscosity * param.radian_cm * 0.01;
    param.calculator = terminalVelMethod1;
  } else if (0.7 <= radian_mm && radian_mm <= 30) {
    param.proportional_const = 0.235 * M_PI * dynamic_viscosity / kinetic_viscosity * pow(param.radian_cm * 0.01, 2);
    param.calculator = terminalVelMethod2;
  } else { puts("Invalid argument"); exit(-1); }
  return param;
}

DataType getDist(DataType a, DataType b)
{
  return fabsl(a - b);
}

int main()
{
  FILE *gplotp = popen("gnuplot -persist", "w");
  const DataType offset = 0.00001;
  const DataType r01 = 0.001l, r07 = 0.007l;
  const DataType v01 = 1.210l, v07 = 5.695l;
  
  fprintf(gplotp, "set xrange [%f:%f]\n", 1.0, 2.0);
  fprintf(gplotp, "set yrange [%f:%f]\n", 0.0, 10000.0);
  fprintf(gplotp, "set xlabel \"d\"\n");
  fprintf(gplotp, "set ylabel \"distance\"\n");  
  fprintf(gplotp, "plot '-' w p ps 1.0 pointtype 7\n");
  for (DataType d = 1.0l; d <= 2.0l; d+=offset) {
    DataType distance = fabsl(pow(r01, d-3)*pow(v01, d) - pow(r07, d-3)*pow(v07, d));
    if (distance < 100) printf("%Lf\t%Lf\n", d, distance);
  }
  return 0;
}
