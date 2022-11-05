#include <stdio.h>

int main()
{
	char * p = 0;
	int i=0;
	int var=-1;
	
	/* Printing all memory we can read */
	p = (char *) &var;
	
	printf(" i:%p\n p:%p\n&p:%p\n", &i, p, &p);
	
	/* No stopping condition. The OS will stop us */
	for(i=0;; i++) {
		printf("(%2li) %02hhX p+i:%p\n", i, p[i], p+i);
		if(&p[i] == &i) {
			printf("p: %p, i: %p\n", &p[i], &i);
			break;
		}
		p[i] = 0;
	}
}
