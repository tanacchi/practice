import re


S = input().split()
N = int(input())
T = [input().replace('*', '.') for _ in range(N)]

for t in map(re.compile, T):
    for i, s in enumerate(S):
        if t.fullmatch(s):
            S[i] = "*" * len(s)

for i, s in enumerate(S):
    end = ' ' if i  != len(S) - 1 else '\n'
    print(s, end=end)
