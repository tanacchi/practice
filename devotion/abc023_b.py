N = int(input())
S = input()

div, mod = divmod((N - 1) // 2, 3)
T = 'bca' * div + 'b' + 'cab' * div
if mod >= 1:
    T = 'a' + T + 'c'
if mod >= 2:
    T = 'c' + T + 'a'
print(3 * div + mod if T == S else -1)
