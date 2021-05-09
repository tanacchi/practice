N, K = map(int, input().split())
A = map(int, input().split())
B = map(int, input().split())

diff = sum(map(lambda x: abs(x[0] - x[1]), zip(A, B)))
print("Yes" if K >= diff and (K - diff) % 2 == 0 else "No")