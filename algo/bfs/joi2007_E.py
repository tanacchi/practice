import sys
from queue import Queue
from copy import deepcopy
from pprint import pprint


def bfs(start, goal, field):
    pass


H, W, N = map(int, input().split())

milestone_list = {}
field = []

for y in range(H):
    row = []
    for x, ch in enumerate(input()):
        if ch == 'S':
            milestone_list[0] = (x, y)
            row.append([True, H+W+1])
            continue
        try:
            num = int(ch)
            milestone_list[num] = (x, y)
            row.append([True, H+W+1])
        except ValueError:
            row.append([ch != 'X', H+W+1])
    field.append(row)

pprint(field)
pprint(milestone_list)

next_goal = 1
dist = 0
while next_goal in milestone_list:
    sx, sy = milestone_list[next_goal-1]
    gx, gy = milestone_list[next_goal]
    dist += bfs((sx, sy), (gx, gy), field)
    next_goal += 1

print(dist)
