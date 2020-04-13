#include <iostream>
#include <numeric>

using ll = long long;
using namespace std;
using ld = long double;

#define rep(i, n) for (i = 0; i < (ll)n; ++i)
#define all(x) begin(x), end(x)

int main()
{
  ll K;
  cin >> K;
  ll ans = 0;
  ll a, b, c;
  rep(a, K) {
    rep(b, K) {
      rep(c, K) {
        ans += gcd(gcd(a, b), c);
      }
    }
  }
  cout << ans << endl;
  return 0;
}
