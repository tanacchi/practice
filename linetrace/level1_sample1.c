#include "lpc13xx.h"
#include "gpio.h"
#include "vs-wrc103.h"
#include "ixbus.h"

int main() {
  const unsigned short MainCycle = 60;
  Init(MainCycle);

  while (1) {
    if (ADRead(0) < 200) {
      if (ADRead(1) < 200) {
        Mtr_Run_lv(10000, -10000, 0, 0, 0, 0);
        Wait(1);
      }
      else {
        Mtr_Run_lv(    0, -10000, 0, 0, 0, 0);
        Wait(1);
      }
    }
    else {
      if (ADRead(1) < 200) {
        Mtr_Run_lv(10000,      0, 0, 0, 0, 0);
        Wait(1);
      }
      else {
        Mtr_Run_lv(10000, -10000, 0, 0, 0, 0);
        Wait(1);
      }
    }
  }
  return 0;
}
