#include <stdio.h>

int minfact(int n);

int main() {
    int i = 0;
    for(i = 0; i < 100; i++) 
        printf("i = %d fact = %d\n", i, minfact(i));
}

int minfact(int n) {
    int val = 1;
    int i = 1;
    while(n >= val)
        val *= i++;
    return val;
}