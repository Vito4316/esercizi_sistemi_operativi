#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv) {
    if(argc != 4)
        return -1;
    int i;
    FILE* file   = fopen(argv[1], "w");
    int n_kids   = atoi (argv[2]);
    int n_writes = atoi (argv[3]);
    int pid;
    
    for(i = 0; i < n_kids; i++) {
        if((pid = fork()) == 0) break;
    }
    
    if(pid) {
        /* while(wait(NULL) != -1);
        fclose(file);*/
        return 0;   
    }

    for(i = 0; i < n_writes; i++)
        fprintf(file, "parent: %d, pid: %d\n", getppid(), getpid());
    
    return 0;
}