#include <iostream>
#include <thread>
#include <exception>
#include <future>
#include <vector>
#include <mutex>

class Class {
public:
  // Thread sample 1
  void func1() {
    std::vector<std::thread> threads{};
    for (int i{0}; i < 10; ++i) threads.push_back(std::thread{&Class::greeting, this, i});
    for (auto& elem : threads) elem.join();
  }
  void greeting(int n)
  {
    std::unique_lock<std::mutex> lock{get_lock()};
    std::cout << "Hi, " << n << std::endl;
  }

  std::unique_lock<std::mutex> get_lock()
  {
    return std::unique_lock<std::mutex>{mutex_};
  }
  // Thread sample 2
  void func2() {
    std::vector<std::future<int> > ans{};
    for (int i{0}; i < 10; ++i) ans.push_back(std::async(std::launch::async, &Class::get_num, this));
    for (auto& elem : ans) std::cout << "num : " << elem.get() << std::endl;
  }
  int get_num()
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::unique_lock<std::mutex> lock{get_lock()};
    return ++num_;
  }

private:
  std::mutex mutex_;
  int num_{0};
};


int main()
{
  Class obj{};
  obj.func1();
  obj.func2();
  return 0;
}
