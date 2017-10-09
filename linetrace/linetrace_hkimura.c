#include "lpc13xx.h"
#include "gpio.h"
#include "vs-wrc103.h"
#include "ixbus.h"

const short maxPower = 0x7fff;

enum {Left, Right};

enum Condition {
  WW = 0x1 << 0,
  WB = 0x1 << 1,
  BW = 0x1 << 2,
  BB = 0x1 << 3
};

typedef struct {
  enum Condition condition;
  void (*run)(int);
} Script;

static inline void run_motor(short left, short right)
{
  Mtr_Run_lv(right, -left, 0, 0, 0, 0);
}

unsigned int get_sensor(unsigned char ch)
{
  unsigned int sum = 0;
  for (int i = 0; i < 4; ++i) sum += ADRead(ch);
  return sum * 0.25;
}

unsigned int get_position(const unsigned int* const threshold)
{
  return ((get_sensor(Left) > threshold[Left]) << 1) | (get_sensor(Right) > threshold[Right]);
}

void wait_switch()
{
  LED(3); while (!getSW()) ;
  LED(0); while (getSW()) ;
  Wait(100);
}

// =========================== Run functions ===================================

void no_action(int position)
{
  LED(3);
  run_motor(0, 0);
}

void go_straight(int position)
{
  run_motor(maxPower, maxPower);
}

void traceLR(int position)
{
  static const short param[][2] = {
    { maxPower, maxPower},
    { maxPower,        0},
    {        0, maxPower},
    { maxPower, maxPower}
  };
  rum_motor(param[position][Left], param[position][Right]);
}

// =============================================================================

int main(int argc, char** argv)
{
  unsigned int sequence = 0;
  unsigned int position = 0x0;
  const unsigned int* const threshold = {200, 200};
  const Script script[] = {
    {0xf, no_motion}
  };  
  const unsigned short mainCycle = 60;
  Init(mainCycle);

  wait_switch();
  while (1) {
    position = get_position(threshold);
    if (0x1 << position & script[sequence].condition) ++sequence;
    script[sequence].run(position);
  }
  return 0;
}
