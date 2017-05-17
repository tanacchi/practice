#include "lpc13xx.h"
#include "gpio.h"
#include "vs-wrc103.h"
#include "ixbus.h"

typedef struct  script_t {
  unsigned short position;
  int next_sign;
  // func-pointer
} Script;

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