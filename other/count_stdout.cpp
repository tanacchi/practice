#include <iostream>

int main()
{
  for (std::size_t i{0}; i < 1000000; ++i)
  {
    std::cout << '\r' << i << std::flush;
  }
  return 0;
}
