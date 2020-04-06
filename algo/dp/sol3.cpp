#include <iostream>
#include <array>

int main()
{
  const std::array<int, 5> ws = {3, 4, 1, 2, 3};
  const std::array<int, 5> ps = {2, 3, 2, 3, 6};
  const std::size_t maxw{10};
  std::array<std::array<int, 6>, maxw+1> dp{};

  for (std::size_t i{0ul}; i < 5; ++i)
    for (std::size_t j{0ul}; j <= maxw; ++j)
      if (j + ws[i] <= maxw)
      {
        dp[i+1][j+ws[i]] = std::max(dp[i+1][j+ws[i]], dp[i][j] + ps[j]);
      }
  std::cout << dp[4][maxw] << std::endl;

  return 0;
}
