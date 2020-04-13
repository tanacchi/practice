a = map(int, input().split())
a = int(list(a)[0])


#  for a in range(100, 1000):

ans = 'No'
while a > 1:
    #  print(f"a = {a}  : ", end='')
    if a % 10 == 7:
        ans = 'Yes'
        break
    a /= 10
    a = int(a)
print(ans)

