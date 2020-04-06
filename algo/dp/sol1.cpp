#include <iostream>
#include <array>
#include <algorithm>

int main()
{
  const std::size_t W{5}, H{4};
  std::array<std::array<std::size_t, W+1>, H+1> dp{};

  dp[0][0] = 1;
  for (std::size_t r{0}; r <= H; ++r)
  {
    for (std::size_t c{0}; c <= W; ++c)
    {
      if (r != 0ul) dp[r][c] += dp[r-1][c];
      if (c != 0ul) dp[r][c] += dp[r][c-1];
    }
  }
  std::cout << dp[H][W] << std::endl;

  return 0;
}
