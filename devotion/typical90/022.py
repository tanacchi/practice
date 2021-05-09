import math

def gcd3(a, b, c):
    return math.gcd(math.gcd(a, b), c)


A, B, C = map(int, input().split())
gcd = gcd3(A, B, C)
ans = (A // gcd) + (B // gcd) + (C // gcd) - 3
print(ans // 1)