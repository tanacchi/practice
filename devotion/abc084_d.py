from copy import deepcopy


def gen_2017_like(limit):
    p = [1 for _ in range(limit+1)]
    p[0] = p[1] = 0

    # prime?
    for i in range(2, len(p)):
        if not p[i]: continue
        else:
           for j in range(i*2, limit+1, i):
               p[j] = 0

    a = deepcopy(p)

    # like 2017?
    for i in range(len(a)):
        target = int((i+1)/2)
        if p[i] and p[target]:
            continue
        else:
            a[i] = 0
    return a



N = int(input())
R = []
L = []

for i in range(N):
    l, r = map(int, input().split())
    R.append(r)
    L.append(l)

limit = max(R)
sum_list = gen_2017_like(limit)
S = [0]*len(sum_list)
for i, e in enumerate(sum_list[1:]):
    S[i+1] = S[i] + e

for l, r in zip(L, R):
    ans = S[r] - S[l-1]
    print(ans)
