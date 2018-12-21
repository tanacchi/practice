#include <iostream>
#include <functional>

class C
{
  public:
    void hello()
    {
      std::cout << "Hello, "  << name_ << std::endl;
    }
  
    void set_name(std::string name)
    {
      name_ = name;
    }

    std::string name_{};
};

int main()
{
  C c{};
  
  c.set_name("Tanaka");

  std::function<void(void)> func = std::bind(&C::hello, &c);
  
  c.set_name("Daiki");

  func();  // Hello, Daiki

  return 0;
}
