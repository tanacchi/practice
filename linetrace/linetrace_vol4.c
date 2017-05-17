#include "lpc13xx.h"
#include "gpio.h"
#include "vs-wrc103.h"
#include "ixbus.h"

typedef struct  script_t {
  unsigned short position;
  int next_sign;
  
} Script;

/*

INIT

READ

UPDATE

RUN

*/


/*

INPUT : sesor

JUDGE : WW, WB, BW, BB, W*, B*, *W, *B, **

OUTPUT : motor

*/
