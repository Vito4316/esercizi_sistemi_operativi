#include "strings.h"
#include "mystring.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct s_strings {
    int size;
    int msize;
    string* s;
};

strings strings_init() {
    strings retval = malloc(sizeof(*retval));
    retval->msize = 1;
    retval->size = 0;
    retval->s = calloc(sizeof(*retval->s), 1);
    return retval;
}

int strings_free(strings v) {
    int i;
    for(i = 0; i < v->size; i++)
        string_free(v->s[i]);
    
    free(v);
}

int strings_putcharp(strings val, char* string) {
    if(val->size >= val->msize) {
        val->s = realloc(val->s, sizeof(*val->s)*val->msize*2);
        if(val->s == NULL) {
            val->size = 0;
            val->msize = 0;
            return -1;
        }
        val->msize*=2;
    }

    string_cpy(&val->s[val->size++], string);
    
    val->s[val->size] = NULL;
    return 1;
}

int strings_putstring(strings val, string s) {
    if(val->size >= val->msize) {
        val->s = realloc(val->s, sizeof(*val->s)*val->msize*2);
        if(val->s == NULL) {
            val->size = 0;
            val->msize = 0;
            return -1;
        }
        val->msize*=2;
    }

    val->s[val->size++] = string_initfrom(s);
    
    val->s[val->size] = NULL;
    return 1;
}

void swap_i(int* v, int a, int b) {
    int x = v[a];
    v[a] = v[b];
    v[b] = x;
}

int* shuffled_vect(int size) {
    int* vec = malloc(sizeof(*vec) * size);
    int i;

    for(i = 0; i < size; i++)
        vec[i] = i;

    srand(time(NULL));

    for(i = 0; i < size; i++)
        swap_i(vec, i, rand() % size);

    return vec;
}

void print_v(int* v, int size) {
    int i;
    for(i = 0; i < size; i++)
        printf("%d\n",v[i]);
}

void strings_shuffle(strings v) {
    void** pointers = malloc(sizeof(*v->s) * v->size);
    int* sh_arr = shuffled_vect(v->size);
    int i;
    memcpy(pointers, v->s, sizeof(*v->s) * v->size);

    for(i = 0; i < v->size; i++)
        v->s[i] = pointers[sh_arr[i]];

    free(pointers);
    free(sh_arr);
}

void strings_fprint(strings v, FILE* f) {
    int i = 0;
    for(; i < v->size; i++)
        string_fprint(v->s[i], f);
}

void strings_print(strings v) { 
    strings_fprint(v, stdout);
}

void trim_newline(char* v) {
    int i = 0;
    while(v[i] != 0) {
        if(v[i] == '\n')
            v[i] = 0;
        i++;
    }
}

strings strings_fillfromfile(FILE* file) {
    int size = (fseek(file, 0, SEEK_END), ftell(file));
    strings strs = strings_init();
    size_t buffsize = 0;
    char* buff = NULL;
    rewind(file);
    while(ftell(file) != size) {
        getline(&buff, &buffsize, file);
        trim_newline(buff);
        strings_putcharp(strs, buff);
    }
    free(buff);
    return strs;
}