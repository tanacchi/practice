from collections import defaultdict

N = int(input())
A = list(map(int, input().split()))

ahi = {}
count = 0
for i in range(1, N + 1):
    a = A[i - 1]
    if a in ahi and ahi[a] == i:
        count += 1
    ahi[i] = a

print(count)
