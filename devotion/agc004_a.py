L = list(map(int, input().split()))
if any(map(lambda x: x % 2 == 0, L)):
    print(0)
else:
    m = max(L)
    n = L.pop(L.index(m))
    print(L[0] * L[1])
