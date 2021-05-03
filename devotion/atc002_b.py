N, M, P = map(int, input().split())

def pow_mod(k):
    if k == 0:
        return 1
    elif k % 2 == 0:
        tmp = pow_mod(k // 2)
        return (tmp**2) % M
    else:
        return (N * pow_mod(k-1)) % M

print(pow_mod(P))
