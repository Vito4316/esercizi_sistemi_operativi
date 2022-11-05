#define _GNU_SOURCE
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<time.h>

void custom_al(int signum);

int main(int argc, char** argv) {
    if(argc < 3) {
        printf("args");
        return 0;
    }
    int maxn = atoi(argv[1]);
    int max_seconds = atoi(argv[2]);
    int var, num;

    struct sigaction signal;
    bzero(&signal, sizeof(struct sigaction));
    signal.sa_handler = &custom_al;
    sigaction(SIGALRM, &signal, NULL);

    alarm(max_seconds);

    srand(time(NULL));
    num = rand() % maxn;
    while(1) {
        printf("Indovina il numero!\n");
        scanf("%d", &var);
        if(var == num) {
            printf("Hai vinto!\n");
            exit(0);
        }
        if(var > num) printf("Il numero inserito è più grande\n");
        else printf("Il numero inserito è più piccolo\n");
    }
}

void custom_al(int signum) {
    printf("Hai perso!");
    exit(0);
}