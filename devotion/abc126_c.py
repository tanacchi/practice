import math

N, K = map(int, input().split())
p = 0
for n in range(1, N+1):
    if n >= K:
        p += 1.0 / N
    else:
        k = math.ceil(math.log2((K - n) /n  + 1))
        p += math.pow(0.5, k) / N
print(p)
