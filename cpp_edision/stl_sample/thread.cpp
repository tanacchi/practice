#include <iostream>
#include <thread>
#include <exception>
#include <vector>
#include <mutex>

class Class {
public:
  void func() {
    std::vector<std::thread> threads{};
    for (int i{0}; i < 10; ++i) threads.push_back(std::thread{&Class::greeting, this, i});
    for (auto& elem : threads) elem.join();
  }
  void greeting(int n)
  {
    //    std::unique_lock<std::mutex> lock{get_lock()};
    std::cout << "Hi, " << n << std::endl;
  }
  std::unique_lock<std::mutex> get_lock()
  {
    return std::unique_lock<std::mutex>{mutex_};
  }
private:
  std::mutex mutex_;
};


int main()
{
  Class obj{};
  obj.func();
  return 0;
}
