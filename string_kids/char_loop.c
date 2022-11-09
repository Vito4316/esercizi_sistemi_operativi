#define _GNU_SOURCE
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<time.h>
#include<sys/wait.h>

char var;

void handler() {
    exit(var);
}

int main(int argc, char** argv) {
    if(argc < 2){
        dprintf(1, "argomenti!\n");
        exit(-1);
    }

    var = argv[1][0];

    struct sigaction signal;
    bzero(&signal, sizeof(struct sigaction)); //setting SIGINT
    signal.sa_handler = &handler;
    sigaction(SIGINT, &signal, NULL);
    while(1) {
        var++;
        if(var >= 126)
            var = 33;
    }
}