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
  
  return powl(radian_mm* 0.01, -1) * T;
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
  const DataType offset = 0.000001;

  Param param = initParam(0.1);
  DataType sample_vel = getTerminalVel(param);
  for (DataType d = 1.565; d <= 1.566; d += offset*100) {
    for (DataType C = 0.0018; C <= 0.0021; C += offset) {
      DataType terminal_vel = getTerminalVel2(0.1l, d, C);
      DataType dist = getDist(sample_vel, terminal_vel);
      if (dist < 0.15) printf("d = %Lf\tC = %Lf\tvel = %Lf\tdist = %Lf\n", d, C, terminal_vel, dist);
    }
  }

  param = initParam(0.7);
  sample_vel = getTerminalVel(param);
  printf("%Lf\n", sample_vel);
  for (DataType d = 1.565; d <= 1.566; d += offset*100) {
    for (DataType C = 0.0018; C <= 0.0021; C += offset) {
      DataType terminal_vel = getTerminalVel2(0.7l, d, C);
      DataType dist = getDist(sample_vel, terminal_vel);
      if (dist < 0.15) printf("d = %Lf\tC = %Lf\tvel = %Lf\tdist = %Lf\n", d, C, terminal_vel, dist);
    }
  }
  return 0;
}

/* C = 0.0019 , d = 1.565*/
