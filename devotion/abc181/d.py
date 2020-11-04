import collections
import itertools

S = list(input())
counter = collections.Counter(S)
S = []
for k, v in counter.items():
    S.extend([k] * min(v, 3))
if len(S) < 3:
    for n in itertools.permutations(S):
        n = int("".join(n))
        if n % 8 == 0:
            print("Yes")
            exit(0)
    print("No")
    exit(0)

for n in itertools.permutations(S, r=3):
    n = int("".join(n))
    if n % 8 == 0:
        print("Yes")
        exit(0)
print("No")
