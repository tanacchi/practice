#include <bits/stdc++.h>

using ll = std::int_fast64_t;

int main()
{
    ll R, C, sy, sx, gy, gx;

    std::cin >> R >> C >> sy >> sx >> gy >> gx;
    --sy;
    --sx;
    --gy;
    --gx;

    std::vector<std::string> c(R);
    for (int i{0}; i < R; ++i)
        std::cin >> c[i];
    
    std::vector<std::pair<ll, ll>> gone;

    std::queue<std::tuple<ll, ll, ll>> q;
    q.push(std::make_tuple(sy, sx, 0));

    std::array<std::pair<ll, ll>, 4> directions{
        std::make_pair(0, 1),
        std::make_pair(1, 0),
        std::make_pair(0, -1),
        std::make_pair(-1, 0)
    };

    while (! q.empty())
    {
        ll y, x, cnt;
        std::tie(y, x, cnt) = q.front();
        q.pop();
        const auto found = std::find(
            std::begin(gone),
            std::end(gone),
            std::make_pair(y, x)
            );
        if (found != std::end(gone))
            continue;

        gone.emplace_back(std::make_pair(y, x));

        if (y == gy && x == gx)
        {
            std::cout << cnt << std::endl;
            break;
        }
        else if (c[y][x] == '#')
        {
            continue;
        }
        for (auto& dir : directions)
        {
            ll next_y = y + dir.first, next_x = x + dir.second;
            q.push(std::make_tuple(next_y, next_x, cnt + 1));
        }
    }
    return 0;
}