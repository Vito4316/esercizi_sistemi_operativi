#define _GNU_SOURCE
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<time.h>
#include<sys/wait.h>

void sigusr1_handle(int SIGNUM);

void child_exec(int module);
void parent_exec(int module);

int num = 0;
int* child;
int num_child;

int main(int argc, char** argv) {
    srand(time(NULL));
    if(argc < 2) {
        printf("argomenti!");
        exit(0);
    }

    num_child = atoi(argv[1]);
    int module = atoi(argv[2]);
    child = malloc(sizeof(*child) * num_child);
    int i;    

    struct sigaction signal;
    bzero(&signal, sizeof(struct sigaction)); //setting sigusr 1
    signal.sa_handler = &sigusr1_handle;
    sigaction(SIGUSR1, &signal, NULL);
    
    for(i = 0; i < num_child; i++) {
        if((child[i] = fork()) == 0) {
            raise(SIGSTOP);
            dprintf(1, "%d waking up!\n", getpid());
            child_exec(module);
            exit(0);
        }
        printf("Generated child %d\n", child[i]);
    }

    parent_exec(module);    
}

void sigusr1_handle(int SIGNUM) {
    if(num_child == 0) return;
    int child_to_kill = rand() % num_child;
    int err; 
    if(num == 0) {
        /*
        printf("\n%d\n", num_child);
        for(int i = 0; i < num_child; i++)
            printf("%d\n", child[i]);
        printf("\n\n"); */
        
        printf("Trying to kill child %d, pid: %d\n", child_to_kill, child[child_to_kill]);
        err = kill(child[child_to_kill], SIGKILL);
        if(!err) printf("child killed\n");
        else {
            printf("Cannot kill child %d, error\n", child[child_to_kill]);
            exit(-1);
        }

        //swapping chosen child with last member
        num_child--;
        child[child_to_kill] = child[num_child];

        if(num_child == 0) {
            printf("Parent terminated.\n");
            free(child);
            exit(0);
        }
    }
}


void child_exec(int module) {
    while(1) { //child
        num++;
        num %= module;
        if(num == 0){
            //dprintf(1, "Sending signal to parent\n");
            kill(getppid(), SIGUSR1);
        }
    }
}

void parent_exec(int module) {
    int i;

    for(i = 0; i < num_child; i++) kill(child[i], SIGCONT);
    printf("Woken up all children\n");

    while(1) {
        num++;
        num %= module;
    }
}