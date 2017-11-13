#include <array>
#include <iostream>
#include <vector>

#define metadefine(token, ...) \
  const std::array<char, sizeof #__VA_ARGS__> token {#__VA_ARGS__}; __VA_ARGS__;

metadefine(main_, int main(int argc, char** argv, char** env)
{
  for (int i{0}; env[i] != nullptr; ++i)
    std::cout << env[i] << std::endl;
  std::cout << main_.data() << std::endl;
  return 0;
});

