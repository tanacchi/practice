#include <iostream>

#define LED(n) LED ##n

int main()
{
  int LED1 = 1;
  int LED2 = 2;
  std::cout << LED(2) << std::endl;
  return 0;
}
