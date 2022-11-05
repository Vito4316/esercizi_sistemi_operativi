#include <stdio.h>

#ifndef MY_STRING_H
#define MY_STRING_H

typedef struct s_string* string; 

string string_init();
string string_initfrom(string s);
int string_free(string v);
int string_append(string s, char* c);
int string_cpy(string* s, char* c);
void string_fprint(string s, FILE* f);
void string_print(string s);

#endif