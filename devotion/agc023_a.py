from collections import defaultdict


N = int(input())
A = map(int, input().split())
A = list(A)

S = [0]*(N+1)
S[0] = 0
for i in range(N):
    S[i+1] = S[i] + A[i]

sum_dict = defaultdict(int)
for s in S:
    sum_dict[s] += 1

ans = sum([n*(n-1)/2 for n in sum_dict.values()])
print(int(ans))
