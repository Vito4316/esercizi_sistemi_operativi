#define _GNU_SOURCE
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<time.h>
#include<sys/wait.h>

void handler() {}

int main(int argc, char** argv) {
    int num_child, i, isFather, child_val;
    if(argc < 2) {
        printf("Argomenti!\n");
        exit(-1);
    }

    num_child = atoi(argv[1]);

    for(i = 0; i < num_child; i++) {
        isFather = 0;
        if(fork() == 0)
            break;
        isFather = 1;
    }    

    if(!isFather) {
        char** vars = malloc(sizeof(char*) * 3);
        vars[0] = "char_loop";
        for(i = 1; i < 2; i++) {
            vars[i] = malloc(sizeof(char));
            srand(getpid());
            vars[i][0] = rand() % (126 - 33) + 33;
        }
        vars[2] = NULL;
        execve("char_loop", vars, NULL);
    }

    struct sigaction signal;
    bzero(&signal, sizeof(struct sigaction)); //setting SIGINT to do nothing
    signal.sa_handler = &handler;
    sigaction(SIGINT, &signal, NULL);

    sleep(1);

    kill(0, SIGINT);

    while(wait(&child_val) != -1) {
        child_val = WEXITSTATUS(child_val);
        printf("val:%c\n", child_val);
    }
}