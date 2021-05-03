H, W = map(int, input().split())
C = []
start = []
for h in range(H):
    c = list(input())
    if 's' in c:
        start = (h, c.index('s'))
    C.append(c)

curr = list(start)
stack = [curr]

while stack:
    pos = stack.pop()
    y, x = pos[0], pos[1]
    if not (0 <= y < H and 0 <= x < W):
        continue
    target = C[y][x]
    if target == 'g':
        print("Yes")
        exit(0)
    elif target == '#':
        continue
    else:
        C[y][x] = '#'
        stack.extend([(y-1, x), (y+1, x), (y, x-1), (y, x+1)])

print("No")