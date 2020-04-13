N = int(input())
S = input()

Rs = len([i for i, ch in enumerate(S) if ch == 'R'])
Gs = len([i for i, ch in enumerate(S) if ch == 'G'])
Bs = len([i for i, ch in enumerate(S) if ch == 'B'])

ans = Rs * Gs * Bs

if Rs == 0 or Gs == 0 or Bs == 0:
    print(0)
    exit(1)

for i in range(N):
    for j in range(i+1, N):
        k = 2*j - i
        if k >= N: continue
        if S[i] != S[j] and S[j] != S[k] and S[k] != S[i]:
            ans -= 1
print(ans)
