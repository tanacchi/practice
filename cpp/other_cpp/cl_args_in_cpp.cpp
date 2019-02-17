#include <iostream>
#include <vector>
#include <algorithm>

int main(int argc, char** argv)
{
  std::vector<std::string> args{argv, argv+argc};
  std::for_each(args.begin(), args.end(), [](auto arg){ std::cout << arg << std::endl; });

  return 0;
}
