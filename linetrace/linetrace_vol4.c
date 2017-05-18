#include "lpc13xx.h"
#include "gpio.h"
#include "vs-wrc103.h"
#include "ixbus.h"

typedef struct run_script_t {
  int next_sign;
  // func-pointer
  const enum Sign {
  }; 
} Script;

typedef struct machine_status_t {
  int run_order;
  int position;
  // func-pointer
} Status;

/*

  init (threshold, order->script)

  write

  check position

  compare

  set 

  run

*/

/*

  INPUT : sesor(avarage)

  JUDGE : WW, WB, BW, BB, W*, B*, *W, *B, **

  OUTPUT : motor

*/

/*

WW : 0001 (0x1)

WB : 0010 (0x2)

BW : 0100 (0x4)

BB : 1000 (0x8)

WB|WW = 0011 (0x3)

BW|WB|WW = 0111 (0x7) = ~BB

*/

void run_motor(short left, short right);

void run_motor(short left, short right) {
  Mtr_Run_lv(right, -left, 0, 0, 0, 0);
}

int main(int argc, char** argv) {

  const unsigned short main_circle = 60;
  Init(main_circle);

  Script script;
  Status status;
  
  while (1) {
    status = update();
    status.run();
  }
}
