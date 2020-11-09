from collections import defaultdict

N, M = map(int, input().split())
road = defaultdict(list)

for _ in range(M):
    a, b = map(int, input().split())
    road[a].append(b)
    road[b].append(a)

a = [N in road[c] for c in road[1]]
print("POSSIBLE" if any(a) else "IMPOSSIBLE")

