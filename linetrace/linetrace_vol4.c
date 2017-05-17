#include "lpc13xx.h"
#include "gpio.h"
#include "vs-wrc103.h"
#include "ixbus.h"

typedef struct run_script_t {
  int next_sign;
  // func-pointer
} Script;


typedef struct machine_status_t {
  int position;
  // func-pointer
} Status;

/*

INIT (threshold, order->script)

UPDATE (sensor, func)

RUN

*/


/*

INPUT : sesor(avarage)

JUDGE : WW, WB, BW, BB, W*, B*, *W, *B, **

OUTPUT : motor

*/

int main(int argc, char** argv) {

Init(60);
}