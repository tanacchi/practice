#include "lpc13xx.h"
#include "gpio.h"
#include "vs-wrc103.h"
#include "ixbus.h"

enum Mode {
  MODE_INIT,
  MODE_READ,
  MODE_RUN,
  MODE_SHIFT,
  MODE_STOP
};

void run_motor(int left, int right) {
  Mtr_Run_lv(right, -left, 0, 0, 0, 0);
}

int (*line_trace[])(int Pos) = {
  line_control(Pos, 10000, 0),
  over_line(Pos, 10000, 0),
  line_control(Pos, 10000, 0),
  over_line(Pos, 1000, 0),
  line_control(Pos, 10000, -10000),
  over_line(Pos, 10000, 5000),
  line_control(Pos, 10000, 5000),
  over_line(Pos, 10000, 0),
  line_control(Pos, 10000, 0),
  over_line(Pos, 10000, 0),
  NULL  
};

int line_control(int Pos, int HIGH, int LOW) {
  switch (Pos) {
  case 0: run_motor( HIGH,  HIGH); break;
  case 1: run_motor( HIGH,   LOW); break;
  case 2: run_motor(  LOW,  HIGH); break;
  case 3: run_motor( HIGH,  HIGH); return MODE_SHIFT;
  }
  return MODE_READ;
}

int over_line(int Pos, int HIGH, int LOW) {
  switch (Pos) {
  case 0: run_motor( HIGH,  HIGH); return MODE_SHIFT;
  case 1: run_motor(  LOW, -HIGH); break:
  case 2: run_motor(-HIGH,   LOW); break;
  case 3: run_motor( HIGH,  HIGH); break;
  }
  return MODE_READ;
}

int main() {
   Mode mode = 0;
   int Position;
   int runOrder = 0;
   
   while (1) {
     switch (mode) {
     case MODE_INIT:
       mode = task_init(60);
       break;
     case MODE_READ:
       mode = task_read(&Position);
       break;
     case MODE_RUN:
       mode = task_run(Position, runOrder);
       break;
     case MODE_SHIFT:
       mode = task_shift(&runOrder);
       break;
     case MODE_STOP:
       LED(3);
       run_motor(0, 0);
       return 0;
     }
   }
   return 0;
}

Mode task_init(const unsigned short MainCycle) {
  Init(MainCycle);
  return MODE_READ;
}

Mode task_read(int* position) {
  int isLeftBlack = read_sensor(0), isRightBlack = read_sensor(1);
  *position = judge_position(isLeftBlack, isRightBlack);
  return MODE_RUN;
}

Mode task_shift(int* runOrder) {
  (*runOrder)++;
  return (&line_trace[*runOrder] != NULL) ? MODE_READ : MODE_STOP;
}

Mode task_run(int Position, int runOrder) {
  return line_trace[runOrder](Position);
}

int read_sensor(unsigned char ch) {
  return (ADRead(ch) > 200) 1 : 0;
}

int judge_position(int isLeftBlack, int isRightBlack) {
  if (!isLeftBlack && !isRightBlack) return 0;
  if (!isLeftBlack &&  isRightBlack) return 1;
  if ( isLeftBlack && !isRightBlack) return 2;
  if ( isLeftBlack &&  isRightBlack) return 3;
}
