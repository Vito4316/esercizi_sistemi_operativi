#include <stdio.h>

int main() {
	int x = 0;
	
	typeof(x) y = 10;
	
	printf("%d\n", y);
}
