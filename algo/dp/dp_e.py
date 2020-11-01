import math


N, W = map(int, input().split())
ws, vs = [], []
for _ in range(N):
    w, v = map(int, input().split())
    ws.append(w)
    vs.append(v)

dp = [[math.inf] * (W + max(ws) + 1) for _ in range(N+1)]

for i in range(1, N+1):
    for w in range(0, W+1):
        if ws[i-1] <= w:
            dp[i][w] = min(dp[i-1][w-ws[i-1]] + vs[i-1], dp[i-1][w])
        else:
            dp[i][w] = dp[i-1][w]

ans = len(dp[N]) - 1
ans = W
print(len(dp[N]))
print(dp[N])
while dp[N][ans] > W:
    ans -= 1
print(dp[N][ans])
