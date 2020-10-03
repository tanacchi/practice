from copy import deepcopy


N = int(input())
happies = []

for _ in range(N):
    a, b, c = map(int, input().split())
    happies.append([a, b, c])

dp = [[0, 0, 0] for _ in range(N)]
dp[0] = deepcopy(happies[0])

for i in range(1, N):
    dp[i][0] = happies[i][0] + max(dp[i-1][1], dp[i-1][2])
    dp[i][1] = happies[i][1] + max(dp[i-1][2], dp[i-1][0])
    dp[i][2] = happies[i][2] + max(dp[i-1][0], dp[i-1][1])

print(max(dp[N-1]))
