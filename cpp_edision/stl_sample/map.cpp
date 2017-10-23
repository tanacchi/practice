#include <iostream>
#include <map>

int main()
{
  std::map<char, int> map{};
  for (int i = 0; i < 'z'-'a'+1; ++i)
    map.insert(std::pair<char, int>{'a'+i, i+1});

  for (int i = 0; i < 'z'-'a'+1; ++i)
    std::cout << static_cast<char>('z'-i)<< ' ' << map.at('z'-i) << std::endl;
  return 0;
}
