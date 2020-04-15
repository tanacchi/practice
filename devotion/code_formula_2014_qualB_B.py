N = int(input())

mode = 'odd'
switch = lambda old_mode: 'even' if old_mode == 'odd' else 'odd'

memory = {'odd': [], 'even': []}

while N > 0:
    memory[mode].append(N%10)
    mode = switch(mode)
    N //= 10

odd_sum  = sum(memory['odd'])
even_sum = sum(memory['even'])
print(f"{even_sum} {odd_sum}")
