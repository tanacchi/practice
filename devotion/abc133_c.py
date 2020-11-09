L, R = map(int, input().split())

if R - L > 2019:
    print(0)
else:
    X = []
    for x in range(L, R+1):
        for y in range(x+1, R+1):
            X.append((x * y) % 2019)
    print(min(X))
