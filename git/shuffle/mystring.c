#include "mystring.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

struct s_string {
    int msize;
    int size;
    char* vect;
};

string string_init() {
    string retval = malloc(sizeof(*retval));
    retval->msize = 1;
    retval->size = 0;
    retval->vect = malloc(sizeof(*retval->vect));
    *retval->vect = '\0';
    return retval;
}

string string_initfrom(string s) {
    string retval = malloc(sizeof(*retval));
    retval->msize = s->msize;
    retval->size = s->size;
    retval->vect = malloc(sizeof(*retval->vect) * retval->msize);
    memcpy(retval->vect, s->vect, retval->msize);
    return retval;
}

int string_free(string v) {
    if(v != NULL)
        free(v->vect);
    free(v);
}

int string_append(string s, char* c) {
    int i;
    int len = strlen(c);

    if(s->size == s->msize) {
        s->vect = realloc(s->vect, sizeof(*s->vect)*(s->msize+len+1));
        if(s->vect == NULL) {
            s->size = 0;
            s->msize = 0;
            return -1;
        }
        s->msize+=len+1;
    }

    memcpy(s->vect+s->size, c, len+1);

    return 1;
}

int string_cpy(string* s, char* c) {
    int i;

    string_free(*s);
    *s = string_init();
    
    i = string_append(*s, c);
    return i;
}

void string_fprint(string s, FILE* f) {
    fprintf(f, "%s\n", s->vect);
}

void string_print(string s) {
    string_fprint(s, stdout);
}