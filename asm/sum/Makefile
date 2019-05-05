a.out: sum.o
	ld sum.o

sum.o: sum.s
	nasm -f elf64 sum.s

clean:
	rm sum.o a.out
