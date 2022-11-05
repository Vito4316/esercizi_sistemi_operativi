#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"


struct mat * mat_read_alloc()
{
	unsigned int i, j;
	struct mat * in;
	
	in = malloc(sizeof(*in));
	printf("Enter number of rows: \n");
	scanf("%i", &(in->rows));
	printf("Enter number of columns: \n");
	scanf("%i", &(in->cols));
	in->data = malloc(sizeof(*in->data)*in->rows*in->cols);
	printf("Enter the matrix data: \n");
	for(i=0; i<in->rows; i++) {
		for(j=0; j<in->cols; j++) {
			scanf("%lf", in->data+j+i*in->cols);
		}
	}
	return in;
}

void mat_print(struct mat * m)
{
	unsigned int i, j;

	for(i=0; i<m->rows; i++) {
		for(j=0; j<m->cols; j++) {
			printf("%f ", m->data[j+i*m->cols]);
		}
		printf("\n");
	}
	
	
}

void mat_free(struct mat * in)
{
	free(in->data);
	free(in);
}

struct mat * mat_mul(const struct mat * a, const struct mat * b)
{
	unsigned int i, j, k;
	struct mat * new;
	double *new_row_p, *a_row_p;

	/* Safety checks: a and b cannot be NULL */
	if (!(a && b)) {
		fprintf(stderr, "NULL pointers passed. This is bad\n");
		return NULL;
	}
	
	/* Check number of rows and columns */
	if (a->cols != b->rows) {	
		fprintf(stderr,
			"Columns of a (%d) should be equal to rows of b (%d)\n",
			a->cols, b->rows);
		return NULL;
	}

	/* Allocate the new matrix (and set values to zeros) */
	new = malloc(sizeof(*new));
	new->rows = a->rows;
	new->cols = b->cols;
	new->data = calloc(new->rows * new->cols, sizeof(*new->data));
	/* pointer to the i-th row of the a matrix */
	a_row_p = a->data;
	/* pointer to the i-th row of the new matrix */
	new_row_p = new->data;
	/* loop on rows of new */
	for(i = 0; i < new->rows; i++) {
		/* loop on columns of new */
		for(j = 0; j < new->cols; j++) {
			/* computing new->data[i][j] */
			for (k = 0; k < a->cols; k++) {
				new_row_p[j] +=
					a_row_p[k] * b->data[j+k*b->cols];
			}
		}
		/* update the row pointer of a to the next row */
		a_row_p += a->cols;
		/* update the row pointer of new to the next row */
		new_row_p += new->cols;
	}
	return new;
}
