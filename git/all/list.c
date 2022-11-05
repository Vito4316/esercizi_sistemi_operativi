#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node * next;   /* pointer to the same structure */
} node;

typedef node* list;

list list_insert_ordered(list p, int val);
list list_cat(list before, list after);
list list_insert_head(list p, int val);
list list_insert_tail(list p, int val);
void list_print(list p);
void list_free(list p);

int main()
{
	list head1 = NULL;

	head1 = list_insert_tail(head1, 10);
	head1 = list_insert_tail(head1, 10);
	
	list_print(head1);

	list_free(head1);
	return 0;
}

list list_insert_head(list p, int val)
{
	list new_el;

	new_el = malloc(sizeof(*new_el));
	new_el->value = val;
	new_el->next = p;

	return new_el;
}

void list_print(list p)
{
	if (p == NULL) {
		printf("Empty list\n");
		return;
	}
	printf("[%i]", p->value);
	for(; p->next!=NULL; p = p->next) {
		printf(" -> [%i]", p->next->value);
	}
	printf("\n");
}

void list_free(list p)
{
	if (p == NULL)
		return;

	list_free(p->next);
	free(p);
}

void node_insert_between(list left, list right, list mid) {
	left->next = mid;
	mid->next = right;
}

list list_init(int val, list next) {
	list ret_val = malloc(sizeof(*ret_val));
	ret_val->next = next;
	ret_val->value = val;

	return ret_val;
}

list list_insert_ordered(list p, int val) {
	list i = p;
	list j = p;
	list new_node = list_init(val, NULL);

	if(i == NULL)
		return new_node;

	if(val < i->value) 
		return list_insert_head(p, val);

	while(i != NULL && val > i->value) {
		j = i;
		i = i->next;
	}

	node_insert_between(j, i, new_node);

	return p;
}

list list_cpy(list _list) {
	list ret_val;
	list i;
	if(_list == NULL)
		return _list;
	 
	ret_val = list_init(_list->value, NULL);
	i = ret_val;
	_list = _list->next;

	while(_list != NULL) {
		i->next = list_init(_list->value, NULL);
		i = i->next;
		_list = _list->next;
	}

	return ret_val;
}

list list_cat(list before, list after) {
	list ret_val = list_cpy(before);
	list i = ret_val;

	if(i == NULL)
		return list_cpy(after);

	while(i->next != NULL) 
		i = i->next;
	
	i->next = list_cpy(after);

	return ret_val;
}

list list_insert_tail(list p, int val) {
	list i = p;

	if(p == NULL)
		return list_init(val, NULL); 

	while(i->next != NULL) 
		i = i->next;
	
	i->next = list_init(val, NULL);

	return p;
}