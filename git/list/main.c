#include<stdio.h>
#include"list.h"

int main()
{
	list head1 = NULL;

	head1 = list_insert_tail(head1, 10);
	head1 = list_insert_tail(head1, 10);
	
	list_print(head1);

	list_free(head1);
	return 0;
}