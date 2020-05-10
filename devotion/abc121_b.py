N, M, C = map(int, input().split())
B = list(map(int, input().split()))
As = []
for _ in range(N):
    A = map(int, input().split())
    As.append(A)

count = 0
for A in As:
    A = list(A)
    mapped = list(map(lambda x: x[0]*x[1], zip(A, B)))
    result = sum(mapped) + C
    cond = result > 0
    count = count+1 if cond else count
print(count)
