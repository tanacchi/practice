import math


N, K = map(int, input().split())
H = [int(h) for h in input().split()]


dp = [math.inf] * N
dp[0] = 0
dp[1] = abs(H[0] - H[1])

for i in range(2, N):
    dp[i] = min([dp[i-k] + abs(H[i] - H[i-k]) for k in range(1, K+1)])

print(dp[N-1])
