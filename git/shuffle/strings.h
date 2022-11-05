#include "mystring.h"

#ifndef STRINGS_H
#define STRINGS_H

typedef struct s_strings* strings;

strings strings_init();

int strings_free(strings v);
int strings_putcharp(strings val, char* string);
int strings_putstring(strings val, string s);
void swap_i(int* v, int a, int b);
int* shuffled_vect(int size);
void print_v(int* v, int size);
void strings_shuffle(strings v);
void strings_fprint(strings v, FILE* f);
void strings_print(strings v);
void trim_newline(char* v);
strings strings_fillfromfile(FILE* file);

#endif