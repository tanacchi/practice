#include "lpc13xx.h"
#include "gpio.h"
#include "vs-wrc103.h"
#include "ixbus.h"

static const short MaxPower = 0x7FFF;

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

typedef struct {
  unsigned int sequence;
  unsigned int position;
  const unsigned int* const threshold;
  const Script* const script;
} Status;

int main(int argc, char** argv)
{
  Init(60);
  return 0;
}

/* 
   =========================================================

   void Mtr_Run_lv(short mt1, short mt2, 0, 0, 0, 0);
   free    : 0 or 0x8000(-32768)
   cw_max  : 0x7FFF(32767)
   ccw_max : 0x8001(-32767)

   =========================================================

   void LED(unsigned char LedOn);
   0 -> 0 0
   1 -> 0 1
   2 -> 1 0
   3 -> 1 1

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

   unsigned int AdRead(unsigned char ch);
   ch     : 0 ~ 7
   return : 0 ~ 1023

   =========================================================
*/
