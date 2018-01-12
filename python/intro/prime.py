def isPrime(num):
    limit = int(num)
    for i in range(2, limit):
        if ((limit % i) == 0): return False
    return True

def getListOfPrime(limit):
    prime_list = []
    for i in range(2, limit):
        if (isPrime(i)): prime_list.append(i)
    return prime_list
    
num = input('Plaese put a number\n>')
if (not num.isdigit()):
    print('Please put a number!!')
    exit()
else:
    limit = int(num)


prime_list = getListOfPrime(limit)
print(prime_list)

with open('prime_list.tmp.txt', mode = 'w', encoding = 'utf-8') as f:
    f.write(str(prime_list) + '\n')
print('See you~~')
