N = int(input())
C, P = [], []
for _ in range(N):
    c, p = map(int, input().split())
    C.append(c)
    P.append(p)

Q = int(input())
L, R = [], []
for _ in range(Q):
    l, r = map(int, input().split())
    L.append(l)
    R.append(r)

point_map = [[0, 0]]

for c, p in zip(C, P):
    last = point_map[-1].copy()
    last[c-1] += p
    point_map.append(last)

for l, r in zip(L, R):
    sum1 = point_map[r][0] - point_map[l-1][0]
    sum2 = point_map[r][1] - point_map[l-1][1]
    print(sum1, sum2)
