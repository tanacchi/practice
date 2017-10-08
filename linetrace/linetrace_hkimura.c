#include "lpc13xx.h"
#include "gpio.h"
#include "vs-wrc103.h"
#include "ixbus.h"

const short maxPower = 0x7fff;

enum Condition {
  WW = 0x1 << 0,
  WB = 0x1 << 1,
  BW = 0x1 << 2,
  BB = 0x1 << 3
};

typedef struct {
  unsigned int condition;
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
  return ((get_sensor(0) > threshold[0]) << 1) | (get_sensor(1) > threshold[1]);
}

// =========================== Run functions ===================================

static void no_action(int position)
{
  LED(3);
  run_motor(0, 0);
}

static void ge_straight(int position)
{
  run_motor(maxPower, maxPower);
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
  
  while (1) {
    position = get_position(threshold);
    if (0x1 << position & status.script[sequence].condition) ++sequence;
    status.script[sequence].run(position);
  }
  return 0;
}

/* 
   =========================================================

   void BuzzerSet(unsigned char pitch, unsigned char vol);
   pitch : 0 ~ 255 (255 is most low-sound)
   vol   : 0 ~ 128

   void BuzzerStart();
   void BuzzerStop();

   =========================================================

   unsigned char getSW();
   0 -> off
   1 -> on

   =========================================================
*/
