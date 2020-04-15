import math

sx, sy, gx, gy, T, V = map(int, input().split())
n = int(input())
coords = []
for _ in range(n):
    x, y = map(int, input().split())
    coords.append((x, y))

start, goal = (sx, sy), (gx, gy)

def calc_powered_length(src, dest):
    return math.sqrt((src[0] - dest[0])**2 + (src[1] - dest[1])**2)

def can_go(checkpoint):
    length1 = calc_powered_length(start, checkpoint)
    length2 = calc_powered_length(checkpoint, goal)
    return (length1 + length2) <= T*V

ans = 'YES' if any(map(can_go, coords)) else 'NO'
print(ans)
