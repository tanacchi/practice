#include <iostream>

void func()
{
  std::cout << "Not ns" << std::endl;
}

namespace ns {
  void func()
  {
    std::cout << "func in ns" << std::endl;
  }
  void f()
  {
    ::func();
  }
};

int main(int argc, char** argv)
{
  ns::f();
  return 0;
}
