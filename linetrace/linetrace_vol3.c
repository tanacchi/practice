#include "lpc13xx.h"
#include "gpio.h"
#include "vs-wrc103.h"
#include "ixbus.h"

#define NULL 0

#define FAST 10000
#define SLOW  5000
#define STOP     0

#define LEFT  0
#define RIGHT 1

enum Mode{
  MDOE_INIT,
  MODE_OP,
  MODE_READ,
  MODE_RUN,
  MODE_SHIFT,
  MODE_ED
};

enum Sensor_result{
  WW, BW, WB, BB
};

int read_sensor(unsigned char ch);
void motor_run(int* param);
int judge_position();
int task_init(const unsigned short main_cycle);
int task_op();
int task_read(int* run_order, int* position);
int task_run(int run_order, int position);
int task_shift(int* run_order);
int task_ed();

int param_list[][4][2] = {
  {{FAST, FAST}, {FAST, STOP}, {STOP, FAST}, {FAST, FAST}},
  {{FAST, FAST}, {STOP, FAST}, {FAST, STOP}, {FAST, FAST}},
  {{FAST, FAST}, {FAST, STOP}, {STOP, FAST}, {FAST, FAST}},
  {{FAST, FAST}, {STOP, FAST}, {FAST, STOP}, {FAST, FAST}},
  {{FAST, FAST}, {FAST, STOP}, {STOP, FAST}, {FAST, FAST}},
  {{FAST, FAST}, {STOP, FAST}, {FAST, STOP}, {FAST, FAST}},
  NULL
};

int order_preset[] = {
  BB, WW, BB, WW, BB
};

int main() {
  int position, run_order = 0;
  int mode = MODE_INIT;

  while (1) {
    switch (mode) {
    case MODE_INIT:
      mode = task_init(60);
      break;
    case MODE_OP:
      mode = task_op();
      break;
    case MODE_READ:
      mode = task_read(&run_order, &position);
      break;
    case MODE_RUN:
      mode = task_run(run_order, position);
      break;
    case MODE_SHIFT:
      mode = task_shift(&run_order);
      break;
    case MODE_ED:
      mode = task_ed();
      return 0;
    }
  }
}

int read_sensor(unsigned char ch) {
  return (ADRead(ch) > 200) ? 1 : 0;
}

void motor_run(int* param) {
  Mtr_Run_lv(param[0], -param[1], 0, 0, 0, 0);
  Wait(1);
}

int judge_position() {
  return (read_sensor(0) << 1 | read_sesor(1));
}

int task_init(const unsigned short main_cycle) {
  Init(main_cycle);
  return MODE_OP;
}

int task_op() {
  return (!getSW()) ? MDOE_OP : MODE_READ;
}

int task_read(int* run_order,int* position) {
  *position = judge_position();
  return (*position != order_preset[*run_order]) ? MODE_RUN : MODE_SHIFT;
}

int task_run(int run_order ,int position) {  
  motor_run(param_list[run_order][position]);
  return MODE_READ;
}

int task_shift(int* run_order) {
  (*run_order)++;
  return (param_list[run_order] != NULL) ? MODE_RUN : MODE_ED;
}

int task_ed() {
  int stop[2] = {STOP, STOP};
  LED(3);
  motor_run(stop);
  return MODE_ED;
}
