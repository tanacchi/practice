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
  std::function<void(void)> func = std::bind(&C::hello, &c);
  
  c.set_name("Tanaka");
  c.set_name("Daiki");

  // 呼び出し時の内部状態を反映してくれるみたい
  func();  // Hello, Daiki

  return 0;
}
