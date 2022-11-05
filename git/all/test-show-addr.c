#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



/* Variables allocated over the BSS */
int int_BSS;
char v_BSS[] = "array_in_BSS";

/* 
 * Only the pointer p_BSS is allocated to the BSS, the pointed string may be elsewhere
 */
char * p_BSS = "pointer_in_BSS";  

void my_fun()
{
	int stack_var;
	static int static_var;
	
	/* Printing addresses of variables over the stack of my_fun */
	printf("\nVariables of the my_fun function)\n");
	printf("  &stack_var:   %p (where is it?)\n", (void *)&stack_var);
	printf("  &static_var:  %p (where is it?)\n", (void *)&static_var);
}

int main()
{
	int int_stack;
	int * p_var_heap;

	/* Now view the memory mapping */
	printf("\nView the memory mapping by launching the command\n");
	printf("  less /proc/%d/maps\n", getpid());

	/* Just to wait for the user */
	printf("\nPress ENTER when done\n");
	fgets((char *)p_var_heap, sizeof(*p_var_heap), stdin);

	/* Printing addresses of variables over BSS */
	printf("\nGlobal variables: allocated over the BSS\n");
	printf("  &int_BSS:     %p\n", (void *)&int_BSS);
	printf("  v_BSS:        %p\n", (void *)v_BSS);
	printf("  &p_BSS:       %p\n", (void *)&p_BSS);
	printf("  p_BSS:        %p (where is it?)\n", (void *)p_BSS);
	printf("  v_BSS:        %s\n", v_BSS);
	v_BSS[0] = 'X';
	printf("  v_BSS (mod):  %s\n", v_BSS);
	printf("  p_BSS:        %s\n", p_BSS);
	p_BSS[0] = 'X';
	printf("  p_BSS (mod):  %s\n", p_BSS);
	
	/* Printing addresses of variables over the stack of main */
	printf("\nVariables over the stack (of the main function)\n");
	printf("  &int_stack:   %p\n", (void *)&int_stack);
	printf("  &p_var_heap:  %p\n", (void *)&p_var_heap);

	my_fun();

	/* Printing addresses of variables over the heap */
	printf("\nVariables over the heap (allocated by malloc)\n");
	p_var_heap = malloc(sizeof(*p_var_heap));
	printf("  p_var_heap:   %p\n", (void *)p_var_heap);

	/* Printing addresses of code */
	printf("\nAddress of code\n");
	printf("  main:         %p\n", (void *)main);

	/* Dynamically allocate memory must be freed */
	free(p_var_heap);
	return 0;
}
  
  
