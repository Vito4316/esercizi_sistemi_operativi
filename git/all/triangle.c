#include <stdio.h>

int maxv(int a, int b, int c);
int midv(int a, int b, int c);
int minv(int a, int b, int c);
int is_triangle(int a, int b, int c);

int main() {
    printf("%d", is_triangle(1, 3, 6));
    printf("%d", is_triangle(1, 6, 3));
    printf("%d", is_triangle(3, 6, 1));
    printf("%d", is_triangle(3, 1, 6)); 
    printf("%d", is_triangle(6, 1, 3));
    printf("%d", is_triangle(6, 3, 1));
    printf("%d", is_triangle(3, 3, 1));
    printf("%d", is_triangle(1, 3, 1));
    printf("%d", is_triangle(6, 6, 6));
}

int maxv(int a, int b, int c) {
    a = a > b ? a : b;
    return a > c ? a : c;
}

int midv(int a, int b, int c) {
    return a+b+c - minv(a,b,c) - maxv(a,b,c);
}

int minv(int a, int b, int c) {
    a = a < b ? a : b;
    return a < c ? a : c;
}

int is_triangle(int a, int b, int c) {
    int max = maxv(a,b,c);
    int mid = midv(a,b,c);
    int min = minv(a,b,c);

    return mid + min > max ? 1 : 0;
}