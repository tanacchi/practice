N = int(input())
nums = []
for _ in range(N):
    nums.append(list(map(int, input().split())))


def get_sum(n):
    a, b = n
    return ((b + 1) * b) // 2 - ((a - 1) * a) // 2


ans = sum([get_sum(n) for n in nums])
print(ans)
