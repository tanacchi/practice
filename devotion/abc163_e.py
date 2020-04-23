N = int(input())
A = map(int, input().split())

A = sorted(enumerate(A), key=lambda x: x[1], reverse=True)
dp = [[0]*(N+1) for _ in range(N+1)]

for n, (from_i, a) in enumerate(A):
    for j in range(n + 1):
        dp[n+1][j+1] = max(dp[n+1][j+1], dp[n][j] + a*(from_i - j))
        dp[n+1][j] = max(dp[n+1][j], dp[n][j] + a*(N - (n - j) - 1 - from_i))

print(max(dp[N]))
