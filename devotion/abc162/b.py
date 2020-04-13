a = int(input())

ans = sum(filter(lambda i: i % 3 != 0 and i % 5 != 0, range(1, a+1)))
print(ans)
