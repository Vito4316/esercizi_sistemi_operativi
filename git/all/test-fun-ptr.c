#include <stdio.h>
#include <unistd.h>
#include <math.h>

/*
 * Below, an example of a macro which usually work to return the
 * length of an array by dividing the size of the array over the size
 * of the first element
 */
#define ARRAY_LEN(v) (sizeof(v)/sizeof(v[0]))

/*
 * Function that multiply a floating point number by 2, by adding
 * one to the representation of the exponent.
 */
double my_mul2(double x)
{
	unsigned long * p;
	
	p = (unsigned long *)&x;
	*p += 0x0010000000000000;  /* Adding one to the exponent */
	return x;
}

int main()
{
	/*
	 * Array of pointer to functions.  Each funtion has an input
	 * as double and produce a double as output
	 */
	double  (* vec_fun[])(double) ={sin,log10,my_mul2};
	int i;
	double in_dbl;

	printf("Enter a floating point number\n");
	scanf("%lf", &in_dbl);

	for (i=0; i<ARRAY_LEN(vec_fun); i++) {
		printf("\tvec_fun[%i](%f) = %f\n", i,
		       in_dbl, vec_fun[i](in_dbl));
	}
	printf("Addresses of pointers to functions\n");
	for (i=0; i<ARRAY_LEN(vec_fun); i++) {
		printf("\tvec_fun[%i] = %p\n", i, vec_fun[i]);
	}
	printf("View the memory mapping by\n");
	printf("\tcat /proc/%i/maps\n", getpid());
	printf("\nPress Ctrl+C to finish\n");
	pause();

	return 0;
}


	
