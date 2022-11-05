FLAGS= -std=c89

run: shuffle
	./shuffle text
shuffle: mystring.o strings.o
	gcc $(FLAGS) mystring.o strings.o main.c -o shuffle