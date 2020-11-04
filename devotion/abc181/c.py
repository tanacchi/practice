import itertools

N = int(input())

XY = []
for _ in range(N):
    x, y = list(map(float, input().split()))
    XY.append((x, y))


def on_line(a, b, c):
    if b[0] == a[0]:
        return c[0] == a[0]
    if c[0] == a[0]:
        return b[0] == c[0]
    if c[0] == b[0]:
        return b[0] == a[0]
    return (b[1] - a[1]) / (b[0] - a[0]) == (c[1] - b[1]) / (c[0] - b[0])


count = 0
for i, j, k in itertools.combinations([i for i in range(N)], 3):
    a, b, c = XY[i], XY[j], XY[k]
    if on_line(a, b, c):
        count += 1
print("Yes" if count else "No")
