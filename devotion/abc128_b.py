from collections import defaultdict

N = int(input())
spot_map = defaultdict(list)
for i in range(N):
    s, p = input().split()
    spot_map[s].append((i+1, int(p)))

spot_map = sorted(spot_map.items())

for _, city_items in spot_map:
    city_items = sorted(city_items, key=lambda x: x[1], reverse=True)
    [print(city[0]) for city in city_items]
