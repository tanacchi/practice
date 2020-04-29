N = int(input())
X = map(int, input().split())
X = list(X)

head = min(X)
tail = max(X)

min_score = float('inf')
for p in range(head, tail+1):
    min_score = min(sum(map(lambda x: (x - p)**2, X)), min_score)

print(min_score)
