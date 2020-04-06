from time import time


def fibo1(n):
    if n == 1 or n == 2: return 1
    return fibo1(n-1) + fibo1(n-2)

def fibo2(n):
    arr = [0 for _ in range(n+1)]
    arr[1] = 1
    for i in range(2, n+1):
        arr[i] = arr[i-1] + arr[i-2]
    return arr[n]

if __name__ == '__main__':
    start = time()
    print(fibo1(36), ", time: ", time() - start)
    start = time()
    print(fibo2(36), ", time: ", time() - start)
