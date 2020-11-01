import math

N, M, X = map(int, input().split())
C = []
A = []
for _ in range(N):
    c, *a = map(int, input().split())
    C.append(c)
    A.append(a)

bitmap = 0b01
min_cost = math.inf
while bitmap <= 0b1 << (N + 1):
    bitarray = [0b1 << i & bitmap != 0b0 for i in range(N)]

    cost = sum([C[i] for i in range(N) if bitarray[i]])
    books = [A[i] for i in range(N) if bitarray[i]]
    scores = [sum([a[m] for a in books]) for m in range(M)]
    # print(f"{bitmap:b}:\tbooks:{books}, score:{scores}")
    is_ok = all(map(lambda s: s >= X, scores))
    min_cost = min(min_cost, cost) if is_ok else min_cost
    bitmap += 1

print(min_cost if min_cost is not math.inf else -1)
