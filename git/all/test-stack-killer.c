#include <stdio.h>


void kill_stack(void * p)
{
	static int count_invocations = 1;
	int v[100];
	
	/* 
	 * p is an address over at the base of the stack (passed as parameter)
	 *
	 * &p is the address of the current parameter. &p becomes
	 * smaller and smaller as the number of recursive invocations
	 * increases
	 */ 
	printf("num invocations: %6d. Used bytes on stack: %lu\n",
		count_invocations++, (unsigned long)p-(unsigned long)&p);
	kill_stack(p);
}


int main()
{
	int var_on_stack;

	/* Si passa un indirizzo grande (in basso) nello stack */
	kill_stack(&var_on_stack);
}
