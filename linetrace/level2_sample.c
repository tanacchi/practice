#include "lpc13xx.h"
#include "gpio.h"
#include "vs-wrc103.h"
#include "ixbus.h"

int main() {
  const unsigned short MainCycle = 60;
  Init(MainCycle);

  int i = 0;
  
  switch (i) {
    
  case 0:
    if (ADRead(0) < 200 && ADRead(1) < 200) Mtr_Run_lv(10000, -10000, 0, 0, 0, 0);
    if (ADRead(0) < 200 && ADRead(1) > 200) Mtr_Run_lv(    0, -10000, 0, 0, 0, 0);
    if (ADRead(0) > 200 && ADRead(1) < 200) Mtr_Run_lv(10000,      0, 0, 0, 0, 0);
    if (ADRead(0) > 200 && ADRead(1) > 200) i++;
    Wait(1);
    break;
    
  case 1:
    if (ADRead(0) < 200 && ADRead(1) < 200) i++;
    else Mtr_Run_lv(10000, -10000, 0, 0, 0, 0);
    Wait(1);
    break;
    
  case 2:
    if (ADRead(0) < 200 && ADRead(1) < 200) Mtr_Run_lv(10000, -10000, 0, 0, 0, 0);
    if (ADRead(0) < 200 && ADRead(1) > 200) Mtr_Run_lv(    0, -10000, 0, 0, 0, 0);
    if (ADRead(0) > 200 && ADRead(1) < 200) Mtr_Run_lv(10000,      0, 0, 0, 0, 0);
    if (ADRead(0) > 200 && ADRead(1) > 200) i++;
    Wait(1);
    break;
    
  case 3:
    if (ADRead(0) < 200 && ADRead(1) < 200) i++;
    else Mtr_Run_lv(10000, -10000, 0, 0, 0, 0);
    Wait(1);
    break;
    
  case 4:
    Mtr_Run_lv(0, 0, 0, 0, 0, 0);
    break;

  }
  return 0;
}
