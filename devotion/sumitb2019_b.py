N = int(input())

X = int(N / 1.08)

ans = ':('
for x in range(X-5, X+6):
    n = int(x * 1.08)
    if n == N:
        ans = x
        break
print(ans)
