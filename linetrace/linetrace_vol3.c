#include "lpc13xx.h"
#include "gpio.h"
#include "vs-wrc103.h"
#include "ixbus.h"

#define NULL 0

#define FAST 10000
#define SLOW 5000
#define STOP 0

enum Mode{
  MODE_INIT,
  MODE_OP,
  MODE_READ,
  MODE_RUN,
  MODE_SHIFT,
  MODE_ED
};

enum Sensor_result{
  WW, WB, BW, BB
};

int is_sensor_Black(unsigned char ch);
void run_motor(int* param);
int get_position();
int task_init(int* run_order);
int task_op();
int task_read(int* run_order, int* position);
int task_run(int run_order, int position);
int task_shift(int* run_order);
int task_ed();

const int param_list[][4][2] = {

  //   WW            WB            BW            BB
  {{ FAST,  FAST}, { SLOW,  FAST}, { FAST,  SLOW}, { FAST,  FAST}}, //  0.over start line
  {{ STOP,  FAST}, { FAST,  STOP}, { STOP,  FAST}, { FAST,  STOP}}, //  1.right edge until T
  {{ FAST,  STOP}, { FAST,  SLOW}, { SLOW,  FAST}, { FAST,  FAST}}, //  2.over T zone
  {{ FAST,  FAST}, { FAST,  STOP}, { STOP,  FAST}, { FAST,  FAST}}, //  3.trace until +
  {{ FAST,  FAST}, { FAST, -FAST}, {-FAST,  FAST}, { FAST,  FAST}}, //  4.over +
  {{ FAST,  FAST}, { FAST, -SLOW}, {-SLOW,  FAST}, { FAST,  FAST}}, //  5.trace until condenser
  {{ FAST,  FAST}, { SLOW,  FAST}, { SLOW,  FAST}, { FAST,  FAST}}, //  6.enter the condenser
  {{ FAST,  FAST}, { FAST,  STOP}, { STOP,  FAST}, { FAST,  FAST}}, //  7.run between plate
  {{ FAST,  FAST}, { SLOW,  FAST}, { FAST,  SLOW}, { FAST,  FAST}}, //  8.get out condenser
  {{ FAST,  FAST}, { FAST,  STOP}, { STOP,  FAST}, { FAST,  FAST}}, //  9.trace until +
  {{ FAST,  FAST}, { SLOW, -FAST}, {-FAST,  SLOW}, { FAST,  FAST}}, // 10.over +
  {{ SLOW, -SLOW}, { SLOW, -SLOW}, { SLOW, -SLOW}, { SLOW, -SLOW}}, // 11.turn right until WB
  {{ SLOW, -SLOW}, { SLOW, -SLOW}, { SLOW, -SLOW}, { SLOW, -SLOW}}, // 12.turn right until WW
  {{ FAST,  STOP}, { FAST,  STOP}, { STOP,  FAST}, { STOP,  FAST}}, // 13.left edge until T
  {{ FAST,  STOP}, { FAST,  STOP}, { FAST,  STOP}, { FAST,  STOP}}, // 14.turn right until WW
  {{ FAST,  FAST}, { FAST, -SLOW}, {-SLOW,  FAST}, { FAST,  FAST}}, // 15.trace until く
  {{ SLOW, -SLOW}, { SLOW, -SLOW}, { SLOW, -SLOW}, { SLOW, -SLOW}}, // 16.toward right until WW
  {{ FAST,  FAST}, { FAST,  STOP}, { STOP,  FAST}, { FAST,  FAST}}, // 17.trace until +
  {{ FAST,  FAST}, { FAST,  FAST}, { FAST,  FAST}, { FAST,  FAST}}, // 18.over +
  {{ FAST,  FAST}, { FAST,  STOP}, { STOP,  FAST}, { FAST,  FAST}}, // 19.trace until condenser
  {{ FAST,  FAST}, { FAST, -SLOW}, {-SLOW,  FAST}, { FAST,  FAST}}, // 20.enter the condenser
  {{ FAST,  FAST}, { FAST,  STOP}, { STOP,  FAST}, { FAST,  FAST}}, // 21.run between plate
  {{ FAST,  FAST}, { FAST, -FAST}, {-FAST,  FAST}, { FAST,  FAST}}, // 22.get out condenser
  {{ FAST,  FAST}, { FAST, -SLOW}, {-SLOW,  FAST}, { FAST,  FAST}}, // 23.trace until +
  {{ FAST,  FAST}, { SLOW, -FAST}, {-FAST,  SLOW}, { FAST,  FAST}}, // 24.over +
  {{-SLOW,  SLOW}, {-SLOW,  SLOW}, {-SLOW,  SLOW}, {-SLOW,  SLOW}}, // 25.turn left until BW
  {{-SLOW,  SLOW}, {-SLOW,  SLOW}, {-SLOW,  SLOW}, {-SLOW,  SLOW}}, // 26.turn left until WW
  {{ FAST,  FAST}, { FAST, -FAST}, {-FAST,  FAST}, { FAST,  FAST}}, // 27.trace until く
  {{ STOP,  SLOW}, { STOP,  SLOW}, { STOP,  SLOW}, { STOP,  SLOW}}, // 28.toward left until WW
  {{ STOP,  FAST}, { FAST,  STOP}, { STOP,  FAST}, { FAST,  STOP}}, // 29.right edge until T
  {{ FAST,  FAST}, { STOP,  FAST}, { FAST,  STOP}, { FAST,  FAST}}, // 30.over T
  {{ SLOW, -SLOW}, { SLOW, -SLOW}, { SLOW, -SLOW}, { SLOW, -SLOW}}, // 31.turn right until WB
  {{ SLOW, -SLOW}, { SLOW, -SLOW}, { SLOW, -SLOW}, { SLOW, -SLOW}}, // 32.turn right until WW
  {{ FAST,  FAST}, { FAST,  STOP}, { STOP,  FAST}, { FAST,  FAST}}, // 33.trace until Goal
  {{-FAST,  FAST}, {-FAST,  FAST}, {-FAST,  FAST}, {-FAST,  FAST}}, // 34.toward left until WW
  {{-FAST,  FAST}, {-FAST,  FAST}, {-FAST,  FAST}, {-FAST,  FAST}}, // 35.toward left until BW
  {{-FAST,  FAST}, {-FAST,  FAST}, {-FAST,  FAST}, {-FAST,  FAST}}, // 36.toward left until WW
  {{-SLOW, -SLOW}, {-SLOW, -SLOW}, {-SLOW, -SLOW}, {-SLOW, -SLOW}}, // 37.back until BB
  NULL
};

//     {{FAST, FAST}, {FAST, STOP}, {STOP, FAST}, {FAST, FAST}}, // Normal trace

const int order_preset[] = {
// 0   1   2   3   4   5   6   7   8   9
  WW, BB, WW, BB, WW, BB, WW, BB, WW, BB,

//10  11  12  13  14  15  16  17  18  19
  WW, WB, WW, BB, WW, BB, WW, BB, WW, BB,

//20  21  22  23  24  25  26  27  28  29
  WW, BB, WW, BB, WW, BW, WW, BB, WW, BB,

//30  31  32  33  34  35  36  37
  WW, WB, WW, BB, WW, BW, WW, BB
};

int main() {
  int position, run_order;
  int mode = MODE_INIT;

  while (1) {
    LED(run_order%4);
    switch (mode) {
    case MODE_INIT:
      mode = task_init(&run_order);
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
      break;
    }
  }
  return 0;
}

int is_sensor_Black(unsigned char ch) {
  return (ADRead(ch) > 200) ? 1 : 0;
}

int get_position() {
  return (is_sensor_Black(0) << 1 | is_sensor_Black(1));
}

void run_motor(int* param) {
  Mtr_Run_lv(param[1], -param[0], 0, 0, 0, 0);
  Wait(1);
}

int task_init(int* run_order) {
  Init(60);
  *run_order = 0;
  return MODE_OP;
}

int task_op() {
  return (!getSW()) ? MODE_OP : MODE_READ;
}

int task_read(int* run_order, int* position) {
  *position = get_position();
  return (*position != order_preset[*run_order]) ? MODE_RUN : MODE_SHIFT;
}

int task_run(int run_order, int position) {  
  run_motor(param_list[run_order][position]);
  return MODE_READ;
}

int task_shift(int* run_order) {
  (*run_order)++;
  return (param_list[*run_order] != NULL) ? MODE_RUN : MODE_ED;
}

int task_ed() {
  Mtr_Run_Lv(0, 0, 0, 0, 0, 0);
  return MODE_INIT;
}
