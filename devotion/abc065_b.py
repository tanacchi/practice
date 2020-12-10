N = int(input())
A = []
for _ in range(N):
    A.append(int(input()))

pos = 0
count = 0
while pos != 1:
    pos = A[pos] - 1
    count += 1
    if count > N:
        count = -1
        break
print(count)
