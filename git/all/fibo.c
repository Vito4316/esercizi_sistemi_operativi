#include <stdio.h>
#include <stdlib.h>

void print_arr(const int* arr, const int size) {
    int i;
    for(i = 0; i < size; i++) 
        printf("%d - ", arr[i]);
}

int* get_fibo(int n) {
    int* fibo = malloc(sizeof(*fibo) * n);
    int i = 0;

    fibo[0] = 0;
    fibo[1] = 1;

    for(i = 2; i < n; i++) {
        fibo[i] = fibo[i-1] + fibo[i-2];
    }

    return fibo;
}

int main(int argc, char** argv) {
    int size = atoi(argv[1]);
    int* f = get_fibo(size);
    print_arr(f, size);
}