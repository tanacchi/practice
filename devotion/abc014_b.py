n, X = map(int, input().split())
A = map(int, input().split())

bought_map = list(map(int, format(X, 'b')))
bought_map.reverse()
ans = sum(map(lambda a: a[0]*a[1], zip(A, bought_map)))

print(ans)
