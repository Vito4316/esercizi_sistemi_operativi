#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define NUM_KIDS 5

int isFather(int x);

int main() {
    int i, pid;
    int num, sum = 0;

    for(i = 0; i < NUM_KIDS; i++) {
        if(!isFather(pid = fork()))
            break;
    }
    
    if (!isFather(pid)) {
        srand(getpid());
        num = rand() % 6 +1;
        printf("process: %d, number: %d\n", getpid(), num);
        exit(num);
    }
    else {
        while(wait(&num) != -1) {
            sum += WEXITSTATUS(num);
        }
        printf("all childs are dead, sum is %d\n", sum);
    }
}

int isFather(int x) {
    return x != 0;
}