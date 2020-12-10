from copy import deepcopy

N = int(input())
A = [0] + list(map(int, input().split())) + [0]
diffs = sum(abs(A[j - 1] - A[j]) for j in range(1, N + 1))
print(A, diffs)

for i in range(1, N):
    ans = diffs + abs(A[i - 1] + A[i + 1]) \
                - abs(A[i - 1] - A[i]) \
                - abs(A[i] - A[i + 1])
    print(ans)
