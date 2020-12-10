N = int(input())
prev = int(input())
for _ in range(N - 1):
    a = int(input())
    if a == prev:
        print("stay")
    elif a >= prev:
        print(f"up {a - prev}")
    else:
        print(f"down {prev - a}")
    prev = a
