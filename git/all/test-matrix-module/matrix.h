#ifndef _MATRIX_H_
#define _MATRIX_H_

/*
 * Data structure of a matrix:
 *   - data is a pointer to the data (rows*cols)
 *   - rows is the number of rows of the matrix
 *   - cols is the number of columns of the matrix
 */
struct mat {
	double * data;
	int rows;
	int cols;
};


/*
 * Read from stdin:
 *   - number of rows
 *   - number of columns
 *   - data of the matrix
 * then allocate all the needed  data structures (in and in->data) and
 * store  the  input  data  accordingly.  Returns  a  pointer  to  the
 * allocated matrix
 */
struct mat * mat_read_alloc();

/*
 * Print the matrix *m
 */
void mat_print(struct mat * m);

/*
 * Free all the memory of in and the related data
 */
void mat_free(struct mat * in);

/*
 * Alloca una  nuova matrice e  la imposta con il  prodotto matriciale
 * fra le  due matrici a  e b. Il  puntatore alla nuova  matrice viene
 * ritornato.  Se le  dimensioni  non  consentono la  moltiplicazione,
 * mat_mul ritorna il puntatore NULL
 */
struct mat * mat_mul(const struct mat * a, const struct mat * b);

#endif   /* _MATRIX_H_ */
