#define _GNU_SOURCE
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<time.h>
#include<sys/wait.h>

void custom_sig(int SIGNUM);
void custom_sig1(int SIGNUM);

int num = 0;
int sig = 0;
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
    int isFather;
    
    struct sigaction signal;
    bzero(&signal, sizeof(struct sigaction)); //setting sigusr 1
    signal.sa_handler = &custom_sig;
    sigaction(SIGUSR1, &signal, NULL);

    signal.sa_handler = &custom_sig;        //setting sigusr 2
    sigaction(SIGUSR2, &signal, NULL);

    for(i = 0; i < num_child; i++) {
        isFather = 0;
        if((child[i] = fork()) == 0) break;
        printf("Generated child %d\n", child[i]);
        isFather = 1; //kids won't arrive here
    }

    /*
    if(isFather) printf("Il mio pid e' %d, e sono il padre!\n", getpid());
    if(isFather) printf("Ho %d figli da uccidere\n", num_child);
    */
    while(isFather) {
        num++;
        num %= module;

        if(sig > 0) {
            int child_to_kill = rand() % num_child;
            int err; 
            if(num == 0) {
                /*
                printf("\n%d\n", num_child);
                for(int i = 0; i < num_child; i++)
                    printf("%d\n", child[i]);
                printf("\n\n");
                */
                //printf("Trying to kill child %d, pid: %d\n", child_to_kill, child[child_to_kill]);
                err = kill(child[child_to_kill], SIGKILL);
                if(!err) printf("child killed");
                else {
                    //printf("Cannot kill child %d, trying to kill all children\n", child[child_to_kill]);
                    kill(-1, SIGKILL);
                    exit(-1);
                }

                //swapping chosen child with last member
                child[child_to_kill] = child[num_child];
                num_child--;
            }
            sig--;
        }

        if(num_child == 0) {
            printf("Father terminated.\n");
            free(child);
            exit(0);
        }
    }

    sleep(3);

    while(!isFather) { //child
        num++;
        num %= module;
        if(num == 0) {
            //printf("pid: %d Sending signal!\n", getpid());
            kill(getppid(), SIGUSR1);
        }
        //sleep(1);
    }
}

void custom_sig(int SIGNUM) {
    if(sig < num_child) sig++;
}

void custom_sig1(int SIGNUM) {}