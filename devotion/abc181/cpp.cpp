#include <bits/stdc++.h>

using ll = long long;
using namespace std;
using ld = long double;

#define rep(i, n) for (i = 0; i < (ll)n; ++i)
#define all(x) begin(x), end(x)
#define printall(v) for_each(all(v), [](auto a){ cout << a << " "; })

ll calc_diff(vector<ll> a)
{
  const auto size = a.size();
  ll result = 0;
  for (ll i = 0l ; i < size - 1; i += 2)
    {
      result += a[i+1] - a[i];
    }
  return result;
}

int main()
{
  ll N, M;
  ll i;
  cin >> N >> M;
  vector<ll> H, W;
  rep(i, N) {
    ll a;
    cin >> a;
    H.emplace_back(a);
  }
  rep(i, M) {
    ll a;
    cin >> a;
    W.emplace_back(a);
  }
  sort(all(H));
  ll min_diff = 10000000000000;
  for (const auto w : W){
    auto A = H;
    auto it = lower_bound(A.begin(), A.end(), w);
    A.insert(it, w);
    auto diff = calc_diff(A);
    min_diff = min(min_diff, diff);
  }
  cout << min_diff << endl;
  return 0;
}
