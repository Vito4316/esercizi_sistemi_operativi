#include <stdio.h>
#include <stdlib.h>

#ifndef MAX_LEN
#define MAX_LEN 6
#endif

#ifndef MAX_AGE
#define MAX_AGE 99
#endif

#ifndef MIN_AGE
#define MIN_AGE
#endif

typedef struct {
    char * name ;
    int age ;
} record ;

record * rec_rand_create (int n);
void rec_sort (record * v , int n);
void rec_print(record * v , int n);
void rec_free (record * v , int n);

int main() {
    int size = 100;
    record* test_rec = rec_rand_create(size);

    printf("creating random record:\n");
    rec_print(test_rec, size);

    rec_sort(test_rec, size);

    printf("sorting it: \n");
    rec_print(test_rec, size);

    rec_free(test_rec, size);
}

record rand_rec() {
    int name_size = 1 + rand() % MAX_LEN;
    int age = MIN_AGE + rand() % MAX_AGE;
    int i;
    record ret_val;

    ret_val.age = age;
    ret_val.name = malloc(sizeof(*ret_val.name) * name_size);

    for(i = 0; i < name_size; i++) 
        ret_val.name[i] = 'a' + rand() % ('z'-'a');

    return ret_val;
}

record * rec_rand_create (int n) {
    int i;
    
    record* ret_vect = malloc(sizeof(*ret_vect) * n);
    
    for(i = 0; i < n; i++) 
        ret_vect[i] = rand_rec();

    return ret_vect;
}

void rec_sort (record * v , int n) {
    int i, j;

    for(i = 0; i < n; i++) {
        for(j = 0; j < n-1; j++) {
            if(v[j].age > v[j+1].age) {
                record temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
        }
    }
}

void rec_print(record * v , int n) {
    int i;
    for(i = 0; i < n; i++) 
        printf("name: %10s, age: %d\n", v[i].name, v[i].age);
    
}

void rec_free (record * v , int n) {
    int i;
    
    for(i = 0; i < n; i++)
        free(v[i].name);

    free(v);
}