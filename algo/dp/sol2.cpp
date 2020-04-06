#include <iostream>
#include <array>
#include <algorithm>


const std::array<int, 5> ws = {3, 4, 1, 2, 3};
const std::array<int, 5> ps = {2, 3, 2, 3, 6};
const int maxw {10};

int knapsack(std::size_t n, int w)
{
  if (w > maxw) return -10000;
  if (n >= 5) return 0;
  return std::max(knapsack(n + 1, w),
                  knapsack(n + 1, w + ws[n]) + ps[n]);
}

int main()
{
  std::cout << knapsack(0, 0) << std::endl;

  return 0;
}
