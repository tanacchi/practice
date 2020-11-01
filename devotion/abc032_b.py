s = input()
k = int(input())

if len(s) < k:
    print(0)
else:
    ans = [s[i:i + k] for i in range(0, len(s) - k + 1)]
    ans = len(set(ans))
    print(ans)
