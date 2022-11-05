#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

int main() {
	char string[100];
	int vect[SIZE];
	int vect1[SIZE];
	
	printf("%d", (int) sizeof(vect));
	
	for(int i = 0; i < SIZE; i++) {
		fgets(string, sizeof(string), stdin);
		vect[i] = strtol(string, NULL, 0);
	}
	
	for(int i = 0; i < SIZE; i++){
		int temp = 0;
		for(int j = i; j < SIZE; j++) 
			temp += vect[j];
		vect1[i] = temp;
	}
	
	for(int i = 0; i < SIZE; i++){
		printf("%d-", vect1[i]);
	}
}
