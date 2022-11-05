#include <stdio.h>
#include <stdlib.h>

int sfunct(int n) {
	if(n%2 == 0)
		return n/2;
	else 
		return n*3+1;
}

void printfunction(int n) {
	if(n < 1)
		return;
	do {
		printf("%d\n", n);
		
		n = sfunct(n);
	} while(n != 1);
}

int main(int argc, char** argv) {
	int n = atoi(argv[1]);
	printfunction(n);
}
