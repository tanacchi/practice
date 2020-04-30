#include <bits/stdc++.h>


using namespace std;

using ui = unsigned long long;

ui get_digit(ui N)
{
  float n = (float)N;
  ui counter = 0;
  while (n >= 1.0)
  {
    n /= 10.0;
    ++counter;
  }
  return counter;
}

int main()
{
  ui N;
  cin >> N;

  ui min_digit = 10;
  for (auto i{1}; i <= sqrt(N); ++i)
  {
    if (N % i == 0)
    {
      const ui A = i, B = (ui)(N / i);
      // cout << A << ' ' << B << endl;
      const auto digit = get_digit(max(A, B));
      min_digit = min(min_digit, digit);
    }
  }
  cout << min_digit << endl;

  return 0;
}
