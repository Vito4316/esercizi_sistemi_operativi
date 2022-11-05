#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int main(int argc, char** argv) {
    if(argc < 4){
        printf("scemo!");
        return 0;
    }
    FILE* file = fopen(argv[1], "w");
    int num_kids = atoi(argv[2]);
    int num_writes = atoi(argv[3]);
    int i;
    int pid;
    for(i = 0; i < num_kids; i++)
        if((pid = fork()) == 0)
            break;
    
    if(pid == 0) {
        for(i = 0; i < num_writes; i++) 
            fprintf(file, "pid: %d parent: %d \n", 
                        getpid(), getppid());
    }
}