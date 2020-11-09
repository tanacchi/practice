N = int(input())
A = []
B = []
for _ in range(N):
    a, b = map(int, input().split())
    A.append(a)
    B.append(b)

def calc_addtion(a, b):
    div, mod = divmod(a, b)
    return b - mod if mod else 0

count = 0

for i in reversed(range(N)):
    count += calc_addtion(A[i]+count, B[i])
print(count)
