#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

int main() {
	char string[] = "Ciao a tutti!";
	
	for(char i = 1; i > 0; i++) {
		int num = 0;
		for(int j = 0; j < sizeof(string); j++) {
			if(string[j] == i)
				num++;
		}
		
		if(num > 0)
			printf("%d, %c\n", num, i);
	}
}
