import sys
from queue import Queue

R, C   = map(int, input().split())
sy, sx = map(int, input().split())
gy, gx = map(int, input().split())
field = [[[ch == '.', R*C+1] for ch in row[:-1]] for row in sys.stdin]

px, py = sx-1, sy-1
gx, gy = gx-1, gy-1

q = Queue()

field[py][px][0] = False
field[py][px][1] = 0

q.put((px, py))

while not q.empty():
    base_x, base_y = q.get()
    for vx, vy in [(1, 0), (0, 1), (-1, 0), (0, -1)]:
        if not (0 <= base_x+vx < C and 0 <= base_y+vy < R):
            continue
        px, py = base_x+vx, base_y+vy
        cell = field[py][px]
        if not cell[0]:
            continue
        field[py][px][0] = False
        field[py][px][1] = min(field[base_y][base_x][1] + 1, field[py][px][1])
        q.put((px, py))

# for row in field:
#  for ch, dist in row:
#    print("\t" + str(dist), end="")
#  print()
print(field[gy][gx][1])
