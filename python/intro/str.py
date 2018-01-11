drink = 'IceTea!'
yaju = drink * 5

print(yaju)
for i in range(-len(drink), len(drink)):
    print(drink[i] + '\b')


iee = drink[0::2]
print(iee)

reverse = drink[-1::-1]
print(reverse)

tea_list = yaju.split("!")
print(tea_list)

coffee_list = tea_list
for elem in coffee_list:
    elem.replace('Tea', 'Coffee')
print(coffee_list)
