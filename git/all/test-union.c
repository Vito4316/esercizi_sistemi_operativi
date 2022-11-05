#include <stdio.h>

/*
 * Try to compile it by
 * 
 *   gcc -std=c89 -Wpedantic test-union.c
 *
 * and by
 *
 *   gcc -std=c89 -Wpedantic -DUSE_UNION test-union.c
 * 
 * What is the difference between the size of the data structure in
 * the two cases?
 *
 * At what address in memory are allocated the fields in the two
 * cases?
 */

#define SIGN_MASK (((unsigned long)~0 >> 1)+1)

#ifdef USE_UNION
#define TOP_STRING "***** USING union  *****"
union my_union_t {
#else
#define TOP_STRING "***** USING struct *****"
struct my_union_t {
#endif
	double f;
	unsigned long i;
	unsigned char lsb;
} var;

int main()
{
	var.f = 1.0;
	
	printf("%s\n", TOP_STRING);
	printf("  Value of var.f = %.10e\n  Value of var.i = 0x%016lX\n",
	       var.f, var.i);
	var.i ^= SIGN_MASK;  /* change the sign of the double */
	printf("Flipping the MSB of var.i\n");
	printf("  Value of var.f = %.10e\n  Value of var.i = 0x%016lX\n",
	       var.f, var.i);
	printf("  Value of least significant byte before division = 0x%02X\n",
	       var.lsb);
	var.f /= 5;
	printf("Dividing var.f by 5\n");
	printf("  Value of least significant byte after division = 0x%02X\n",
	       var.lsb);
	printf("sizeof(var) = %d\nsizeof(var.f) = %d\nsizeof(var.lsb) = %d\n",
	       (int)sizeof(var), (int)sizeof(var.f), (int)sizeof(var.lsb));
	printf("&var     = %p\n", (void *)&var);
	printf("&var.f   = %p\n", (void *)&var.f);
	printf("&var.i   = %p\n", (void *)&var.i);
	printf("&var.lsb = %p\n", (void *)&var.lsb);
}

