#include <stdio.h>

/* c1 is global variable, allocated over the BSS */
int c1 = 100;

void func(int ** p_c1, int ** p_c2, int ** p_c3) {
	/* c2 is allocated over the stack */ 
	int c2 = 10;
	/* c3 is allocated over the BSS, but visible only within the
	 * function */
	static int c3 = 1;
	
	printf("func: c1=%2d,   c2=%2d,   c3=%2d\n", c1, c2, c3);
	c1++;
	c2++;
	c3++;
	/* Used to return the addresses of c1, c2, c3, outside the function */
	*p_c1 = &c1;
	*p_c2 = &c2;
	*p_c3 = &c3;
}

int main(int argc, char *argv[])
{
	int i;
	int *p_c1, *p_c2, *p_c3;
	
	for (i = 0; i < 5; i++) {
		func(&p_c1, &p_c2, &p_c3);
	}
	
	/* We know the addresses of c1, c2, c3. We can modify them */
	*p_c1 += 1000;
	*p_c2 += 1000;
	*p_c3 += 1000;
	
	/* Now printing them again */
	printf("Printing after adding 1000 to all\n");
	func(&p_c1, &p_c2, &p_c3);

	
	return 0;
}
