#include <stdio.h>
#include <stdlib.h>
#define SIZE 7

int main() {
	char string[100];
	int vect[SIZE];
	
	for(int i = 0; i < SIZE; i++) {
		fgets(string, sizeof(string), stdin);
		vect[i] = strtol(string, NULL, 0);
	}
	
	for(int i = 0; i < SIZE; i++) {
		if(vect[i] % 2 == 1)
			printf("%d", vect[i]);
	}
	
	for(int i = 0; i < SIZE; i++) {
		if(vect[i] % 2 == 0)
			printf("%d", vect[i]);
	}
	
}
