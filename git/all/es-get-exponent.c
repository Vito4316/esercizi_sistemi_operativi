/*
 * Si scriva un programma che:
 * 
 * 1. legga un double da tastiera,
 *
 * 2. estragga l'esponente della sua rappresentazione in floating
 * point secondo lo Standard IEEE 754-1985
 *
 * 3. stampi tale esponente in decimale.

 * IMPORTANTE:  Per  massimizzare  l'apprendimento, si  raccomanda  di
 * leggere  la  soluzione  proposta  soltanto *dopo*  aver  provato  a
 * risolvere il problema autonomamente.
 */

#include <stdio.h>
#include <stdlib.h>
#define STRLEN 80

/* Mask to extract the exponent */
#define EXP_MASK_INT 0x7FF00000
/* Potition of the LSB bit of the exponent over 4 bytes */
#define LSB_POS 20
/* Exponent bias according to IEEE 754-1985 standard */
#define EXP_BIAS   1023

int main()
{
	char s[STRLEN];
	double f;
	int * p_int, exp_f;
	
	if (sizeof(int) != 4 || sizeof(double) != 8) {
		printf("Assuming sizeof(int) = 4, sizeof(double) = 8\n");
		printf("Instead  sizeof(int) = %d, sizeof(double) = %d\n",
			(int)sizeof(int), (int)sizeof(double));
		printf("Plz, modify the code accordingly\n");

		return 0;
	}
	
	/* Read the string and convert it to double  */
	printf("Enter a floating number\n");
	fgets(s, sizeof(s), stdin);
	f = atof(s);

	/* 
	 * Setting p_int to point to f: by doing so the bits of f can
	 * be interpreted as integers 
	 */
	p_int = (int *)&f;
	/* Get the most significant int */
	exp_f = p_int[1];
	/* Keep only the exponent and set all other bits to zero */
	exp_f &= EXP_MASK_INT;
	/* Shifting the exponent */
	exp_f >>= LSB_POS;
	/* Subtracting the bias */
	exp_f -= EXP_BIAS;

	printf("The exponent of the floating-point binary representation of\n");
	printf("%f\nis\n%d\n", f,exp_f);
	
	return 0;
}
