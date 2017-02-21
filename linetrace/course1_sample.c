#include "lpc13xx.h"
#include "gpio.h"
#include "vs-wrc103.h"
#include "ixbus.h"

int main() {
  const unsigned short MainCycle = 60;
  Init(MainCycle);

  while (1) {
    if (ADRead(0) < 200 && ADRead(1) < 200) Mtr_Run_lv(10000, -10000, 0, 0, 0, 0);
    if (ADRead(0) < 200 && ADRead(1) > 200) Mtr_Run_lv(    0, -10000, 0, 0, 0, 0);
    if (ADRead(0) > 200 && ADRead(1) < 200) Mtr_Run_lv(10000,      0, 0, 0, 0, 0);
    if (ADRead(0) > 200 && ADRead(1) > 200) Mtr_Run_lv(10000, -10000, 0, 0, 0, 0);
  }
  return 0;
}



//   Mtr_Run_lv(right, -left, 0, 0, 0, 0);

// ADRead(ch) < THRESHOLD  <- white
