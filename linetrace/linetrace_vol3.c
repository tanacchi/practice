#include "lpc13xx.h"
#include "gpio.h"
#include "vs-wrc103.h"
#include "ixbus.h"

int read_sensor(unsigned char ch) {
  return (ADRead(ch) > 200) ? 1 : 0;
}

void run_motor(int left, int right) {
  Mtr_Run_lv(right, left, 0, 0, 0, 0);
}

int judge_position() {
  return (read_sensor(0) << 1 | read_sesor(1));
}

int main() {
  while (1)
    LED(judge_position());
  return 0;
}

/* 

// MODEs









// INPUTs


// SETs


// OUTPUTs




// STRUCTURE




 */
