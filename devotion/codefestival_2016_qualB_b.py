N, A, B = map(int, input().split())
S = input()

A_count = B_count = 0
for i, s in enumerate(S):
    if s == 'a' and A_count + B_count < A + B:
        print('Yes')
        A_count += 1
    elif s == 'b' and A_count + B_count < A + B and B_count < B:
        print('Yes')
        B_count += 1
    else:
        print('No')

