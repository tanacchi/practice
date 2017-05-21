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

typedef struct run_script_t {
  int condition;
  void (*run)(int);
} Script;

typedef struct machine_status_t {
  int order;
  int position;
  const int* const threshold;
  const Script* const script;
} Status;

void run_motor(short left, short right);
const int* set_threshold();
int get_position(const int* const threshold);
void update(Status* status);

void run_motor(short left, short right) {
  Mtr_Run_lv(right, -left, 0, 0, 0, 0);
}

const int* set_threshold() {
  int buff[2][2] = { {0, 0}, {0, 0} };
  for (int i = 0; i < 2; i++) {
    LED(i+1);
    while (!getSW()) ;
    for (int j = 0; j < 20; j++) buff[i][j%2] += ADRead(j%2);
    while (getSW()) ;
    Wait(100);
  }
  int dist[2];
  for (int i = 0; i < 2; i++) dist[i] = (buff[0][i] + buff[1][i]) / 2;
  return dist;
}

void wait_start_switch() {
  while (!getSW()) ;
  while (!getSW()) ;
  Wait(100);
}

int get_position(const int* threshold) {
  return (((ADRead(0) > threshold[0]) << 1)|(ADRead(1) > threshold[1]));
}

void update(Status* status) {
  status->position = get_position(status->threshold);
  if (!((0x1 << status->position)&(status->script[status->order].condition))) status->order++;
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

// =============================================================================

int main(int argc, char** argv) {

  Init(MAIN_CYCLE);

  const Script const script_list[] = {
    {~BB, go_straight },
    { BB, go_straight },
    {~BB, twin_trace  },
    {~WW, go_straight },
    { WW, go_straight },
    {~BB, twist       },
    { BB, go_straight },
    {~BB, twin_tight  },
    {~WW, no_motion   }
  };

  Status status = {
    0,
    0x0,
    set_threshold(),
    script_list
  };

  wait_start_switch();
  while (1) {
    LED(status.order%4);
    update(&status);
    status.script_list[status.order].run(status.position);
  }

  return 0;
}
