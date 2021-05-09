def is_ok(s):
    count_open = 0
    count_close = 0
    for i, c in enumerate(s):
        if c == '1':
            count_open += 1
        else:
            count_close += 1
        if count_open < count_close:
            return False
    return True


N = int(input())
if N % 2 != 0:
    exit(0)

cnt = 2**N

while cnt > 1:
    cnt -= 1
    binary = bin(cnt)[2:].zfill(N)
    if binary.count("0") != binary.count("1"):
        continue
    if is_ok(binary):
        print(binary.replace("1", "(").replace("0", ")"))
    
    