CFLAGS= -std=c89 -pedantic

run: main
	./main

main: liblist.a main.o
	gcc $(FLAGS) main.o -llist -L. -o main

liblist.a: list.o
	ar -crs liblist.a list.o