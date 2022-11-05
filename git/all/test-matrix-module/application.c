#include <stdio.h>
#include "matrix.h"


int main()
{
	struct mat * m1, *m2, *m3;

	/* Read two matrices */
	m1 = mat_read_alloc();
	m2 = mat_read_alloc();
	/* Compute the matrix product */
	m3 = mat_mul(m1, m2);
	/* Print the product */
	printf("The product between\n");
	mat_print(m1);
	printf("and\n");
	mat_print(m2);
	printf("is\n");
	mat_print(m3);
	/* Free memory */
	mat_free(m1);
	mat_free(m2);
	mat_free(m3);
}
