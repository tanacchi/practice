import bisect
import math
from copy import deepcopy

N, M = list(map(int, input().split()))
H = list(map(int, input().split()))
W = list(map(int, input().split()))


def calc_diff2(a):
    it = iter(a)
    splited = zip(it, it)
    return [y - x for x, y in splited]


def calc_diff(a):
    it = iter(a)
    splited = zip(it, it)
    return sum([y - x for x, y in splited])


H.sort()
f = deepcopy(H)
front = calc_diff2(f)

b = deepcopy(H)
b.insert(0, 0)
back = calc_diff2(b)

min_diff = math.inf
for w in W:
    it = bisect.bisect_left(H, w)
    s_front = front[:it]
    if it % 2 == 0:
        s_mid = H[it - 1] - w
    else:
        s_mid = w - H[it]
    s_back = back[it + 1:]
    diff = sum(s_front) + s_mid + sum(s_back)
    print(f"it: {it}, f: {s_front}, m: {s_mid}, b: {s_back}, diff: {diff}")
    min_diff = min(min_diff, diff)
print()
print(min_diff)
