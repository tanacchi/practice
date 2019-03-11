#include <iostream>

class Master
{
  public:
    Master(std::string name)
      : name{name}
    {
    }

    class Tool
    {
      public:
      void call(const Master&);
    };

    void call()
    {
      tool.call(*this);
    }

  private:
    std::string name;
    Tool        tool;
};

void Master::Tool::call(const Master& master)
{
  std::cout << "Master name : " << master.name << std::endl;
}

int main()
{
  Master master{"tanaka"};
  master.call();

  return 0;
}
