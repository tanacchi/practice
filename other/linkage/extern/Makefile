a.out: main.o increment.o
	gcc main.o increment.o

main.o: main.c
	gcc -c main.c

increment.o: increment.c
	gcc -c increment.c

clean:
	rm *.o *.out
