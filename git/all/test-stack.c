#include <stdio.h>
#include <string.h>

/*
 * 
 */


/*
 * Print n bytes in memory, starting from the address p.
 */
void dump_mem(const void * p, unsigned int n);

#define PARAM ((unsigned long)4)


/*
 * Trivial function that returns the same integer passed as parameters
 * after a couple of recursive calls. Recursive calls are used to
 * build up the stack with return address, passed parameters. At the last call,
 * that is when n == 0, the stack content is printed. If ALTER_STACK is defined,
 * then the stack content is overwritten to alter then the control flow
 */
long print_stack(long n)
{
	if (n==0) {
		dump_mem(&n, 256);
#ifdef ALTER_STACK
		/*
		 * memcpy copies n bytes (3rd parameter) from a source
		 * address (2nd parameter) to  a destination address 1
		 * * (1st). By copying data as follows onto the stack,
		 * we change the return  address. BY WRITING SOME DATA
		 * WE CHANGE THE EXECUTION FLOW!!!
		 */
		printf("\n%p\n", &n+2+PARAM*4);
		memcpy(&n+2, &n+2+PARAM*4, 40);
		dump_mem(&n, 256);
#endif
		return 0;
	} else {
		return 1+print_stack(n-1);
	}
}

int main()
{
	long in_stack_var=0x0123456789abcdef;
	
	printf("Invoked print_stack(%lu)\n", PARAM);
	printf("Returned value\n%lu\n", print_stack(PARAM));
}

void dump_mem(const void * p_in, unsigned int n)
{
	unsigned int i;
	char *p;

	p = (char *)p_in;
	/* if the last hex digit of p is not 0... */
	if ((long)p & 0xF) {
		/* 
		 * ...need to print some heading space
		 *
		 * (void *)((long)p & -15) is
		 *    the address p with last hex digit set = 0x0
		 */
		printf("(%p)", (void *)((long)p & -15));
		for (i=0; i<((long)p & 0xF); i++) {
			printf("   ");
		}
	}
	/* printing 16 bytes per row */
	for (i=0; i<n; i++, p++) {
		/* print the address at the begin of each row */
		if (!(((long)p & 0xF))) {
			printf("(%p)", p);
		}
		/* print the byte */
		printf(" %02X", (unsigned char)*p);
		/* new line if last byte of the row */
		if (((long)p & 0xF) == 0xF) {
			printf("\n");
		}
	}
	printf("\n\n");
}
