R, C = map(int, input().split())
sy, sx = map(int, input().split())
gy, gx = map(int, input().split())
c = []
for _ in range(R):
    c.append(input())

q = [(sy - 1, sx - 1, 0)]
while q:
    y, x, cnt = q.pop(0)
    if (y, x) == (gy - 1, gx - 1):
        print(cnt)
        break
    elif not (0 <= y < R and 0 <= x < C) or c[y][x] == '#':
        continue
    for step_y, step_x in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
       q.append((y + step_y, x + step_x, cnt + 1)) 