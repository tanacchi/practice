name = 'hiyori'
char_list = list(name)
print(char_list)

char_list.append('n')
print(char_list)

family = list(' tunekawa')
char_list.extend(family)
print(char_list)

del char_list[4:]
print(char_list)

hiyo = tuple(char_list)
print(hiyo)

h, i, y, o= hiyo
del h, i, y, o

del name

name = 't! a! n! a! k! a'.split('! ')
print(name)

name_set = set(name)
print(name_set)

name_set.add('d')
name_set.remove('a')
print(name_set)

val = name_set.pop()
print('popped char is ' + val)
print(name_set)

import random

num_list1 = [random.randint(0,9) for i in range(10)]
num_list2 = [random.randint(0,9) for i in range(10)]

num_set1 = set(num_list1)
num_set2 = set(num_list2)
print('======================')
print(num_set1)
print(num_set2)
print('======================')

print(num_set1 & num_set2)
print(num_set1 |num_set2)
print(num_set1 - num_set2)
print(num_set1 ^ num_set2)
