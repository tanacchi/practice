#include <iostream>
#include <array>
#include <algorithm>


int main()
{
  std::array<int, 3> bases;
  std::vector<std::array<int, 3>> expr_history{};
  std::size_t latest_added_index{3};
  int latest_value{1ul};
  std::size_t count{1ul};
  std::size_t k;

  for (auto& b : bases)
  {
    std::cin >> b;
  }
  std::cin >> k;

  while (count < k)
  {
    std::size_t min_index{3ul};
    int min_value{1000000};
    for (std::size_t i{0ul}; i < 3; ++i)
    {
      int tmp{i == latest_added_index ? latest_value : latest_value/bases[latest_added_index]};
      if (min_value > tmp*bases[i])
      {
        min_value = tmp*bases[i];
        min_index = i;
      }
    }
    std::cout << "index: " << min_index << ", value: " << min_value << std::endl;
    latest_added_index = min_index;
    latest_value = min_value;
    ++count;
  }
  std::cout << latest_value << std::endl;

  return 0;
}
