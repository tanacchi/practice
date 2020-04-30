#include <bits/stdc++.h>

using namespace std;

bool is_prime(unsigned int N)
{
  for (auto i{2}; i <= sqrt(N); ++i)
  {
    if (N % i == 0) return false;
  }
  return true;
}

int main()
{
  unsigned int N;
  cin >> N;

  auto ans = is_prime(N) ? "YES" : "NO";
  cout << ans << endl;

  return 0;
}
