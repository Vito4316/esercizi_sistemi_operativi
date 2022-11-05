#include <stdio.h>

/*
 * Try to compile it by
 * 
 *   gcc -std=c89 -Wpedantic test-struct.c -o test-struct
 *
 * and by
 *
 *   gcc -DDBL_VAR -std=c89 -Wpedantic test-struct.c -o test-struct
 *
 * to check the difference between the amount of allocated memory.
 * Finally, also try to compile by defining CHARS_LAST
 */


struct my_struct {
#ifndef CHARS_LAST
	char c1[3];      /* if no macro defined */
#endif
#ifdef DBL_VAR
	double var;
#else
	int var;         /* if no macro defined */
#endif	
#ifdef CHARS_LAST
	char c1[3];
#endif
	char c2;         /* if no macro defined */
};


/*
 * Print n bytes in memory, starting from the address p.
 */
void dump_mem(const void * p, unsigned int n);


int main()
{
#ifndef CHARS_LAST
	struct my_struct my_s = {"AB", -1, '1'}; /* if no macro defined */
#else
	struct my_struct my_s = {-1, "AB", '1'};
#endif

	printf("sizeof(my_s)       = %2d (at %p)\n",
		(int)sizeof(my_s), (void *)&my_s);
	printf("  sizeof(my_s.c1)  = %2d (at %p); my_s.c1  = \"%s\"\n",
	       	(int)sizeof(my_s.c1), (void *)&my_s.c1, my_s.c1);
	printf("  sizeof(my_s.var) = %2d (at %p); my_s.var = %d\n",
	       	(int)sizeof(my_s.var),(void *)&my_s.var, (int)my_s.var);
	printf("  sizeof(my_s.c2)  = %2d (at %p); my_s.c2  = \'%c\'\n",
	       	(int)sizeof(my_s.c2), (void *)&my_s.c2, my_s.c2);
	printf("Memory content at &my_s\n");
	dump_mem(&my_s,sizeof(my_s));
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
