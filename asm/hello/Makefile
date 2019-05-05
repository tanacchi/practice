a.out: hello.o
	ld hello.o

hello.o: hello.s
	nasm -g -f elf64 hello.s

clean:
	rm hello.o a.out
