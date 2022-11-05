#ifndef LIST_H
#define LIST_H

typedef struct node* list;

list list_insert_ordered(list p, int val);
list list_cat(list before, list after);
list list_insert_head(list p, int val);
list list_insert_tail(list p, int val);
void list_print(list p);
void list_free(list p);

#endif