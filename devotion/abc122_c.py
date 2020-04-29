N, Q = map(int, input().split())
S = input()
L = []
R = []

for _ in range(Q):
    l, r = map(int, input().split())
    L.append(l)
    R.append(r)

a = [0] * len(S)
for i, _ in enumerate(S[1:]):
    addition = 1 if S[i] + S[i+1] == 'AC' else 0
    a[i+1] = a[i] + addition

for l, r in zip(L, R):
    print(a[r-1] - a[l-1])
