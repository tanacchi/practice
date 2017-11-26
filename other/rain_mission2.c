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

DataType getTerminalVel2(DataType radian_mm, DataType d)
{
  const DataType radian = radian_mm * 0.001;
  return powl(radian, 3/2-1);
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
  } else { puts("Invalid argument"); exit(-1); };
  return param;
}

int main()
{
  FILE *gplotp = popen("gnuplot -persist", "w");
  fprintf(gplotp, "set xrange [%f:%f]\n", 0.0, 0.8);
  fprintf(gplotp, "set yrange [%f:%f]\n", 0.0, 7.0);
  fprintf(gplotp, "set xlabel \"x\"\n");
  fprintf(gplotp, "set ylabel \"y\"\n");
  fprintf(gplotp, "plot '-' w p ps 2 pointtype 2\n");
  const DataType rad_offset = 0.01;
  for (int i = 1; i <= 10; ++i) {
    Param param = initParam(i*rad_offset);
    DataType terminal_vel = getTerminalVel(param);
    printf("r = %Lf\tvel = %.15Lf\n", i*rad_offset, terminal_vel);
    fprintf(gplotp, "%Lf\t%.15Lf\n", i*rad_offset, terminal_vel);
  }
  for (int i = 70; i <= 80; ++i) {
    Param param = initParam(i*rad_offset);
    DataType terminal_vel = getTerminalVel(param);
    printf("r = %Lf\tvel = %.15Lf\n", i*rad_offset, terminal_vel);
    fprintf(gplotp, "%Lf\t%.15Lf\n", i*rad_offset, terminal_vel);
  }
  /* fprintf(gplotp, "plot '-' w p ps 5 pointtype 3\n"); */
  for (int i = 10; i < 70; ++i) {
    DataType terminal_vel = getTerminalVel2(i*rad_offset, 1.6);
    printf("r = %Lf\tvel = %.15Lf\n", i*rad_offset, terminal_vel);
    fprintf(gplotp, "%Lf\t%.15Lf\n", i*rad_offset, terminal_vel);    
  }
  Param param;
  param = initParam(0.1);
  DataType terminal_vel01 = getTerminalVel(param);
  param = initParam(0.7);
  DataType terminal_vel07 = getTerminalVel(param);
  
  fprintf(gplotp, "e\n");
  fclose(gplotp);
  return 0;
}
