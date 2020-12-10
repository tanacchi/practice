from collections import Counter

N = int(input())
A = list(map(int, input().split()))

count = Counter(A)
s = [k for k, v in count.items() if v >= 4]
t = [k for k, v in count.items() if v >= 2]
if len(s) < 1 and len(t) < 2:
    print(0)
elif len(s) < 1:
    print(t[-1] * t[-2])
elif len(t) < 2:
    print(s[-1]**2)
else:
    print(max(t[-1] * t[-2], s[-1]**2))
