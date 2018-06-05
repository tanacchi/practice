#include <iostream>

class Singleton {
public:
  Singleton(const Singleton&) = delete;
  Singleton(Singleton&&) = delete;
  Singleton& operator=(const Singleton&) = delete;
  Singleton& operator=(Singleton&&) = delete;
  static Singleton& getInstance()
  {
    static Singleton instance;
    return instance;
  }
  const std::string getString()
  {
    return "I am Singleton.";
  }
private:
  Singleton() = default;
  ~Singleton() = default;
};

int main(int argc, char** argv)
{
  std::string ss{Singleton::getInstance().getString()};
  std::cout << ss << std::endl;
  return 0;
}
