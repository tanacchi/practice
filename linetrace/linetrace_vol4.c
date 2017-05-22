#include "lpc13xx.h"
#include "gpio.h"
#include "vs-wrc103.h"
#include "ixbus.h"

#define MAIN_CYCLE 60

enum Sign {
  WW = 0x1 << 0,
  WB = 0x1 << 1,
  BW = 0x1 << 2,
  BB = 0x1 << 3
};

typedef struct {
  int condition;
  void (*run)(int);
} Script;

typedef struct {
  int order;
  int position;
  const int* const threshold;
  const Script* const script;
} Status;

static inline void run_motor(short left, short right) {
  Mtr_Run_lv(right, -left, 0, 0, 0, 0);
}

const int* get_threshold() {
  int buff[2][2] = { {0, 0}, {0, 0} };
  for (int i = 0; i < 2; i++) {
    LED(i+1);
    while (!getSW()) ;
    for (int j = 0; j < 10; j++) buff[i][j%2] += ADRead(j%2);
    while (getSW()) ;
    Wait(100);
  }
  static int dist[2];
  for (int i = 0; i < 2; i++) dist[i] = (buff[0][i]/5 + buff[1][i]/5) / 2;
  return dist;
}

void wait_start_switch() {
  LED(3);
  while (!getSW()) ;
  LED(0);
  while (getSW()) ;
  Wait(100);
}

int get_sensor(unsigned char ch) {
  int sum = 0;
  for (int i = 0; i < 3; i++) sum += ADRead(ch);
  return sum / 3;
}

static inline int get_position(const int* threshold) {
  return (((get_sensor(0) > threshold[0]) << 1)|(get_sensor(1) > threshold[1]));
}

void update(Status* status) {
  status->position = get_position(status->threshold);
  if (!((0x1 << status->position)&(status->script[status->order].condition))&0xf) status->order++;
}

// ==================== Running pattern =========================================

void twin_trace(int position) {
  static const short param[][2] = {
    { 10000, 10000 },
    { 10000, 0     },
    { 0    , 10000 },
    { 10000, 10000 }
  };
  run_motor(param[position][0], param[position][1]);
}

void twin_tight(int position) {
  static const short param[][2] = {
    { 10000, 10000 },
    { 10000,-5000  },
    { -5000, 10000 },
    { 10000, 10000 }
  };
  run_motor(param[position][0], param[position][1]);
}

void no_motion(int position) {
  run_motor(0, 0);
}

void go_straight(int position) {
  run_motor(10000 , 10000);
}

void twist(int position) {
  static const  short param[][2] = {
    { 10000, 10000 },
    { 0,    -10000 },
    {-10000, 0     },
    { 10000, 10000 }
  };
  run_motor(param[position][0], param[position][1]);
}

void edge_right(int position) {
  static const  short param[][2] = {
    { 0,     10000 },
    { 10000, 0     },
    { 0,     10000 },
    { 10000, 0     }
  };
  run_motor(param[position][0], param[position][1]);
}

void edge_left(int position) {
  static const  short param[][2] = {
    { 10000, 0     },
    { 10000, 0     },
    { 0,     10000 },
    { 0,     10000 }
  };
  run_motor(param[position][0], param[position][1]);
}

void tward_left(int position) {
  run_motor(-10000, 10000);
}

void tward_right(int position) {
  run_motor(10000,-10000);
}

// =============================================================================

int main(int argc, char** argv) {

  Init(MAIN_CYCLE);

  const Script script[] = {
    {~BB, go_straight },  // 0 0 : box
    { BB, go_straight },  // 0 1 : start line
    {~BB, twin_trace  },  // 1 0 : S road
    {~WW, go_straight },  // 1 1 : enter 1st condenser
    { WW, go_straight },  // 0 0 : between 1st condenser
    {~BB, twist       },  // 0 1 : on line of 1st condenser
    { BB, go_straight },  // 1 0 : exit 1st condenser
    {~BB, twin_tight  },  // 1 1 : road to diode
    { BB, tward_left  },  // 0 0 : in diode
    {~WW, go_straight },  // 0 1 : escape center
    { WW, tward_right },  // 1 0 : turn right
    {~WW, edge_left   },  // 1 1 : exit diode
    {~BB, edge_right  },  // 0 0 : road to 2nd condenser
    { BB, go_straight },  // 0 1 : enter 2nd condenser
    { WW, go_straight },  // 1 0 : between 2nd condenser
    {0x0, no_motion   }
  };

  Status status = {
    0,
    0x0,
    get_threshold(),
    script
  };

  wait_start_switch();
  while (1) {
    LED(status.order%4);
    update(&status);
    status.script[status.order].run(status.position);
  }

  return 0;
}
