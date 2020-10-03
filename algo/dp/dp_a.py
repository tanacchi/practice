import math


N = int(input())
H = [int(h) for h in input().split()]


dp = [math.inf] * N
dp[0] = 0
dp[1] = abs(H[0] - H[1])

for i in range(2, N):
    dp[i] = min(dp[i-1] + abs(H[i] - H[i-1]),
                dp[i-2] + abs(H[i] - H[i-2]))

print(dp[N-1])
